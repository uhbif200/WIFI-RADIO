#include "gpioirqlib.c"
#include "encoder.cpp"
#include <iostream>

using namespace std;

/*int encoder(){
  cout<<"tratata"<<endl;
}
*/

int main(){
  init_encoder();
  start_irq(2,check_sw);
}
