#ifndef _Logger_h
#define _Logger_h

#include "Multimeter.h"
#include "VDisplay.h"
#include "Arduino.h"
#include "menu.h"
#include <SD.h>

class Logger {
    public:
    
        Logger();
        Logger(VDisplay* display, int loggerStatusScreenID, int configScreenID, int sdStatusScreenID, int pinCS, MMReading* source);

        void main();

        void toggle();

        void buttonPressed();
        void buttonHeld();

        void saveSettings();
        
        bool isLogging = 0;
        bool selectedRow = 0;

        bool sdCardDetected = 0;

        void evaluateFiles();
        void listFiles();        // show sd files as scrolling list
    private:

        void initLog();
        void log();
        void write(char* str);

        uint8_t bufferIndex = 0;
        char outputBuffer[16] = {0};

        unsigned long numSamples;

        unsigned long timeLastLog;
        unsigned long timeLogStart;
        unsigned long timeRefresh;

        MMReading* source;

        int sdStatusScreenID;
        int loggerStatusScreenID;
        int configScreenID;

        Menu menu;

        VDisplay* display;

        char filename[13];
        File file;
        int pinCS;
        unsigned int nextFileId = 0;

        unsigned long totalSize = 0;
        int numFiles = 0;
        float cardSize = 0;
        unsigned long timeLastFlush = 0;

        void getSdStatus(); 
        float getCardSize();
        void sdUpdate();

};

#endif
