#include "displayDriver.h"
#include "oled-exp.h"
#include <thread>
#include <inputcontrol.h>
using namespace std;

void functionToThread(){
  system("mpg123 http://195.93.246.231:80/voicerushi ");
}

int main(){
  InputControl input;
  input.start();

  //dis = new Display;



  //dis->draw_current_menu();

  return 0;
}
