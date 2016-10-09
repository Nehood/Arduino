String odebraneDane = "";
int zielona = 8;
int zolta = 9;
int czerwona = 10;
bool zielonaOn = false;
bool zoltaOn = false;
bool czerwonaOn = false;

void setup() {
  Serial.begin(9600);
  pinMode(zielona, OUTPUT);
  pinMode(zolta, OUTPUT);
  pinMode(czerwona, OUTPUT);

  digitalWrite(zielona, LOW);
  digitalWrite(zolta, LOW);
  digitalWrite(czerwona, LOW);
}

void loop() {
  if (Serial.available() > 0) {
    odebraneDane = Serial.readStringUntil('\n');
    Serial.println("Nadeszlo: " + odebraneDane);
      if (odebraneDane == "zielona") {
        if (zielonaOn == false) {
          digitalWrite(zielona, HIGH);
          zielonaOn = true;
        }
        else {
          digitalWrite(zielona, LOW);
          zielonaOn = false;
        }
      
    }
    else if (odebraneDane == "zolta") {
      if (zoltaOn == false) {
          digitalWrite(zolta, HIGH);
          zoltaOn = true;
        }
        else {
          digitalWrite(zolta, LOW);
          zoltaOn = false;
        }
    }
    else if (odebraneDane == "czerwona") {
      if (czerwonaOn == false) {
          digitalWrite(czerwona, HIGH);
          czerwonaOn = true;
        }
        else {
          digitalWrite(czerwona, LOW);
          czerwonaOn = false;
        }
    }
    else {
      Serial.println("Bledne dane!");
    }
  }

}
