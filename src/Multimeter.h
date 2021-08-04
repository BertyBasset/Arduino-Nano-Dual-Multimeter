#ifndef _Multimeter_h
#define _Multimeter_h

#include "VDisplay.h"
#include "Arduino.h"
#include "Ammeter.h"
#include "Voltmeter.h"



struct MMReading {
    float v0;
    float v1;
    float i0;
    float i1;
};

class Multimeter {
    public:
        enum Type {
            Voltage,
            Current
        };

        // Contructor
        Multimeter(VDisplay* display, int screenID);

        void measure();
        
        void print(int Channel, Type type, float Value);
        void print(int channel, Multimeter::Type type, bool inputIsZero);
        VDisplay* display;

        MMReading reading;

    private:
        Ammeter ammeters[2];
        Voltmeter voltmeters[2];
        int screenID;

        enum SuffixMultiplier {
            None,
            Milli,
            Micro
        };


};
#endif
