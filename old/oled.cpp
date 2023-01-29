#include <iostream>
#include "gpio.h"
#include "oled-exp.h"
using namespace std;
char lala[] = "asdfasdf";

int main(int argc, char const *argv[]) {
  oledDriverInit();
  oledSetCursor(3,3);
  oledClear();
  oledSetCursor(5,6);
  oledWrite(lala);
  oledSetCursor(7,8);
  oledWrite(lala);
  oledDisplay();
  cout <<"lol";
  return 0;
}
