#include "menu.h"
#include "Logger.h"
#include "InputEvents.h"
#include "VDisplay.h"
#include "Multimeter.h"
#include <EEPROM.h>



constexpr char* colsAll_Channels = "Time,Voltage 1,Current 1,Voltage 2,Current 2\n";
constexpr char* colsV0_only = "Time,Voltage\n";
constexpr char* colsI0_only = "Time,Current\n";
constexpr char* colsV0_and_V1 = "Time,Voltage 1,Voltage 2\n";
constexpr char* colsI0_and_I1 = "Time,Current 1,Current 2\n";
constexpr char* colsV0_and_I0 = "Time,Voltage,Current\n";

/* Auto Generated Code - do not modify- use Generator*/
constexpr char* settingsText = "Logged Channels\000All Channels\000V0 only\000I0 only\000V0 and V1\000I0 and I1\000V0 and I0\000Sample Rate\00010/s\00020/s\000Max. Speed\0001/min\0002/min\00010/min\0001/s\0002/s\0005/s\000Max. Duration\000Infinite\0001 second\0005 seconds\00010 seconds\00020 seconds\00030 seconds\0001 minute\0005 minutes\00010 minutes\00030 minutes\0001 hour\0003 hours\0006 hours\00012 hours\00024 hours\000Output\000SD ONLY\000UART ONLY\000SD & UART\000Baud Rate\0009600\00019200\000OneShot\000Inactive\000Active\000OneShot: Repeat\000Once only\000x2\000x5\000x10\000x20\000x50\000x100\000Max. Duration\000OneShot: Trig.\000V0\000V1\000I0\000I1\000OneShot: Edge\000Rising\000Falling\000OneShot: Sign\000Positive: +Ve\000Negative: -Ve\000Abs.: |Ve|\000OneShot: V Trig\000 0.0V\000 0.3V\000 0.6V\000 1.8V\000 2.0V\000 3.3V\000 5.0V\000 7.0V\000 9.0V\00012.0V\00015.0V\00021.0V\000OneShot: I Trig\000  0.0mA\000  0.5mA\000  1.0mA\000  2.0mA\000  5.0mA\000 10.0mA\000 20.0mA\000 50.0mA\000100.0mA\000250.0mA\000500.0mA\000  1.0A\000  2.0A\000";
constexpr char* optionptrs[] = {settingsText+16, settingsText+29, settingsText+37, settingsText+45, settingsText+55, settingsText+65, 0x00, settingsText+87, settingsText+92, settingsText+97, settingsText+108, settingsText+114, settingsText+120, settingsText+127, settingsText+131, settingsText+135, 0x00, settingsText+153, settingsText+162, settingsText+171, settingsText+181, settingsText+192, settingsText+203, settingsText+214, settingsText+223, settingsText+233, settingsText+244, settingsText+255, settingsText+262, settingsText+270, settingsText+278, settingsText+287, 0x00, settingsText+303, settingsText+311, settingsText+321, 0x00, settingsText+341, settingsText+346, 0x00, settingsText+360, settingsText+369, 0x00, settingsText+392, settingsText+402, settingsText+405, settingsText+408, settingsText+412, settingsText+416, settingsText+420, settingsText+425, 0x00, settingsText+454, settingsText+457, settingsText+460, settingsText+463, 0x00, settingsText+480, settingsText+487, 0x00, settingsText+509, settingsText+523, settingsText+537, 0x00, settingsText+564, settingsText+570, settingsText+576, settingsText+582, settingsText+588, settingsText+594, settingsText+600, settingsText+606, settingsText+612, settingsText+618, settingsText+624, settingsText+630, 0x00, settingsText+652, settingsText+660, settingsText+668, settingsText+676, settingsText+684, settingsText+692, settingsText+700, settingsText+708, settingsText+716, settingsText+724, settingsText+732, settingsText+740, settingsText+747, 0x00};
constexpr Setting settingptrs[] = {{settingsText+0, optionptrs+0}, {settingsText+75, optionptrs+7}, {settingsText+139, optionptrs+17}, {settingsText+296, optionptrs+33}, {settingsText+331, optionptrs+37}, {settingsText+352, optionptrs+40}, {settingsText+376, optionptrs+43}, {settingsText+439, optionptrs+52}, {settingsText+466, optionptrs+57}, {settingsText+495, optionptrs+60}, {settingsText+548, optionptrs+64}, {settingsText+636, optionptrs+77}};

