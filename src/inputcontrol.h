#ifndef _INPUTCONTROL_H
#define _INPUTCONTROL_H
#include <gpioirqt.h>
#include <encoder.h>
#include <functional>
#include <vector>
#include <mutex>
#include <thread>

#define ROTARY1_PIN1 3
#define ROTARY1_PIN2 11
#define ROTARY2_PIN1 17
#define ROTARY2_PIN2 16
#define KEY1_PIN 2
#define KEY2_PIN 15


class InputRotary : public Rotary
{
public:
    InputRotary(char pin1, char pin2);
    void setCallback(std::function<void(bool)> func);
    void update();
private:
    void callCallback(bool result);
    std::function<void(bool)> m_callback;
    std::mutex m_mutex;
};

class InputKey : public Key
{
public:
    InputKey(char pin, int debonce_ms);
    void setCallback(std::function<void()> func);
    void update();
private:
    void callCallback();
    std::function<void()> m_callback;
    int m_debonce_ms;
    std::mutex m_mutex;
    bool m_deboncing;
    bool m_stableState;
    bool m_state;
};

class InputControl
{
public:
    InputControl();
    void start();
    void update();
    void assignOnRotary(int rotary, std::function<void(bool)> func);
    void assignOnKeyPressed(int key, std::function<void()> func);
private:
    std::vector<InputRotary*> rotVec;
    std::vector<InputKey*> keyVec;
};


#endif