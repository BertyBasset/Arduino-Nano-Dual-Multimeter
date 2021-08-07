# Arduino Nano Every Dual Channel Multimeter
A dual channel combined ammeter and voltmeter for Arduino Every using two 4 channel differential 16 bit I2C modules - ADS1115.


![GitHub Logo](/resources/Meter.png)

## Features:
* Uses Arduino Every flavour of Arduino Nano
* 2 channel differential inputs, both measuring Voltage and Current (positive and negative)
* Relay for auto switching between 5V and 25V voltage ranges
* Current sense resistors for current measurements
* Logging: SD card and Serial - with configurable log parameters
* Max 20 samples /s
* 2 push button UI input with push and hold events for menu navigation
* 'Standard' 2x16 LCD display UI output
* 'Virtual' screen functionality for
  * Meter Display
  * SD Card Status
  * Logger Status

## Schematic:
![GitHub Logo](/resources/Schematic.png)

## Menu System:
![GitHub Logo](/resources/Menu.png)

## Display Modes
### Meter
![GitHub Logo](/resources/Mode_Meter.png)
### SD Status
![GitHub Logo](/resources/Mode_SD.png)
### Logger Status

### Logger Settings



## Logger Settings:
![GitHub Logo](/resources/LoggerSettings.png)
