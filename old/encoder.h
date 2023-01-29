#ifndef _ENCODER_CPP_
#define _ENCODER_CPP_

#include <iostream>
#include <unistd.h>
#include "gpio.h"
#include "display.h"

// Constants

const uint8_t CLK_PIN = 2;
const uint8_t DT_PIN = 11;
const uint8_t SW_PIN = 3;
const uint8_t LED_RIGHT_PIN = 19;
const uint8_t LED_LEFT_PIN = 18;

//Functions

int init_encoder();
int check_sw(Display &displ);


#endif
