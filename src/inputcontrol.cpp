#include <inputcontrol.h>
#include <iostream>

InputControl::InputControl() : 
    rotariesVec{
    std::make_pair(Rotary(ROTARY1_PIN1, ROTARY1_PIN2), [](bool dir){
        std::cout <<"Rotary1 rotated " <<dir <<std::endl;
    }),
    std::make_pair(Rotary(ROTARY2_PIN1, ROTARY2_PIN2), [](bool dir){
        std::cout <<"Rotary2 rotated " <<dir <<std::endl;
    })},
    keysVec{
    std::make_pair(Key(KEY1_PIN), [](){
        std::cout <<"Key1 pressed" <<std::endl;
    }),
    std::make_pair(Key(KEY2_PIN), [](){
        std::cout <<"Key2 pressed" <<std::endl;
    })}
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
    for(auto& rotary : rotariesVec){
        char result = rotary.first.process();
        if(result == DIR_CW){
            rotary.second(true);
        }
        else if(result == DIR_CCW){
            rotary.second(false);
        }
    }

    for(auto& key : keysVec){
        char result = key.first.process();
        if(result == 1){
            key.second();
        }
    }
}

void InputControl::assignOnRotary(int rotary, std::function<void(bool)> func)
{

}

void InputControl::assignOnKeyPressed(int key, std::function<void()> func)
{

}