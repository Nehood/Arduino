#include <OneWire.h>
#include <DS18B20.h>
//termometr:
byte PIN = 4;
byte address[8] = {0x28, 0xFF, 0xD5, 0xDF, 0x2, 0x15, 0x2, 0xBF};
//czujnik odleglosci:
byte Trig = 3;
byte Echo = 2;
byte BUZZER = 7;
int distance;
long duration = 0;
//znow termometr:
OneWire onewire(PIN);
DS18B20 sensors(&onewire);
void setup() {
  while (!Serial);
  Serial.begin(9600);
  //czujnik odleglosci
  pinMode(Trig, OUTPUT);
  pinMode(Echo, INPUT);
  pinMode(BUZZER, OUTPUT);
//termometr
  sensors.begin();
  sensors.request(address);
}

void loop() {
  //temperatura
  if (sensors.available()){
  float temperature = sensors.readTemperature(address);

  Serial.print(temperature);
  Serial.println(F(" 'C"));

  sensors.request(address);
 }
 //czujnik odleglosci
  digitalWrite(Trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(Trig, LOW);

  duration = pulseIn(Echo, HIGH);

  distance = duration/58;

  if (distance < 2 || distance > 200) Serial.println("Poza zasiegiem!");
  else {
    Serial.print("Odleglosc: ");
    Serial.print(distance);
    Serial.println(" cm");
  }
  delay(500);
digitalWrite(BUZZER, HIGH);
delay(100);
digitalWrite(BUZZER, LOW);
delay(4*distance);
}
