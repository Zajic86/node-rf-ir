# node-rf-ir 
***still in progress***

Node MCU ESP8266 with IR Rx/Tx diode, HC-12 433MHz and NRF24L01 2.4GHz to receive, store and send codes.

**/nodeIRDuplicator** : IR send and receive through webserver (connect to wifi or set as AP). First code test. All accepted codes are transformed into buttons for the possibility to duplicate individual codes and a field to insert and send your own code. Also you can save codes to txt file. 

<img src="/imgs/ir-rx-tx.png">

## progress
- OK install NodeMCU drivers and connect to IDE
- OK Testing IR Rx 
- OK Testing IR Tx on Node MCU with IRremoteESP8266 lib
- OK Webserver
- OK AP/HOST mode
- OK Save IR codes as buttons
- OK Save IR codes as txt file
- Open saved codes
- Send saved codes
- Repeat for RF 433MHz (simple rx/tx, but more modulations,freq. etc.)
- Make beauty and user-friendly GUI for web (responsive for mobile devices of course)

## HW

### Core
**NodeMCU with ESP8266** 

<img src="https://components101.com/sites/default/files/component_pin/NodeMCU-ESP8266-Pinout.jpg" width="500">

**IR emitting diode** (950nm tested) ==> D0 (GPIO-16)

<img src="https://grobotronics.com/images/detailed/1/31enqibtuyl_grobo.jpg" width="500">

**IR sensor** (KY-022/VS1838B) ==> D1 (GPIO-5)

<img src="https://arduinomodules.info/wp-content/uploads/KY-022_infrared_receiver_module-300x300.jpg" width="500">

**433MHz receiver** XD-MK-5V (STX882 better)<br>
**433MHz transmitter** XD-FST (SRX882 better)

<img src="https://danyk.cz/reverz21b.jpg" width="500">

I'm trying the **HC-12 SI4463** module but no luck yet

<img src="https://www.allaboutcircuits.com/uploads/thumbnails/HC12.jpg" width="500">

**2.4GHz module** NRF24L01(+PA+LNA)

<img src="https://europe1.discourse-cdn.com/arduino/original/4X/7/d/6/7d627f8ddd622cdda15af669ae1c7d097a0341b4.jpeg"  width="500">

**Connection** - NRF24L01 x NodeMCU<br>
VCC x 3.3V<br>
GND x GND<br>
CE x D4 (GPIO 2)<br>
CSN x D2 (GPIO 4)<br>
MOSI x D7 (GPIO 13)<br>
MISO x D6 (GPIO 12)<br>
SCK x D5 (GPIO 14)

I still don't know if it is possible to connect these components together at once without interference. But I'm working on it

### other
- Li-Ion 18650 cell
- BMS for 18650
- USB connector for charging
- antennas, case