#ifndef _SdCard_h
#define _SdCard_h

#include "Arduino.h"
#include <SD.h>


class SdCard {
    
    public:
        SdCard();
        //SdCard(Stream);
        void TestWriteFile();

    private:
        int pinCS = 10;

};


#endif

