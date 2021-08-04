#include "VDisplay.h"
#include <LiquidCrystal.h>
#include <PrintString.h>

VDisplay::VDisplay() {};

VDisplay::VDisplay(uint8_t rs, uint8_t en, uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7, uint8_t cols, uint8_t rows, uint8_t pages) {
    
    printer = PrintString();

    displayBuffer = malloc((cols+1)*rows*pages);

    VDisplay::cols = cols;
    VDisplay::rows = rows;
    VDisplay::pages = pages;

    lcd = LiquidCrystal(rs, en, d4, d5, d6, d7);
    lcd.begin(cols, rows);

    cursor = (Cursor){.col = 0, .row = 0};

    //Initialise to be blank
    for(int i = 0; i < pages; i++) {
        for(int j = 0; j < rows; j++) {
            //char* page = (char*)displayBuffer.retrievePropertyReference(i, j);
            for(int k = 0; k < cols; k++) {
                //displayBuffer[i][j][k] = 0x20;
                displayBuffer[i*rows*(cols+1)+j*(cols+1)+k] = 0x20;
                //page[k] = 0x20;
            }
            //displayBuffer[i][j][cols] = 0x00;
            displayBuffer[i*rows*(cols+1)+j*(cols+1)+cols] = 0x00;
            //page[cols] = 0x00;
        }
    }
}

void VDisplay::setTargetPage(uint8_t page) {
    //Bounded above by number of pages
    targetPage = page >= pages ? pages-1 : page;
}

void VDisplay::setVisiblePage(uint8_t page) {
    visiblePage = page >= pages ? pages-1 : page;

    for(int i = 0; i < rows; i++) {
        lcd.setCursor(0, i);
        //char* text = (char*)displayBuffer.retrievePropertyReference(page, i);
        for(int j = 0; j < cols; j++) {
            //lcd.print(displayBuffer[visiblePage][i][j]);
            lcd.print(displayBuffer[visiblePage*rows*(cols+1)+i*(cols+1)+j]);
            //lcd.print(text[j]);
        }
    }

    lcd.setCursor(cursor.col, cursor.row);
}

uint8_t VDisplay::getVisiblePage() {

    return visiblePage;

}

void VDisplay::clear() {
    if(targetPage == visiblePage) {
        lcd.clear();
    }

    for(int i = 0; i < rows; i++) {
        //char* text = (char*)displayBuffer.retrievePropertyReference(targetPage, i);
        for(int j = 0; j < cols; j++) {
            //text[j] = 0x20;
            //displayBuffer[targetPage][i][j] = 0x20;
            displayBuffer[targetPage*rows*(cols+1)+i*(cols+1)+j] = 0x20;
        }
    }
}

void VDisplay::setCursor(uint8_t col, uint8_t row) {
    cursor = (Cursor){.col = col, .row = row};
}

void VDisplay::setCursor(uint8_t col, uint8_t row, uint8_t page) {
    cursor = (Cursor){.col = col, .row = row};
    setTargetPage(page);
}

void VDisplay::showNextPage() {
    setVisiblePage(visiblePage + 1 >= pages ? 0 : visiblePage + 1);
}

void VDisplay::showPreviousPage() {
    setVisiblePage(visiblePage - 1 < 0 ? pages-1 : visiblePage - 1);
}