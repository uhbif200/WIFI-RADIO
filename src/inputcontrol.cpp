#include <inputcontrol.h>
#include <iostream>

InputRotary::InputRotary(char pin1, char pin2):
    Rotary(pin1, pin2)
{
}

void InputRotary::setCallback(std::function<void(bool)> func)
{
    std::lock_guard<std::mutex> lock(m_mutex);
    m_callback = func;
}

void InputRotary::callCallback(bool result)
{
    std::lock_guard<std::mutex> lock(m_mutex);
    if(!m_callback){
        std::cout <<"Rotary no callback!" <<std::endl;
        return;
    }

    m_callback(result);
}

void InputRotary::update()
{
    char result = process();
    if(result == DIR_CW)
        callCallback(true);
    else if(result == DIR_CCW)
        callCallback(false); 
}

InputKey::InputKey(char pin, int debonce_ms):
    Key(pin),
    m_debonce_ms(debonce_ms),
    m_deboncing(false),
    m_stableState(false),
    m_state(false)
{
}

void InputKey::setCallback(std::function<void()> func)
{
    std::lock_guard<std::mutex> lock(m_mutex);
    m_callback = func;
}

void InputKey::callCallback()
{
    std::lock_guard<std::mutex> lock(m_mutex);
    if(!m_callback){
        std::cout <<"Input key no callback!" <<std::endl;
        return;
    }

    m_callback();
}

void InputKey::update()
{
    m_state = process();
    if(m_state != m_stableState){
        if(!m_deboncing){
            m_deboncing = true;
            std::thread th([this](){
                std::this_thread::sleep_for(std::chrono::milliseconds(m_debonce_ms));
                m_deboncing = false;
                if(m_state != m_stableState){
                    m_stableState = m_state;
                    if(!m_state)
                        callCallback();
                }
            });
            th.detach();
        }
    }
}


InputControl::InputControl() : 
    rotVec{ new InputRotary(ROTARY1_PIN1, ROTARY1_PIN2),
            new InputRotary(ROTARY2_PIN1, ROTARY2_PIN2)},
    keyVec{ new InputKey(KEY1_PIN, 50), 
            new InputKey(KEY2_PIN, 50)}
{
}

void InputControl::start()
{
    int size = 6;
    int gpioarr[size] = {ROTARY1_PIN1, ROTARY1_PIN2, ROTARY2_PIN1, ROTARY2_PIN2, KEY1_PIN, KEY2_PIN};
    start_irq(gpioarr, size, std::function<void()>([this](){update();}));
} 

void InputControl::update()
{
    for(auto& rotary : rotVec){
        rotary->update();
    }

    for(auto& key : keyVec){
        key->update();
    }
}

void InputControl::assignOnRotary(int rotary, std::function<void(bool)> func)
{
    if(rotary < 0 || rotary > rotVec.size())
        return;
    rotVec[rotary]->setCallback(func);
}

void InputControl::assignOnKeyPressed(int key, std::function<void()> func)
{
    if(key < 0 || key > keyVec.size())
        return;
    keyVec[key]->setCallback(func);
}