enum Settings {Logged_Channels = 0, Sample_Rate, Max_Duration, Output, Baud_Rate, OneShot, OneShot_Repeat, OneShot_Trig_, OneShot_Edge, OneShot_Sign, OneShot_V_Trig, OneShot_I_Trig};

enum Logged_Channels {All_Channels = 0, V0_only, I0_only, V0_and_V1, I0_and_I1, V0_and_I0};
enum Sample_Rate {_10_s = 0, _20_s, Max_Speed, _1_min, _2_min, _10_min, _1_s, _2_s, _5_s};
enum Max_Duration {Infinite = 0, _1_second, _5_seconds, _10_seconds, _20_seconds, _30_seconds, _1_minute, _5_minutes, _10_minutes, _30_minutes, _1_hour, _3_hours, _6_hours, _12_hours, _24_hours};
enum Output {SD_ONLY = 0, UART_ONLY, SD_UART};
enum Baud_Rate {_9600 = 0, _19200};
enum OneShot {Inactive = 0, Active};
enum OneShot_Repeat {Once_only = 0, x2, x5, x10, x20, x50, x100, MaxDuration};
enum OneShot_Trig_ {V0 = 0, V1, I0, I1};
enum OneShot_Edge {Rising = 0, Falling};
enum OneShot_Sign {Positive_Ve = 0, Negative_Ve, Abs_Ve_};
enum OneShot_V_Trig {_0_0V = 0, _0_3V, _0_6V, _1_8V, _2_0V, _3_3V, _5_0V, _7_0V, _9_0V, _12_0V, _15_0V, _21_0V};
enum OneShot_I_Trig {_0_0mA = 0, _0_5mA, _1_0mA, _2_0mA, _5_0mA, _10_0mA, _20_0mA, _50_0mA, _100_0mA, _250_0mA, _500_0mA, _1_0A, _2_0A};

constexpr unsigned int baudRates[] = {9600, 19200};
constexpr unsigned int samplePeriod[] = {100, 50, 0, 60000, 30000, 6000, 1000, 500, 200};
constexpr unsigned long maxDurations[] = {4294967295, 1000, 5000, 10000, 20000, 30000, 60000, 300000, 600000, 1800000, 3600000, 10800000, 21600000, 43200000, 86400000};

constexpr char* delimitter = ",";
constexpr char* newline = "\r\n";

Logger::Logger() {}

Logger::Logger(VDisplay* display, int loggerStatusScreenID, int configScreenID, int sdStatusScreenID, int pinCS, MMReading* source) {

    Logger::display = display;
    Logger::loggerStatusScreenID = loggerStatusScreenID;
    Logger::sdStatusScreenID = sdStatusScreenID;
    Logger::configScreenID = configScreenID;
    Logger::source = source;
    Logger::pinCS = pinCS;
    //12 instead of 5 to re-enable one-shot settings
    Logger::menu = Menu(settingptrs, 5);

    pinMode(pinCS, OUTPUT);

    for(size_t i = 0; i < menu.getNumSettings()*sizeof(int); i++) {
        ((char*)menu.settingValues)[i] = EEPROM.read(i);
    }

    display->setCursor(0, 0, configScreenID);
    display->print(">");
    display->print(menu.getSettingName());
    display->setCursor(2, 1);
    display->print(menu.getOptionName());

    display->setCursor(0, 0, loggerStatusScreenID);
    display->print("Logged: 00:00:00");
    display->setCursor(0, 1);
    display->print("Samples: 0");

    display->setCursor(0, 0, sdStatusScreenID);
    display->print("SD: ");

}

void Logger::main() {

    if(isLogging) {

        if(millis() - timeLastLog >= samplePeriod[menu.settingValues[Settings::Sample_Rate]]) {
            timeLastLog = millis();
            if(!sdCardDetected && menu.settingValues[Settings::Output] != Output::UART_ONLY) {
                isLogging = false;
            }
            else {
                Logger::log();
            }
        }
        if(millis() - timeLastFlush > 1000 && menu.settingValues[Settings::Output] != Output::UART_ONLY) {
            file.flush();
            sdUpdate();
            timeLastFlush = millis();
        }
        if(millis() - timeLogStart >= maxDurations[menu.settingValues[Settings::Max_Duration]]) {
            toggle();
        }

    }
    if(display->getVisiblePage() == loggerStatusScreenID && isLogging) {
        if(millis() - timeRefresh > 1000) {

            char buffer[3] = "00";
            unsigned long t = (millis() - timeLogStart)/1000;

            sprintf(buffer, "%02u", t%60);
            display->setCursor(14, 0, loggerStatusScreenID);
            display->print(buffer);
            t /= 60;
            sprintf(buffer, "%02u", t%60);
            display->setCursor(11, 0);
            display->print(buffer);
            t /= 60;
            sprintf(buffer, "%02u", t);
            display->setCursor(8, 0);
            display->print(buffer);


            timeRefresh = millis();

        }
        display->setCursor(9, 1, loggerStatusScreenID);
        display->print(numSamples);
    }

}

