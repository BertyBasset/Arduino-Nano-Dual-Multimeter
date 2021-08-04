#include "Voltmeter.h"
#include "Multimeter.h"
#include <Adafruit_ADS1015.h>
#include <math.h>

Voltmeter::Voltmeter() {}

Voltmeter::Voltmeter(int channel) {
    Voltmeter::channel = channel;

    pinMode(CHANNEL_RELAY_PIN[channel], OUTPUT);                    // Set FSD relay control pin to OUTPUT

    adc = Adafruit_ADS1115(ADC_ADDRESS);                            // Voltage A/D is 0x48
    adc.begin();
}

float Voltmeter::read() {
    
    float voltage = channel == 0 ?                                        // Read specified A/D channel (0, 1) and scale
        (float)adc.readADC_Differential_0_1() * ADC_RESOLUTION:
        (float)adc.readADC_Differential_2_3() * ADC_RESOLUTION;

    // Divide by 5 if relay off (i.e. we've got 2:1:2 resistor network, with voltage measured accross the '1')
    if(relayState == OFF)
        voltage = voltage * (RESISTOR_LADDER[channel][0] + RESISTOR_LADDER[channel][1]+ RESISTOR_LADDER[channel][2]) / RESISTOR_LADDER[channel][1];



    bool _inputIsZero = false;
    
    if((voltage>0 ? voltage : -voltage) <= zeroDelta)  {
        _inputIsZero = true;
    }
    



    //updateBuffer(voltage);

    
    // Relay OFF defaults to 25V FSD mode

    // ADC OVERVOLTAGE PROTECTION
    // Check voltage, and set relay off or on depending on threshold configuration
    // or if floating inpout detected i.e. maybe they will flick a switch, and connect 25V to the input!
    
    // Also if we're at 0V, we may be floating, so in case someone switches
    // in a voltage > 5V, go to 25 FSD mode

    //              5V mode      Voltage too high, so set to 25V mode 
    if(relayState == ON && (voltage>0 ? voltage : -voltage) > RELAY_OFF_VOLTAGE || _inputIsZero) {
        // Turn to 25V mode - relay OFF
        relayState = OFF;
        digitalWrite(CHANNEL_RELAY_PIN[channel], LOW);
    }

    //             25V mode       Is voltage low enough to set to 5V mode (relay on)
    if(relayState == OFF && (voltage>0 ? voltage : -voltage) < RELAY_ON_VOLTAGE  && !_inputIsZero) {
        // Turn to 5V mode - relay ON
        relayState = ON;
        digitalWrite(CHANNEL_RELAY_PIN[channel], HIGH);
    }

    return voltage;
}

