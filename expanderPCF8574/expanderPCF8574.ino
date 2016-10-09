#include <Wire.h>
#include <PCF8574.h>

PCF8574 expander;
void setup() {
  expander.begin(0x20);
  expander.pinMode(2, OUTPUT);
  expander.pinMode(4, OUTPUT);
}

void loop() {
  expander.digitalWrite(2, HIGH);
  delay(1000);
  expander.digitalWrite(2, LOW);
  delay(1000);
  expander.digitalWrite(4, HIGH);
  delay(1000);
  expander.digitalWrite(4, LOW);
  delay(1000);
}
