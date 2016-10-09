int odczytanaWartosc = 0;
 
void setup() {
  Serial.begin(9600);
  pinMode(8, OUTPUT); //Konfiguracja wyjść pod diody LED
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
}
 
void loop() {
  odczytanaWartosc = analogRead(A5);//Odczytanie wartości z ADC 
  Serial.println(odczytanaWartosc);  
  odczytanaWartosc = map(odczytanaWartosc, 0, 1023, 1, 5);//Przeskalowanie wartości
  
  if (odczytanaWartosc == 1) { //Pierwszy zakres
      digitalWrite(8, HIGH); 
      digitalWrite(9, LOW); 
      digitalWrite(10, LOW); 
      digitalWrite(11, LOW); 
      digitalWrite(12, LOW); 
  } else if (odczytanaWartosc == 2) { //Drugi zakres
      digitalWrite(8, LOW); 
      digitalWrite(9, HIGH); 
      digitalWrite(10, LOW); 
      digitalWrite(11, LOW); 
      digitalWrite(12, LOW);       
  } else if (odczytanaWartosc == 3) {  //Trzeci zakres
      digitalWrite(8, LOW); 
      digitalWrite(9, LOW); 
      digitalWrite(10, HIGH); 
      digitalWrite(11, LOW); 
      digitalWrite(12, LOW);       
  } else if (odczytanaWartosc == 4) {  //Czwarty zakres
      digitalWrite(8, LOW); 
      digitalWrite(9, LOW); 
      digitalWrite(10, LOW); 
      digitalWrite(11, HIGH); 
      digitalWrite(12, LOW);       
  } else {  //Pozostałe, czyli piąty zakres
      digitalWrite(8, LOW); 
      digitalWrite(9, LOW); 
      digitalWrite(10, LOW); 
      digitalWrite(11, LOW); 
      digitalWrite(12, HIGH);       
  }
  delay(50); //Opóźnienie, aby nie odczytywać ADC zbyt szybko         
}
