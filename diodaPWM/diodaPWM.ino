int wypelnienie = 0;
int zmiana = 5;

void setup() {
  pinMode(9, OUTPUT);

}

void loop() {
  for (int i=0;i<52;i++)
  {
    analogWrite(9, wypelnienie);
    wypelnienie += zmiana;
    delay(20);
  }
  for (int i=0;i<52;i++)
  {
    wypelnienie -= zmiana;
    analogWrite(9, wypelnienie);
    delay(20);
  }
}
