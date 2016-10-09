byte licznik;

void setup() {
  Serial.begin(9600);
  licznik = 220;
}

void loop() {
  Serial.println(licznik);
  licznik++;
  delay(100);

}
