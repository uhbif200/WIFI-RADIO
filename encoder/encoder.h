/*
 * Rotary encoder library for ONION.
 */

#ifndef encoder_h
#define encoder_h

//#include "Arduino.h"
#include "gpio.h"
#include <iostream>
using namespace std;

// Enable this to emit codes twice per step.
//#define HALF_STEP

// Enable weak pullups
//#define ENABLE_PULLUPS

// Values returned by 'process'
// No complete step yet.
#define DIR_NONE 0x0
// Clockwise step.
#define DIR_CW 0x10
// Anti-clockwise step.
#define DIR_CCW 0x20

class Rotary
{
  public:
    Rotary(char, char);
    // Process pin(s)
    unsigned char process();
  private:
    unsigned char state;
    int pin1;
    int pin2;
};

#endif
