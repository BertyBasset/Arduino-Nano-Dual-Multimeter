/* BUGS
    Logger text overrun
    Logging remove trailing zeroes
    SD directory
*/




#include "Multimeter.h"
#include "Arduino.h"
#include <SPI.h>
#include "InputEvents.h"
#include "Logger.h"

#define VERSION "V1.0"

// Button handlers
constexpr int BUTTON_A = A0;
constexpr int BUTTON_B = A1;
constexpr int SD_DETECT = A2;
InputEvents inputEvents = InputEvents();
void buttonAHandler(int, int);
void buttonBHandler(int, int);
void sdDetectHandler(int, int);

void (*reset)(void) = 0x00;

// Backlight
constexpr int BACKLIGHT_PIN = A3;
//constexpr unsigned long timeout = 10000;
constexpr unsigned long timeout = 300000;
bool powerSaving = false;
constexpr int SPLASH_DELAY = 3000;

// Virtual Display
//  We pass pointer to display down into Multimer and SdCard
constexpr uint8_t cols = 16, rows = 2, pages = 4;
constexpr uint8_t rs = 9, en = 8, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
VDisplay display = VDisplay(rs, en, d4, d5, d6, d7, cols, rows, pages);
uint8_t prevPage = 0;

// SD Card
constexpr int pinCS = 10;

unsigned long timeSinceLastInput = millis();
unsigned long timeHeld = millis();

bool holding = false;

enum Screens {
    MM_DISPLAY = 0,
    SD_STATUS,
    LOGGER_STATUS,
    CONFIG
};

Multimeter multimeter = Multimeter(&display, Screens::MM_DISPLAY);
MMReading Reading;

Logger logger;




void splash() {
        display.setVisiblePage(0);
        display.setCursor(0, 0, 0);
        display.print("Multimeter  ");
        display.print(VERSION);
        display.setCursor(0, 1);
        display.print("bld. ");
        display.print(__DATE__);
        delay(SPLASH_DELAY);

}

void setup() {
    
    pinMode(BACKLIGHT_PIN, OUTPUT);
    digitalWrite(BACKLIGHT_PIN, HIGH);

    splash();
    

    inputEvents.registerDigitalInputEvent(BUTTON_A, buttonAHandler, LOW, 250);
    inputEvents.registerDigitalInputEvent(BUTTON_B, buttonBHandler, LOW, 250);
    inputEvents.registerDigitalInputEvent(SD_DETECT, sdDetectHandler, LOW, 50);

    logger = Logger(&display, Screens::LOGGER_STATUS, Screens::CONFIG, Screens::SD_STATUS, pinCS, &multimeter.reading);

    noSdCard();
    
}

void loop() {

    inputEvents.processEvents();
 
    multimeter.measure();

    logger.main();

    if(!powerSaving) {
        if(millis()-timeSinceLastInput > timeout) {
            powerSavingOn();
        }
    }
    
    if(holding && millis()-timeHeld > 5000) {
        display.setVisiblePage(0);
        display.setCursor(0, 0, 0);
        display.print("RESETTINGRESETTI");
        display.setCursor(0, 1);
        display.print("NGRESETTINGRESET");
        delay(3000);
        while(digitalRead(A0)) {}
        delay(1000);
        reset();
    }

}

void buttonAHandler(int pin, int event) {

    if(event==InputEvents::Events::LOW_TO_HIGH) {
        holding = true;
        timeHeld = millis();
    }
    else if(event==InputEvents::Events::HIGH_TO_LOW || event==InputEvents::Events::HOLD_RELEASE) {
        holding = false;
    }

    if(!powerSaving) {
        if(event == InputEvents::Events::HIGH_TO_LOW) {
            switch(display.getVisiblePage()) {
                case Screens::MM_DISPLAY:
                    display.setVisiblePage(Screens::SD_STATUS);
                    break;
                case Screens::SD_STATUS:
                    display.setVisiblePage(Screens::LOGGER_STATUS);
                    break;
                case Screens::LOGGER_STATUS:
                    display.setVisiblePage(Screens::MM_DISPLAY);
                    break;
                case Screens::CONFIG:
                    if(logger.selectedRow) {
                        logger.buttonHeld();
                    }
                    display.setVisiblePage(prevPage);
                    logger.saveSettings();
                    break;
            }
        }
        else if(event == InputEvents::Events::HELD_HIGH) {
            switch(display.getVisiblePage()) {
                case Screens::MM_DISPLAY:
                case Screens::SD_STATUS:
                case Screens::LOGGER_STATUS:
                    if(logger.isLogging) {
                        display.setVisiblePage(Screens::LOGGER_STATUS);
                    }
                    else {
                        prevPage = display.getVisiblePage();
                        display.setVisiblePage(Screens::CONFIG);
                    }
                    break;
                case Screens::CONFIG:
                    if(logger.selectedRow) {
                        logger.buttonHeld();
                    }
                    display.setVisiblePage(prevPage);
                    logger.saveSettings();
                    break;
            }
        }
    }
    else if(event != InputEvents::Events::LOW_TO_HIGH) {
        powerSavingOff();
    }
    timeSinceLastInput = millis();
}

void buttonBHandler(int pin, int event) {
    if(!powerSaving) {
        if(event == InputEvents::Events::HIGH_TO_LOW) {
            switch(display.getVisiblePage()) {
                case Screens::CONFIG:
                    logger.buttonPressed();
                    break;
                case Screens::SD_STATUS:
                    // List files if on SD screen and we are not logging
                    if(!logger.isLogging && logger.sdCardDetected)
                        logger.listFiles();
                    break;


            }
        }
        else if(event == InputEvents::Events::HELD_HIGH) {
            switch(display.getVisiblePage()) {
                case Screens::CONFIG:
                    logger.buttonHeld();
                    break;
                default:
                    if(!logger.isLogging) {
                        display.setVisiblePage(Screens::LOGGER_STATUS);
                    }
                    logger.toggle();
            }
        }
    }
    else if(event != InputEvents::Events::LOW_TO_HIGH) {
        powerSavingOff();
    }
    timeSinceLastInput = millis();
}

void sdDetectHandler(int pin, int event) {

    switch(event) {
        //case InputEvents::Events::LOW_TO_HIGH:
        case InputEvents::Events::HELD_HIGH:
            logger.evaluateFiles();
            logger.sdCardDetected = true;
            if(millis() > 500+SPLASH_DELAY)
                display.setVisiblePage(Screens::SD_STATUS);
            display.setCursor(4, 0, Screens::SD_STATUS);
            display.print("Yes");
            break;
        case InputEvents::Events::HIGH_TO_LOW:
        case InputEvents::Events::HOLD_RELEASE:
            logger.sdCardDetected = false;
            noSdCard();
            display.setVisiblePage(Screens::SD_STATUS);
            break;
    }

    powerSavingOff();
    timeSinceLastInput = millis();

}

void noSdCard() {
    display.setCursor(0, 0, Screens::SD_STATUS);
    display.clear();
    display.print("SD: No");
    display.setCursor(14, 0);
    display.print("#-");
    display.setCursor(0, 1);
    display.print("-kB/-kB");
}

void powerSavingOn() {
    digitalWrite(BACKLIGHT_PIN, LOW);
    powerSaving = true;
}

void powerSavingOff() {
    digitalWrite(BACKLIGHT_PIN, HIGH);
    powerSaving = false;
}