void Logger::toggle() {

    if(!isLogging) {

        //INIT SD
        if(menu.settingValues[Settings::Output] != Output::UART_ONLY) {

            if(sdCardDetected) {
                SD.begin(pinCS);
                sprintf(filename, "%u.csv", nextFileId);
                file = SD.open(filename, FILE_WRITE);
                nextFileId++;
                timeLastFlush = millis();
                numFiles++;
                display->setCursor(numFiles == 0 ? 14 : 14 - floor(log10(numFiles)), 0, sdStatusScreenID);
                display->print("#");
                display->print(numFiles);
            }
            else {
                display->setVisiblePage(sdStatusScreenID);
                goto sd_fail;
            }
        }

        //INIT UART
        if(menu.settingValues[Settings::Output] != Output::SD_ONLY) {
            Serial.begin(baudRates[menu.settingValues[Settings::Baud_Rate]]);
            Serial.print("[Start of file]\002\n");
        }

        initLog();
        isLogging = true;

        sd_fail:
        char x;

    }else {

        if(menu.settingValues[Settings::Output] != Output::UART_ONLY) {
            //SD close file
            sdUpdate();
            file.close();
        }
        if(menu.settingValues[Settings::Output] != Output::SD_ONLY) {
            Serial.print("\003\n[End of file]");
            Serial.end();
        }


        char buffer[3] = "00";
        unsigned long t = (millis() - timeLogStart)/1000;

        sprintf(buffer, "%02u", t%60);
        display->setCursor(14, 0, loggerStatusScreenID);
        display->print(buffer);
        t /= 60;
        sprintf(buffer, "%02u", t%60);
        display->setCursor(11, 0);
        display->print(buffer);
        t /= 60;
        sprintf(buffer, "%02u", t);
        display->setCursor(8, 0);
        display->print(buffer);

        display->setCursor(9, 1);
        display->print(numSamples);


        display->setVisiblePage(loggerStatusScreenID);
        isLogging = false;

    }

}

void Logger::initLog() {

    switch(menu.settingValues[Settings::Logged_Channels]) {
        case Logged_Channels::All_Channels:
            write(colsAll_Channels);
            break;
        case Logged_Channels::V0_only:
            write(colsV0_only);
            break;
        case Logged_Channels::I0_only:
            write(colsI0_only);
            break;
        case Logged_Channels::V0_and_V1:
            write(colsV0_and_V1);
            break;
        case Logged_Channels::I0_and_I1:
            write(colsI0_and_I1);
            break;
        case Logged_Channels::V0_and_I0:
            write(colsV0_and_I0);
            break;
    }

    numSamples = 0;

    display->setCursor(0, 0, loggerStatusScreenID);
    display->print("Logged: 00:00:00");
    display->setCursor(0, 1);
    display->print("Samples: 0      ");

    timeLogStart = millis();
    timeLastLog = 0;
    timeRefresh = 0;

}

