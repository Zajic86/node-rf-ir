# node-rf-ir 
***still in progress***

Node MCU ESP8266 with IR Rx/Tx diode and 433MHz Rx/Tx store and send codes.

**/nodeIRDuplicator** : IR send and receive through webserver (connect to wifi or set as AP). First code test. All accepted codes are transformed into buttons for the possibility to duplicate individual codes and a field to insert and send your own code. Also you can save codes to txt file. 

<img src="/imgs/ir-rx-tx.png">
<img src="https://www.martinlukasek.cz/imgs/proj/irrf.jpg">

## progress
- OK install NodeMCU drivers and connect to IDE
- OK Testing IR Rx 
- OK Testing IR Tx on Node MCU with IRremoteESP8266 lib
- OK Webserver
- OK AP/HOST mode
- OK Save IR codes as buttons
- OK Send custom IR code
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

### other
- Li-Ion 18650 cell
- BMS for 18650
- USB connector for charging
- antennas, case

my home RF remote freq.: 433.92MHz

<img src="https://www.martinlukasek.cz/imgs/proj/433_1.jpg">
