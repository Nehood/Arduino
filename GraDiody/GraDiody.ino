int odczytanaWartosc = 0;         //wartosc potencjometru
String odebraneDane = "";         //wyslane przez uzytkownika dane
int odebranaLiczba = 0;
int proby = 2;                  //licznik gier
bool od_nowa = true;              //kontynuujemy, czy od nowa
void setup() {
  Serial.begin(9600);
  pinMode(6, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(2, INPUT_PULLUP);
  Serial.println("Zaczynamy zabawe!");
}

void loop() {
  if (od_nowa == true){     //poczatek gry lub od nowa
    proby = 2;
    digitalWrite(6, LOW);
    digitalWrite(8, LOW);
    digitalWrite(10, LOW);
    while(!Serial) delay(10);     //czekamy na otwarcie terminala
    Serial.println("Przekrec potencjometr i nacisnij przycisk");
    while (digitalRead(2) == LOW) delay(20);  //czekamy na zwolnienie przyciku
    while (digitalRead(2) == HIGH) delay(20); //czekamy na wcisniecie przycisku
    odczytanaWartosc = analogRead(A5);  //odczyt z potencjometru
    Serial.println(odczytanaWartosc);
    Serial.println("Podaj liczbe:");
  }
  while (Serial.available() == 0);  //czekamy na podanie liczby
  odebraneDane = Serial.readStringUntil('\n');
  odebranaLiczba = odebraneDane.toInt();
  Serial.println(odebranaLiczba);
  if (max(odczytanaWartosc,odebranaLiczba) - //sprawdzamy roznice
  min(odczytanaWartosc,odebranaLiczba) < 50)  {
    Serial.println("Trafiony!");
    digitalWrite(10, HIGH);
    digitalWrite(8, LOW);
    od_nowa = true;
    Serial.println("Jesli chcesz zagrac - nacisnij przycisk");
    while (digitalRead(2) == HIGH) delay(20); //czekamy na przycisk
  }
  else {  //podana liczba jest rozna o ponad 50
    if (proby > 0) {
      od_nowa = false;  //nie zaczynamy od nowa
      digitalWrite(8, HIGH);
      Serial.println("Nie trafiles. ilosc prob: ");
      Serial.println(proby);
      Serial.flush();
      Serial.println("Podaj kolejna liczbe:");
      proby--;
      while(Serial.available() == 0); //czekamy na kolejna liczbe
    }
    else {  //koniec prob
      digitalWrite(6, HIGH);
      digitalWrite(8, LOW);
      Serial.println("Przegrales, aby zagrac ponownie - nacisnij przycisk");
      od_nowa = true;
      while (digitalRead(2) == HIGH) delay(20);
    }
  }
  delay(5);
}
//  if (digitalRead(2) == LOW) {
//    
//    digitalWrite(6, LOW);
//    digitalWrite(8, LOW);
//    digitalWrite(10, LOW);
//    odczytanaWartosc = analogRead(A5);
//    Serial.println(odczytanaWartosc);
//    while (licznik < 3)
//    {
//      Serial.flush();
//    Serial.println("Podaj Liczbe:");
//    while (Serial.available() == 0);  
//    if (Serial.available() > 0) {
//      odebraneDane = Serial.read();
//      if (max(odczytanaWartosc,odebraneDane) - min(odczytanaWartosc,odebraneDane)
//      < 50) {
//        Serial.println("Wygrana!");
//        digitalWrite(10, HIGH);
//        digitalWrite(6, LOW);
//        digitalWrite(8, LOW);
//        Serial.flush();
//      }
//      else {
//        digitalWrite(10, LOW);
//        digitalWrite(6, LOW);
//        digitalWrite(8, HIGH);
//        licznik++;
//      }
//    } 
//    }
//        digitalWrite(10, LOW);
//        digitalWrite(6, HIGH);
//        digitalWrite(8, LOW);
//    }

