byte switchRightDown = 1;
byte switchLeftDown = 2;
byte switchRightUp = 3;
byte switchLeftUp = 4;
////////////////////////
byte diodeRightDown = 5;
byte diodeLeftDown = 6;
byte diodeRightUp = 7;
byte diodeLeftUp = 8;
////////////////////////
byte switchStart = 9;
byte buzzer = 10;
////////////////////////
byte tab[64];
byte licznik;    ///ile pol tablicy mamy zajetych
byte randomNumber;
bool gameOn;


void setup() {
  pinMode(switchRightDown, INPUT_PULLUP);
  pinMode(switchLeftDown, INPUT_PULLUP);
  pinMode(switchRightUp, INPUT_PULLUP);
  pinMode(switchLeftUp, INPUT_PULLUP);
  pinMode(diodeRightDown, OUTPUT);       // ogolny uklad(dla diod i switchy):
  pinMode(diodeLeftDown, OUTPUT);       //  D8  D7        S4  S3   
  pinMode(diodeRightUp, OUTPUT);       //  D6  D5        S2  S1
  pinMode(diodeLeftUp, OUTPUT);
  pinMode(switchStart, INPUT_PULLUP);
  pinMode(buzzer, OUTPUT);
  randomSeed(analogRead(0));
  gameOn = false;
}

void loop() {
  if (gameOn == false) {
    while (digitalRead(switchStart) != LOW);
    gameOn = true;
    licznik = 0;
  }

  //////////////////////////
  
  randomNumber = random(4);
  tab[licznik] = randomNumber + 1;
  for (byte i=0;i<licznik;i++) {
    digitalWrite(tab[i]+4, HIGH);
    delay(1000);
    digitalWrite(tab[i]+4, LOW);
    delay(100);
  }

  for (byte i=0;i<licznik;i++) {
    while ((digitalRead(switchRightDown) != LOW) && (digitalRead(switchLeftDown) != LOW)
      && (digitalRead(switchRightUp) != LOW) && (digitalRead(switchLeftUp) != LOW));
        if (digitalRead(tab[i]) == LOW) {
          digitalWrite(tab[i]+4, HIGH);
          delay(300);
          digitalWrite(tab[i]+4, LOW);
          delay(100);
        }
        else {
          digitalWrite(buzzer, HIGH);
          delay(4000);
          digitalWrite(buzzer, LOW);
          for (byte i=0;i<licznik;i++)
          {
            tab[i] = (char)0;
          }
          licznik = 0;
          gameOn = false;        
          break;
        }
  }
  licznik++;
}




