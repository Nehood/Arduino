void setup() {
  Serial.begin(9600);
  Serial.println("Zaczynamy program");

  pinMode(8, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(4, INPUT_PULLUP);

  digitalWrite(8, LOW);
  digitalWrite(10, LOW);
}

void loop() {
  if (digitalRead(4) == LOW) {
    digitalWrite(8, HIGH);
    digitalWrite(10, LOW);
  }else{
    digitalWrite(8, LOW);
    digitalWrite(10, HIGH);
    Serial.println("ALARM! ALARM!");
  }

  while (digitalRead(4) == HIGH) {
    delay(25);
  }
}
