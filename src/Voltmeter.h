#ifndef _Voltmeter_h
#define _Voltmeter_h

#include "Arduino.h"
#include <Adafruit_ADS1015.h>

#define ON 1
#define OFF 0

class Voltmeter {
    public:
        Voltmeter();
        Voltmeter(int channel);       // 0 or 1

        float read();             // Make measurement 



    private:
        // Floating input detection stuff
        // The plan is to put subsequent voltage samples into the circular buffer
        // Then if the mean is within x of 0, and Max - Min value > y, then input is deemed floating
        bool inputIsZero();
    
        float zeroDelta = 0.0001;        // If the mean voltage is < 1mV, then call it zero

        int channel;

        bool relayState = OFF;

        int CHANNEL_RELAY_PIN[2] = {6, 7};

        ///* 
        // Operation - switch mode at low voltage
        // Provide some hysteresis between switching on and turning off
        float RELAY_ON_VOLTAGE = 4.7;
        float RELAY_OFF_VOLTAGE = 4.2;
        //*/

        /* 
        // Test - switch mode at approx 5V
        // Provide some hysteresis between switching on and turning off
        float RELAY_ON_VOLTAGE = 2.8;
        float RELAY_OFF_VOLTAGE = 2.2;
        */


        int ADC_ADDRESS = 0x48;
        float ADC_RESOLUTION = 1.875e-4;

        //float RESISTOR_LADDER[2][3] = {{2.0, 1.0, 2.0}, {2.0, 1.0, 2.0}};
        float RESISTOR_LADDER[2][3] = {{19.99, 9.95, 20.01}, {20.0, 9.95, 20.0}};     // <- Actual measured values

        Adafruit_ADS1115 adc;
};

#endif
