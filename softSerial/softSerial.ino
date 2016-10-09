#include <SoftwareSerial.h>
SoftwareSerial mySerial(10,11);

void setup() {
  pinMode(10, INPUT);
  pinMode(11, OUTPUT);
  Serial.begin(57600);
  while (!Serial){
    
  }
  Serial.println("Zaczynamy zabawe");
  while (!mySerial){
    
  }
  mySerial.begin(9600);
  mySerial.println("Ja tez wkraczam do akcji");
}

void loop() {
  // put your main code here, to run repeatedly:
  char someChar = mySerial.read();
  // print out the character:
  mySerial.print(someChar);
}
