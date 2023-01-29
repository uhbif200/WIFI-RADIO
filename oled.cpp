#include <iostream>
#include <unistd.h>
#include <onion-i2c.h>
#include "gpio.h"
#include "oled-exp.h"
using namespace std;


int main(int argc, char const *argv[]) {
  oledDriverInit();
  oledClear();

  cout <<"lol";
  return 0;
}
