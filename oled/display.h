#ifndef _DISPLAY_CPP_
#define _DISPLAY_CPP_

#include <thread>
#include <string>
#include <cstring>
#include <vector>
#include "oled-exp.h"
#include "onion-i2c.h"
#include <iostream>

using namespace std;

class Display{
private:
    vector<string> submenu = {"Menu:", "Source", "Equalizer", "Settings", "Alarm", "Hide", "Shutdown"};
    uint8_t source_choose = 0;
    vector<string> submenu_source = {"Source:", "PlayList", "Dir", "Other", "Back"};
    vector<string> submenu_equalizer = {"Equalizer:", "Rock", "Pop", "Classic", "Jaz", "Off", "Back"};
    uint8_t equalizer_choose = 0;
    vector<string> submenu_settings = {"Settings:", "Time", "Network", "Back"};
    vector<string> submenu_alarm = {"Alarm:", "Alarm 1", "Alarm 2", "Alarm 3", "Alarm 4", "Alarm 5", "Back"};
    int selected = 1;
    int choosen = 5;
public:
    Display();
    int drawSubMenu();
    int clrscr();
    int refresh();
    int drawText(int x, int y, string text, int font);
    int right();
    int left();
    void play();
};


#endif
