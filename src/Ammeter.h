#ifndef _Ammeter_h
#define _Ammeter_h

#include "Arduino.h"
#include <Adafruit_ADS1015.h>

class Ammeter {
    public:
        Ammeter();
        Ammeter(int channel);       // 0 or 1

        float read();             // Make measurement


    private:
        int channel;
        // These are nominally 150mR resistors
        float R_SENSE [2] = {0.15, 0.15};            // Adjust these according to actual values. These are 5% tolerance rather than 0.1%  :-(

        int ADC_ADDRESS = 0x49;
        float ADC_RESOLUTION = 1.875e-4;

        Adafruit_ADS1115 adc;

};

#endif