void Logger::log() {

    dtostrf((float)(millis()-timeLogStart)/1000.0, 1, 3, outputBuffer);
    write(outputBuffer);
    write(delimitter);
    switch(menu.settingValues[Settings::Logged_Channels]) {
        case Logged_Channels::All_Channels:
            dtostrf(source->v0, 1, 7, outputBuffer);
            write(outputBuffer);
            write(delimitter);
            dtostrf(source->i0, 1, 5, outputBuffer);
            write(outputBuffer);
            write(delimitter);
            dtostrf(source->v1, 1, 7, outputBuffer);
            write(outputBuffer);
            write(delimitter);
            dtostrf(source->i1, 1, 5, outputBuffer);
            write(outputBuffer);
            //sprintf(outputBuffer, "%.3f,%.7f,%.5f,%.7f,%.5f\r\n", (float)(millis()-timeLogStart)/1000.0, source->v0, source->i0, source->v1, source->i1);
            break;
        case Logged_Channels::V0_only:
            dtostrf(source->v0, 1, 7, outputBuffer);
            write(outputBuffer);
            //sprintf(outputBuffer, "%.3f,%.7f\r\n", (float)(millis()-timeLogStart)/1000.0, source->v0);
            break;
        case Logged_Channels::V0_and_V1:
            dtostrf(source->v0, 1, 7, outputBuffer);
            write(outputBuffer);
            write(delimitter);
            dtostrf(source->v1, 1, 7, outputBuffer);
            write(outputBuffer);
            //sprintf(outputBuffer, "%.3f,%.7f,%.7f\r\n", (float)(millis()-timeLogStart)/1000.0, source->v0, source->v1);
            break;
        case Logged_Channels::I0_only:
            dtostrf(source->i0, 1, 5, outputBuffer);
            write(outputBuffer);
            //sprintf(outputBuffer, "%.3f,%.5f\r\n", (float)(millis()-timeLogStart)/1000.0, source->i0);
            break;
        case Logged_Channels::I0_and_I1:
            dtostrf(source->i0, 1, 5, outputBuffer);
            write(outputBuffer);
            write(delimitter);
            dtostrf(source->i1, 1, 5, outputBuffer);
            write(outputBuffer);
            //sprintf(outputBuffer, "%.3f,%.5f,%.5f\r\n", (float)(millis()-timeLogStart)/1000.0, source->i0, source->i1);
            break;
        case Logged_Channels::V0_and_I0:
            dtostrf(source->v0, 1, 7, outputBuffer);
            write(outputBuffer);
            write(delimitter);
            dtostrf(source->i0, 1, 5, outputBuffer);
            write(outputBuffer);
            //sprintf(outputBuffer, "%.3f,%.7f,%.5f\r\n", (float)(millis()-timeLogStart)/1000.0, source->v0, source->i0);
            break;
    }

    //write(outputBuffer);
    write(newline);
    numSamples++;

}

void Logger::write(char* str) {

    switch(menu.settingValues[Settings::Output]) {
        case Output::SD_ONLY:
            //SD OUT
            file.print(str);
            break;
        case Output::UART_ONLY:
            Serial.print(str);
            break;
        case Output::SD_UART:
            Serial.print(str);
            file.print(str);
            //SD OUT
            break;
    }

}

void Logger::buttonPressed() {

    display->setTargetPage(configScreenID);
    display->clear();

    if(selectedRow) {

        menu.nextOption();

    }
    else {

        menu.nextSetting();

    }

    display->setCursor(0, 0);
    display->print(selectedRow ? " " : ">");
    display->print(menu.getSettingName());
    display->setCursor(0, 1);
    display->print(selectedRow ? "> " : "  ");
    display->print(menu.getOptionName());

}

void Logger::buttonHeld() {

    selectedRow = !selectedRow;
    display->setTargetPage(configScreenID);
    display->setCursor(0, 0);
    display->print(selectedRow ? " " : ">");
    display->setCursor(0, 1);
    display->print(selectedRow ? ">" : " ");

}

void Logger::saveSettings() {

    for(size_t i = 0; i < menu.getNumSettings()*sizeof(int); i++) {
        if(EEPROM.read(i) != ((char*)menu.settingValues)[i]) {
            EEPROM.write(i, ((char*)menu.settingValues)[i]);
        }
    }

}

void Logger::evaluateFiles() {
    
    SD.begin(pinCS);

    int currentMax = -1;
    numFiles = 0;
    totalSize = 0;
    File root = SD.open("/");
    File currentFile = root.openNextFile();

    while(currentFile) {

        char* name = currentFile.name();

        int i = 0;
        while(name[i+1] != '.') {
            if(name[i+1] == 0x00) {
                goto escape_hatch;
            }
            i++;
        }

        int x = 0;

        for(int p = 1; i >= 0; p*=10, i--) {
            x += (name[i]-48)*p;
        }
        
        currentMax = currentMax > x ? currentMax : x;
        totalSize += currentFile.size();
        numFiles++;

        escape_hatch:

        currentFile.close();
        currentFile = root.openNextFile();
    }

    getSdStatus();

    nextFileId = currentMax + 1;

    //display->setCursor(0, 1, sdStatusScreenID);
    //display->print(nextFileId);
    //display->print(".csv");

}

