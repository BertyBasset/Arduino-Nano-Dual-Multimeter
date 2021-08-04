#ifndef _VDisplay_h
#define _VDisplay_h


#include "Arduino.h"
#include <LiquidCrystal.h>
#include <PrintString.h>


// Virtual Display - Static buffer version
class VDisplay {

    public:

        VDisplay();
        VDisplay(uint8_t rs, uint8_t en, uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7, uint8_t cols = 16, uint8_t rows = 2, uint8_t pages = 2);

        // Virtual screen stuff
        void setTargetPage(uint8_t page);      // Select screen to print to
        void setVisiblePage(uint8_t page);        // Select screen to display

        uint8_t getVisiblePage();

        void showNextPage();
        void showPreviousPage();

        void clear();
        void setCursor(uint8_t col, uint8_t row);
        void setCursor(uint8_t col, uint8_t row, uint8_t page);

        template <typename T>
        void print(T text) {
            
            printer.print(text);
            
            if(targetPage == visiblePage) {
                lcd.setCursor(cursor.col, cursor.row);
                lcd.print(printer.getString());
            }

            //char* bufferdest = (char*)displayBuffer.retrievePropertyReference(targetPage, cursor.row);
            String source = printer.getString();
            int numchars = printer.size();

            //Terminate before buffer overrun
            for(int i = 0; cursor.col < cols && i < numchars; cursor.col++, i++) {
                //displayBuffer[targetPage][cursor.row][cursor.col] = source.charAt(i);
                displayBuffer[targetPage*rows*(cols+1)+cursor.row*(cols+1)+cursor.col] = source.charAt(i);
            }

            printer.clear();
        }

    private:
        /*
        static const uint8_t cols = COLS;       // Defined in VDisplay_config.h
        static const uint8_t rows = ROWS;       // Defined in VDisplay_config.h
        static const uint8_t pages = PAGES;     // Defined in VDisplay_config.h
        char displayBuffer[pages][rows][cols+1];
        */

        uint8_t cols;
        uint8_t rows;
        uint8_t pages;

        char* displayBuffer;

        LiquidCrystal lcd;

        PrintString printer;
        
        struct Cursor {
            uint8_t col;
            uint8_t row;
        }cursor;


        uint8_t targetPage = 0;     // Screen we print to
        uint8_t visiblePage = 0;    // Screen we display

};

#endif
