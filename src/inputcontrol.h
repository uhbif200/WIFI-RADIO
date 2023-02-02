#ifndef _INPUTCONTROL_H
#define _INPUTCONTROL_H
#include <gpioirqt.h>
#include <encoder.h>
#include <functional>
#include <vector>

#define ROTARY1_PIN1 3
#define ROTARY1_PIN2 11
#define ROTARY2_PIN1 17
#define ROTARY2_PIN2 16
#define KEY1_PIN 2
#define KEY2_PIN 15


class InputControl
{
public:
    InputControl();
    void start();
    void update();
    void assignOnRotary(int rotary, std::function<void(bool)> func);
    void assignOnKeyPressed(int key, std::function<void()> func);
private:
    std::vector<std::pair<Rotary, std::function<void(bool)>>> rotariesVec;
    std::vector<std::pair<Key, std::function<void()>>> keysVec;
};


#endif