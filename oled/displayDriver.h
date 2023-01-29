#ifndef _displayDriver_
#define _displayDriver_

//#include <windows.h>
#include <iostream>
#include <vector>
#include <string>
#include "oled-exp.h"
#include "onion-i2c.h"
#include <thread>
#include <fstream>

using namespace std;

class Display;
class MenuItem;

typedef int(Display::*fint_t)(vector<MenuItem*>& new_menu);         // указателт на методы
typedef void(Display::*fint_text)(string text);
typedef void(Display::*fint_play)();

enum playing{ nothing,aplay,mpg123,moc };



vector<MenuItem*> radioParcer(string &inputFileName);
MenuItem* parcerMenuFormer(vector<string> &strok);


class MenuItem{
public:
    virtual void doStaff(Display* dis);
    vector<MenuItem*>* arg;
    string text;
    int funct;
};

class MenuItemChanger : public MenuItem{
public:
    fint_t funct;
    vector<MenuItem*>* arg;
    void doStaff(Display* dis);
};

class MenuItemSyOut : public MenuItem{
public:
    fint_text funct;
    string arg;
    void doStaff(Display* dis);
};


class MenuItemPlay : public MenuItem{
public:
    fint_play funct;
    void doStaff(Display* dis);
};




class Factory{
public:
   //virtual MenuItem* createMenuItem(string text, fint_t funct, vector<MenuItem*>* menu_ptr);
   //virtual MenuItem* createMenuItem(string text, fint_text funct, string out);
   //virtual MenuItem* createMenuItem(string text, fint_play funct);
};

class ChangerFactory : public Factory{
public:
    MenuItem* createMenuItem(string text, fint_t funct, vector<MenuItem*>* menu_ptr);
};

class SysOutFactory : public Factory{
public:
    MenuItem* createMenuItem(string text, fint_text funct, string out);
};

class PlayFactory : public Factory{
public:
    MenuItem* createMenuItem(string text, fint_play funct);
};

class Display{
private:
    vector<MenuItem*> submenu;
    vector<MenuItem*> submenu_source;
    vector<MenuItem*> submenu_settings;
    vector<MenuItem*> submenu_equalizer;
    vector<MenuItem*> submenu_alarm;

    vector<MenuItem*> submenu_radio_urls;


    vector<MenuItem*>* current_menu = &submenu_radio_urls;


    int radio_is_playing = 0;

    int display_size = 7;
    int source_choose = 0;
    int equalizer_choose = 0;
    int selected = 1;
    int choosen = 5;


    int prew_first_row = 1;
    int prew_selected = 1;

public:
    MenuItem *last_radio_play = nullptr;
    Display();
    playing program_playing_now = nothing;
    int change_menu(vector<MenuItem*>& new_menu);
    void delai_cheta(string text);
    int key_pressed();
    int draw_current_menu();
    int clrscr();
    int refresh();
    int draw_text(int x, int y, string &text, int font = 0);
    int right();
    int left();
    void play();

    void pause_key_pressed();

    void play_radio(string text);

};


#endif
