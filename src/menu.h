#ifndef _MENU_H
#define _MENU_H

struct Setting {
    char* name;
    char** options;
};

struct CurrentSetting {
    char* setting;
    char* option;
};

class Menu {

    public:

        Menu();
        Menu(Setting* settingptrs, int numSettings);

        char* getSettingName();
        char* getSettingName(int setting);

        CurrentSetting nextSetting();
        CurrentSetting previousSetting();

        char* nextOption();
        char* previousOption();

        char* getOptionName();
        char* getOptionName(int setting);

        int getSettingValue(int setting);

        int getNumSettings();

        int* settingValues;
        Setting* settingptrs;

    private:

        int selectedSetting = 0;
        int numSettings;

        int* numOptions;

        static char errorString[17];

};

#endif