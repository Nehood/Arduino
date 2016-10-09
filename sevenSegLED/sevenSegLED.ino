#include <SevenSeg.h>

SevenSeg disp(11,7,3,5,6,10,2);
const int numOfDigits=1;
int digitPins[numOfDigits] = {12};

void setup() {
  disp.setDigitPins(numOfDigits,digitPins);

}

void loop() {

 disp.write(5);

}
