#include "menu.h"
#include <stdlib.h>

char Menu::errorString[17] = "*StringNotFound*";

Menu::Menu() {}

Menu::Menu(Setting* settingptrs, int numSettings) {

    Menu::settingptrs = settingptrs;
    Menu::numSettings = numSettings;
    
    settingValues = (int*)malloc(sizeof(int)*numSettings);
    for(int i = 0; i < numSettings; i++) {
        settingValues[i] = 0;
    }

    numOptions = (int*)malloc(sizeof(int)*numSettings);
    for(int i = 0; i < numSettings; i++) {
        int j = 0;
        while(settingptrs[i].options[j] != 0x00) {
            j++;
        }
        numOptions[i] = j;
    }

}

char* Menu::getSettingName() {

    return getSettingName(selectedSetting);

}

char* Menu::getSettingName(int setting) {
    
    if(setting >= numSettings) {
        return errorString;
    }

    return settingptrs[setting].name;

}

CurrentSetting Menu::nextSetting() {

    selectedSetting = selectedSetting + 1 >= numSettings ? 0 : selectedSetting + 1;

    return {
        settingptrs[selectedSetting].name,
        settingptrs[selectedSetting].options[settingValues[selectedSetting]]
    };

}

CurrentSetting Menu::previousSetting() {

    selectedSetting = selectedSetting <= 0 ? numSettings - 1 : selectedSetting - 1;

    return {
        settingptrs[selectedSetting].name,
        settingptrs[selectedSetting].options[settingValues[selectedSetting]]
    };

}

char* Menu::nextOption() {

    settingValues[selectedSetting] = settingValues[selectedSetting] + 1 >= numOptions[selectedSetting] ? 0 : settingValues[selectedSetting] + 1;

    return settingptrs[selectedSetting].options[settingValues[selectedSetting]];

}

char* Menu::previousOption() {

    settingValues[selectedSetting] = settingValues[selectedSetting] <= 0 ? numOptions[selectedSetting] - 1 : settingValues[selectedSetting] - 1;

    return settingptrs[selectedSetting].options[settingValues[selectedSetting]];

}

char* Menu::getOptionName() {
    
    return getOptionName(selectedSetting);

}

char* Menu::getOptionName(int setting) {

    if(setting >= numSettings) {
        return errorString;
    }

    return settingptrs[setting].options[settingValues[setting]];

}

int Menu::getSettingValue(int setting) {

    if(setting >= numSettings) {
        return -1;
    }

    return settingValues[setting];

}

int Menu::getNumSettings() {

    return numSettings;

}
