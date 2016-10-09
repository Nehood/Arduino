int value = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Zaczynamy:");
}

void loop() {
  // put your main code here, to run repeatedly:
  value = analogRead(A4);
  Serial.println(0.0049 * value);
  delay(500);
}
