#include "displayDriver.h"
#include "oled-exp.h"
#include "gpioirqt.h"
#include "encoder.h"
#include <thread>
using namespace std;

Rotary* rotary1;
Rotary* rotary2;
Key* key1;
Key* key2;
unsigned char controlKeyPrev;
unsigned char musicKeyPrev;
unsigned char control;
unsigned char volume;
unsigned char controlKey;
unsigned char musicKey;
Display* dis;


void update(){
  control = rotary1->process();
  volume = rotary2->process();
  controlKey = key1->process();
  musicKey = key2->process();


  if(controlKey != controlKeyPrev && controlKey == 0)
    dis->key_pressed();
  controlKeyPrev = controlKey;

  if(musicKey != musicKeyPrev && musicKey == 0){
    dis->pause_key_pressed();
    usleep(1000);
  }


  musicKeyPrev = musicKey;

  if (control == DIR_CW) {
    dis->right();
  } else if (control == DIR_CCW) {
    dis->left();
  }

  volume == DIR_CW ? system("amixer set Speaker 5%+") : 0;
  volume == DIR_CCW ? system("amixer set Speaker 5%-") : 0;

}


void functionToThread(){
  system("mpg123 http://195.93.246.231:80/voicerushi ");
}

int main(){

  dis = new Display;

  rotary1 = new Rotary(3,11);
  rotary2 = new Rotary(17,16);
  key1 = new Key(2);
  key2 = new Key(15);
  controlKeyPrev = 1;
  musicKeyPrev = 1;

  dis->draw_current_menu();

  int size = 6;
  int gpioarr[size] = {3,11,17,16,2,15};
  start_irq(gpioarr, size, update);
}
