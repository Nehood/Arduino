#include <SoftwareSerial.h>
SoftwareSerial esp8266(2,3);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  esp8266.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:

}