float Logger::getCardSize() {

    Sd2Card card;
    SdVolume volume;

    card.init(SPI_HALF_SPEED, pinCS);
    volume.init(card);
    cardSize = volume.blocksPerCluster()*volume.clusterCount()/2097152.0;
    
    return cardSize;

}

void Logger::getSdStatus() {

    display->setCursor(numFiles == 0 ? 14 : 14 - floor(log10(numFiles)), 0, sdStatusScreenID);
    display->print("#");
    display->print(numFiles);

    char buffer[8] = {0};
    char suffix[3] = {0};
    if(totalSize < 1048576) { //Less than 1MiB
        dtostrf(totalSize/1024.0, 1, 1, buffer);
        sprintf(suffix, "%s", "kB");
    }
    else if(totalSize < 1073741824) { //Less than 1GiB
        dtostrf(totalSize/1048576.0, 1, 1, buffer);
        sprintf(suffix, "%s", "MB");
    }
    else {
        dtostrf(totalSize/1073741824.0, 1, 1, buffer);
        sprintf(suffix, "%s", "GB");
    }

    display->setCursor(0, 1, sdStatusScreenID);
    display->print(buffer);
    display->print(suffix);
    display->print("/");
    dtostrf(getCardSize(), 1, 1, buffer);
    display->print(buffer);
    display->print("GB");

}

void Logger::sdUpdate() {

    unsigned long newTotalSize = totalSize + file.size();

    char buffer[8] = {0};
    char suffix[3] = {0};
    if(newTotalSize < 1048576) { //Less than 1MiB
        dtostrf(newTotalSize/1024.0, 1, 1, buffer);
        sprintf(suffix, "%s", "kB");
    }
    else if(newTotalSize < 1073741824) { //Less than 1GiB
        dtostrf(newTotalSize/1048576.0, 1, 1, buffer);
        sprintf(suffix, "%s", "MB");
    }
    else {
        dtostrf(newTotalSize/1073741824.0, 1, 1, buffer);
        sprintf(suffix, "%s", "GB");
    }

    display->setCursor(0, 1, sdStatusScreenID);
    display->print(buffer);
    display->print(suffix);
    display->print("/");
    dtostrf(cardSize, 1, 1, buffer);
    display->print(buffer);
    display->print("GB");

}



// show sd files as scrolling list
void Logger::listFiles() {
    // For time being, just overwrite SD screen
    // maybe this goes to it's own virtual screen??

    SD.begin(pinCS);

    File root = SD.open("/");
    File currentFile = root.openNextFile();
    currentFile.close();
    currentFile = root.openNextFile();

    bool x = false;

    char lines[2][17] = {0};

    display->setTargetPage(sdStatusScreenID);

    while(currentFile) {

        //display->setCursor(0, 0, sdStatusScreenID);
        //display->print(name);

        unsigned int filesize = currentFile.size();

        char buffer[8] = {0};
        char suffix[3] = {0};
        if(filesize < 1048576) { //Less than 1MiB
            dtostrf(filesize/1024.0, 1, 1, buffer);
            sprintf(suffix, "%s", "kB");
        }
        else if(filesize < 1073741824) { //Less than 1GiB
            dtostrf(filesize/1048576.0, 1, 1, buffer);
            sprintf(suffix, "%s", "MB");
        }
        else {
            dtostrf(filesize/1073741824.0, 1, 1, buffer);
            sprintf(suffix, "%s", "GB");
        }

        sprintf(lines[x], "%s %s%s", currentFile.name(), buffer, suffix);
        
        display->setCursor(0, 0);
        display->clear();
        display->print(lines[!x]);
        display->setCursor(0, 1);
        display->print(lines[x]);

        x = !x;

        //display->print(" ");
        //display->print(buffer);
        //display->print(suffix);
        
        delay(1000);
        currentFile.close();
        currentFile = root.openNextFile();
    }

    lines[x][0] = 0x00;
    display->setCursor(0, 0);
    display->clear();
    display->print(lines[!x]);
    display->setCursor(0, 1);
    display->print(lines[x]);
    delay(1000);

    display->clear();
    evaluateFiles();
    display->setCursor(0, 0, sdStatusScreenID);
    display->print("SD: ");
    display->print(digitalRead(A2) ? "Yes" : "No ");
}
