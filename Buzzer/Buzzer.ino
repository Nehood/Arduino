int BUZZER = 9;

void setup() {
  pinMode(BUZZER, OUTPUT);

}

void loop() {
//  digitalWrite(BUZZER, i);
//  delay(1000);
//  digitalWrite(BUZZER, LOW);
//  delay(1000);
//  i+= 10;
for (int i=0;i<400;i+=10)
{
  digitalWrite(BUZZER, HIGH);
  delay(50);
  //digitalWrite(BUZZER, LOW);
  //delay(800-(2*i));
}
}
