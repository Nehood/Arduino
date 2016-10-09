#include <OneWire.h>
#include <DS18B20.h>

byte PIN = 2;
byte address[8] = {0x28, 0xFF, 0xD5, 0xDF, 0x2, 0x15, 0x2, 0xBF};

OneWire onewire(PIN);
DS18B20 sensors(&onewire);
void setup() {
  while (!Serial);
  Serial.begin(9600);

  sensors.begin();
  sensors.request(address);
}

void loop() {
 if (sensors.available()){
  float temperature = sensors.readTemperature(address);

  Serial.print(temperature);
  Serial.println(F(" 'C"));

  sensors.request(address);
 }

}
