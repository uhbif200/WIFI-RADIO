#include "encoder.h"

using namespace std;


int dt, sw0, clk0;
int nsw, nclk;

int init_encoder(){
    Gpio::initialize();
    Gpio::pinMode(SW_PIN, GPD_INPUT);
    //Gpio::pinMode(CLK_PIN, GPD_INPUT);
    //Gpio::pinMode(LED_RIGHT_PIN, GPD_OUTPUT);
    //Gpio::pinMode(LED_LEFT_PIN, GPD_OUTPUT);
    cout <<"init_encoder succesful"<<endl;
}

int check_sw(Display &displ){
    nsw = Gpio::digitalRead(SW_PIN);
    nclk = Gpio::digitalRead(CLK_PIN);
    cout <<nclk <<" " <<nsw <<endl;
    if(nclk != nsw){
        cout <<"rotate left" <<endl;
        displ.left();
    }
    else{
        cout <<"rotate right" <<endl;
        displ.right();
    }
}

/* int main() {
    Gpio::initialize();

    // set the pin mode to output, so that we can digitalWrite() it
    //Gpio::pinMode(DT_PIN, GPD_INPUT);
    Gpio::pinMode(SW_PIN, GPD_INPUT);
    Gpio::pinMode(CLK_PIN, GPD_INPUT);
    Gpio::pinMode(LED_RIGHT_PIN, GPD_OUTPUT);
    Gpio::pinMode(LED_LEFT_PIN, GPD_OUTPUT);
    // by the default our led is set to be on
    bool ledRight, ledLeft = false;
    //dt = Gpio::digitalRead(DT_PIN);
    sw0 = Gpio::digitalRead(SW_PIN);
    clk0 = Gpio::digitalRead(CLK_PIN);
    int sw = sw0;
    int clk = clk0;

    while (true) {

        nsw = Gpio::digitalRead(SW_PIN);
        nclk = Gpio::digitalRead(CLK_PIN);
        if(clk0 != nclk && clk == clk0) {
            //dt = Gpio::digitalRead(DT_PIN);
            if(nclk == nsw){
                cout <<"rotate right" <<endl;
                ledRight = !ledRight;
                Gpio::digitalWrite(LED_RIGHT_PIN, ledRight);
                usleep(50 * 1000);
            }
            else{
                cout <<"rotate left" <<endl;
                ledLeft = !ledLeft;
                Gpio::digitalWrite(LED_LEFT_PIN, ledLeft);
                usleep(50 * 1000);
            }


            ledLeft = false;
            ledRight = false;
            Gpio::digitalWrite(LED_RIGHT_PIN, ledRight);
            Gpio::digitalWrite(LED_LEFT_PIN, ledLeft);

        }
        clk = nclk;
    }
}
*/
