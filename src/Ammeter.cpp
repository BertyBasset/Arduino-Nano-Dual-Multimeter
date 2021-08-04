#include "Ammeter.h"
#include "Multimeter.h"

#include <Adafruit_ADS1015.h>

Ammeter::Ammeter() {}


Ammeter::Ammeter(int channel) {
    Ammeter::channel = channel;


    adc = Adafruit_ADS1115(ADC_ADDRESS);       // Current A/D is 0x49
    adc.begin();    
}

float Ammeter::read() {
    float vDrop = channel == 0 ?
        (float)adc.readADC_Differential_0_1() * ADC_RESOLUTION:
        (float)adc.readADC_Differential_2_3() * ADC_RESOLUTION;
    
    // May need to adjust gain to maximise current FSD
    // I = V / R
    return vDrop / R_SENSE[channel];

}
