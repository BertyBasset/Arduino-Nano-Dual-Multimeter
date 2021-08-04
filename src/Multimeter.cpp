#include "Multimeter.h"
#include "VDisplay.h"
#include <Math.h>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wwrite-strings"

Multimeter::Multimeter(VDisplay* display, int screenID) {
    Multimeter::display = display;
    Multimeter::screenID = screenID;

    ammeters[0] = Ammeter(0);
    ammeters[1] = Ammeter(1);
    voltmeters[0] = Voltmeter(0);
    voltmeters[1] = Voltmeter(1);
}

void Multimeter::measure() {

    reading.v0 = voltmeters[0].read();
    reading.i0 = ammeters[0].read();
    reading.v1 = voltmeters[1].read();
    reading.i1 = ammeters[1].read();

    //Only print when necessary
    if(display->getVisiblePage() == screenID) {

        display->setTargetPage(screenID);

        print(0, Voltage, reading.v0);
        print(0, Current, reading.i0);
        print(1, Voltage, reading.v1);
        print(1, Current, reading.i1);

    }
    
}

// Channels 0 and 1
void Multimeter::print(int channel, Multimeter::Type type, float value) {

    // Set cursor according to Channel (0 or 1) and Type (Voltage or Current)
    int x = channel == 0 ? 0 : 8;
    int y = type == Multimeter::Voltage ? 0 : 1;
    display->setCursor(x, y);
    
    if(type == Multimeter::Current) {
        //if(abs(value) < .0001) {
        if((value>0 ? value : -value) < 0.0001) {
            display->print("  0.00 A");
            return;
        }
    }
    if(type == Multimeter::Voltage) {
        //if(abs(value) < .0001) {
        if((value>0 ? value : -value) < 0.0001) {
            display->print("  0.00 V");
            return;
        }
    }


    // Value scaling and suffix selection
    // i.e. if value < 0.001 e.g. 0.0009, we want to show as 900uA
    //      if value < 1 e.g. 0.9, we want to show as 900mA
    Multimeter::SuffixMultiplier suffixMultiplier = Multimeter::None;
    //if(abs(value) < 0.001) 
    if((value>0 ? value : -value) < 0.001)
        suffixMultiplier = Multimeter::Micro;
    //else if(abs(value) < 1)
    else if((value>0 ? value : -value) < 1)
        suffixMultiplier = Multimeter::Milli;

    // Scale Value
    if(suffixMultiplier == Multimeter::Micro)
        value = value * 1000000.0;
    if(suffixMultiplier == Multimeter::Milli)
        value = value * 1000.0;


    // Number is XXX.YY
    // Right justify on decimal place
    //if(abs(value) < 100.0)
    if((value>0 ? value : -value) < 100.0)
        display->print(' ');
    //if(abs(value) < 10.0)
    if((value>0 ? value : -value) < 10.0)
        display->print(' ');
    display->print(value);



    // Add multiplier suffix
    x = channel == 0 ? 6 : 14;
    display->setCursor(x, y);

    if(suffixMultiplier == Multimeter::Micro)
        display->print((char)228);  // Micro character
    else if(suffixMultiplier == Multimeter::Milli)
        display->print('m');
    else 
        display->print(' ');


    if(type == Multimeter::Voltage)
        display->print('V');
    else
        display->print('A');
}

#pragma GCC diagnostic pop
