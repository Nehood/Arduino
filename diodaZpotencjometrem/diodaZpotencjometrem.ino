int odczytanaWartosc = 0;
void setup() {
  pinMode(2, OUTPUT);

}

void loop() {
  odczytanaWartosc = analogRead(A5);
  digitalWrite(2, HIGH);
  delay(odczytanaWartosc);
  digitalWrite(2, LOW);
  delay(odczytanaWartosc);
}
