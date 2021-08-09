# *Arduino Nano Every* Dual Channel Multimeter
A dual channel combined ammeter and voltmeter for *Arduino Nano Every* using two 4 channel differential 16 bit I2C modules - ADS1115.


![GitHub Logo](/resources/Meter.png)

## Features:
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
  * Logger Settings

## Simultaneous Voltage and Current Measurement
To measure I vs V, or power dissipation in a component or module, wire one channel up thus:
![GitHub Logo](/resources/IVMeasurement.png)

## Voltage Autoranging
The ADCs have 5V max differential voltage input. To extend this range to 25V, we use a relay to switch in a 2:1:2 potentiometer:


## Schematic:
![GitHub Logo](/resources/Schematic.png)

## Menu System:
![GitHub Logo](/resources/Menu.png)

## Display Modes
### Mode: Meter
![GitHub Logo](/resources/Mode_Meter.png)
### Mode: SD Status
![GitHub Logo](/resources/Mode_SD.png)
### Mode: Logger Status
![GitHub Logo](/resources/Mode_Logger.png)
### Mode: Logger Settings
![GitHub Logo](/resources/Mode_LoggerSettings.png)

Display Modes are maintained via 'virtual' displays. Virtual displays can be written to and viewed independently. For instance, a logging session can write to a virtual logger display, whilst a meter display is being displayed in real time. The virtual displays are implemented by Vdisplay.cpp/h and use dynamic memory allocation so that virtual displays can be created and removed at run-time.

## Logger Settings:
![GitHub Logo](/resources/LoggerSettings.png)

## To Do:
* Implement One-shot functionality
* General code tidy
* Tidy floating voltage detection to stop relay 'chatter'
* Meter screen - only refresh display about twice /second
