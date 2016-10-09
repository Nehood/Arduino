int odczytanaWartosc = 0;
float napiecie = 0;
void setup() {
  Serial.begin(9600);

}

void loop() {
  odczytanaWartosc = analogRead(A5);
  napiecie = (5.0/1023.0) * odczytanaWartosc;
  Serial.println(napiecie);
  delay(200);
}
