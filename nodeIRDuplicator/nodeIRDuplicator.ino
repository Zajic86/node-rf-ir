#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <IRremoteESP8266.h>
#include <IRrecv.h>
#include <IRsend.h>
#include <IRutils.h>
#include <FS.h>
#include <map>

const char* ssid = "-";
const char* password = "-";

ESP8266WebServer server(80);

const uint16_t IR_RX_PIN = 14; // IR Rx pin
const uint16_t IR_TX_PIN = 4; // IR Tx pin

IRrecv irrecv(IR_RX_PIN);
IRsend irsend(IR_TX_PIN);

decode_results results;

std::map<int, String> codeHistoryMap;

void handleRoot();
void handleSend();
void handleDownload();
void handleAddCode();
void handleCodes();
void handleIRReceive();

void setup() {
  Serial.begin(115200);
  irrecv.enableIRIn();
  irsend.begin();

  if (!SPIFFS.begin()) {
    Serial.println("Failed to mount file system");
    return;
  }

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  int attempts = 0;
  Serial.print("Connecting to WiFi...");
  while (WiFi.status() != WL_CONNECTED && attempts < 10) {
    delay(1000);
    Serial.print(".");
    attempts++;
  }

  if (WiFi.status() != WL_CONNECTED) {
    WiFi.mode(WIFI_AP);
    WiFi.softAP("ESPIR", "12345678");
    Serial.println("Failed to connect to WiFi, created AP.");
  } else {
    Serial.println("Connected to WiFi.");
  }

  server.on("/", HTTP_GET, handleRoot);
  server.on("/send", HTTP_GET, handleSend);
  server.on("/download", HTTP_GET, handleDownload);
  server.on("/addcode", HTTP_POST, handleAddCode);
  server.on("/codes", HTTP_GET, handleCodes);
  server.begin();
  Serial.println("HTTP server started.");
}

void loop() {
    server.handleClient();
    handleIRReceive();
}

void handleRoot() {
  String html = "<html><head><script>";
  html += "function sendCode(code) {";
  html += "  var xhr = new XMLHttpRequest();";
  html += "  xhr.open('GET', '/send?code=' + code, true);";
  html += "  xhr.send();";
  html += "}";
  html += "function sendCustomCode() {";
  html += "  var codeCustom = document.getElementById('codeInput').value;";
  html += "  var xhr = new XMLHttpRequest();";
  html += "  xhr.open('GET', '/send?code=' + codeCustom, true);";
  html += "  xhr.send();";
  html += "}";
  html += "function refreshCodes() {";
  html += "  var xhr = new XMLHttpRequest();";
  html += "  xhr.onreadystatechange = function() {";
  html += "    if (xhr.readyState === XMLHttpRequest.DONE) {";
  html += "      if (xhr.status === 200) {";
  html += "        document.getElementById('codeList').innerHTML = xhr.responseText;";
  html += "      }";
  html += "    }";
  html += "  };";
  html += "  xhr.open('GET', '/codes', true);";
  html += "  xhr.send();";
  html += "}";
  html += "setInterval(refreshCodes, 1000);";
  html += "</script></head>";
  html += "<body onload='refreshCodes()' style='font-family: sans-serif;background-color:#212121;color:#C2C2C2'>";
  html += "<center><h1>IR codes</h1></center>";
  html += "<input type='text' id='codeInput' placeholder='Enter custom code'>";
  html += "<button onclick='sendCustomCode()'>Send Code</button> ";
  html += " &nbsp <a href='/download'> <button> Download Codes</button></a><hr>";
  html += "<div id='codeList'>";
  html += "</div>";
  html += "</body></html>";

  server.send(200, "text/html", html);
}

void sendCodeHistoryToClients() {
  String codeListHtml = "";
  for (auto const& entry : codeHistoryMap) {
    int buttonCode = entry.first;
    String code = entry.second;
    codeListHtml += "<button style='padding:5px;width:100%;font-size:22px;font-weight:bold;' onclick='sendCode(\"" + code + "\")'>" + code + "</button><br>";
  }
  server.send(200, "text/plain", codeListHtml);
}

void handleAddCode() {
  server.send(200, "text/plain", "Code added.");
}

void handleSend() {
  if (server.hasArg("code")) {
    int buttonCode = strtoul(server.arg("code").c_str(), nullptr, 16);
    if (codeHistoryMap.find(buttonCode) != codeHistoryMap.end()) {
      irsend.sendNEC(buttonCode);
      server.send(200, "text/plain", "Code sent.");
    } else {
      server.send(404, "text/plain", "Code not found.");
    }
  } else {
    server.send(400, "text/plain", "Bad request.");
  }
}

void handleDownload() {
  String content = "NODE MCU IR SCANNED Codes:\n";
  for (auto const& entry : codeHistoryMap) {
    int buttonCode = entry.first;
    String code = entry.second;
    content += code + " (0x" + String(buttonCode, HEX) + ")\n";
  }

  File file = SPIFFS.open("/codes.txt", "w");
  if (file) {
    file.print(content);
    file.close();
    server.sendHeader("Content-Disposition", "attachment; filename=codes.txt");
    server.send(200, "text/plain", content);
  } else {
    server.send(500, "text/plain", "Error creating file.");
  }
}

void handleCodes() {
  String codeListHtml = "";
  for (auto const& entry : codeHistoryMap) {
    int buttonCode = entry.first;
    String code = entry.second;
    codeListHtml += "<button style='padding:5px; width:100%;font-size:22px;font-weight:bold;' onclick='sendCode(\"" + code + "\")'>" + code + "</button><br>";
  }
  server.send(200, "text/plain", codeListHtml);
}

void handleIRReceive() {
  if (irrecv.decode(&results)) {
    int buttonCode = results.value;
    codeHistoryMap[buttonCode] = String(buttonCode, HEX);
    irrecv.resume();
    sendCodeHistoryToClients();
  }
}
