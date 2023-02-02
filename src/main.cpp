#include "displayDriver.h"
#include "oled-exp.h"
#include <thread>
#include <inputcontrol.h>
using namespace std;

int main(){
  InputControl input;
  
  input.assignOnRotary(0, std::function<void(bool)>([](bool dir){
    std::cout <<"Rotor 0 rotated " <<dir <<std::endl;
  }));

  input.assignOnRotary(1, std::function<void(bool)>([](bool dir){
    std::cout <<"Rotor 1 rotated " <<dir <<std::endl;
  }));

  input.start();

  //dis = new Display;
  //dis->draw_current_menu();

  return 0;
}
