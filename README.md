# node-rf-ir 
***still in progress***

Node MCU ESP8266 with IR Rx/Tx diode, HC-12 433MHz and NRF24L01 2.4GHz to receive, store and send codes.
 
## progress
- OK install NodeMCU drivers and connect to IDE
- OK Testing IR Rx 
- OK Testing IR Tx on Node MCU with IRremoteESP8266 lib
- Webserver
- AP/HOST mode
- Save IR codes (flash or sd?)
- Open saved codes
- Send saved codes
- Make web admin page

## HW

<img src="https://components101.com/sites/default/files/component_pin/NodeMCU-ESP8266-Pinout.jpg" width="500">

### Core
- **NodeMCU with ESP8266**
- **IR emitting diode** (950nm tested)
- **IR sensor** (KY-022/VS1838B)
- **433MHz receiver** XD-MK-5V / STX882 better
- **433MHz transmitter** XD-FST / SRX882 better
  - I'm trying the **HC-12 SI4463** module but no luck yet
- **2.4GHz module** NRF24L01(+PA+LNA)

I still don't know if it is possible to connect these components together at once without interference. But I'm working on it

### Aditional
- 2x Li-Ion 18650 cell
- BMS for 18650
- USB connector for charging
- antennas, case