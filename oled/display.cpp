#include "display.h"
using namespace std;


    Display::Display(){
      oledDriverInit();
      oledClear();
      printf("%i\n", oledCheckInit() );
      printf("init succesful\n");
    }

    int Display::drawSubMenu(){
      //clrscr();
      drawText(0, 3, submenu[0], 0);
      for (int i = 1; i < submenu.size(); i++){
        //char text[30];
        string text = submenu[i];

        if(i == this->selected){
            text.insert(0,1,'>');
        }
        if(i == this->choosen){
            text.insert(0,1,'o');
        }
        drawText(i,3,text,0);
      }
    }

    int Display::clrscr(){
      oledClear();
    }

    int Display::refresh(){

    }

    int Display::drawText(int x, int y, string text, int font){
      oledSetCursor(x,y);
      char text2[30];
      strcpy(text2, text.c_str());
      oledWrite(text2);
    }

    int Display::right(){
      if(this->selected < submenu.size()-1){
        this->selected += 1;
        drawSubMenu();
      }
    }

    int Display::left(){
      if(this->selected > 1){
        this->selected -= 1;
        drawSubMenu();
      }
    }

    void Display::play(){
      system("aplay /root/EXP.wav");
    }
