
#include "Arduino.h"
#include "SdCard.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wwrite-strings"


SdCard::SdCard() {
    // Set CS pin to output
    pinMode(SdCard::pinCS, OUTPUT);


    if (!SD.begin(pinCS)) {
        // initialization failed!
        return;
    }
    // initialization done.
}
/*
SdCard::SdCard(Stream *streamObject) {


}
*/
void SdCard::TestWriteFile() {
    File myFile;

    myFile = SD.open("Howdy.txt", FILE_WRITE);

    if (myFile) {
        myFile.println("If you like chEEse, you'll love these!");
        // close the file:
        myFile.close();
    } else {
        // if the file didn't open, print an error:
        
    }
}




#pragma GCC diagnostic pop
