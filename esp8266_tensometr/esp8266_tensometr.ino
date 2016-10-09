#include <SoftwareSerial.h>

SoftwareSerial mySerial(2,3);
int flexSensorPin = A0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  mySerial.begin(9600);

  pinMode(11,OUTPUT);
  digitalWrite(11,LOW);

  pinMode(12,OUTPUT);
  digitalWrite(12,LOW);

  pinMode(13,OUTPUT);
  digitalWrite(13,LOW);
  
  while(!wyslij("AT","OK",100)){
    Serial.println("Blad komunikacji!");
    delay(1000);
  }
  Serial.println("Rozpoczeto komunikacje!");

//  if(wyslij("AT+CWMODE=1","OK",100))
//  Serial.println("CWMODE - OK");
//  if(wyslij("AT+CIPMODE=0","OK",100))
//  Serial.println("CIPMODE - OK");
//  if(wyslij("AT+CIPMUX=1","OK",100))
//  Serial.println("CIPMUX - OK");
//  if(wyslij("AT+CWJAP=\"703a\",\"$ylwusi@007\"","OK",5000))
//  Serial.println("Polaczono z siecia");
//  if(wyslij("AT+CIPSERVER=1,80","OK",5000))
//  Serial.println("Uruchomiono serwer");
//  mySerial.println("AT+CIFSR");
//  Serial.println(mySerial.readString());
if(wyslij("AT+RST","OK",300))
  Serial.println("RESET - OK");
  if(wyslij("AT+CWMODE=3","OK",300))
  Serial.println("CWMODE - OK");
  if(wyslij("AT+CIPMUX=1","OK",300))
  Serial.println("CIPMUX - OK");
  if(wyslij("AT+CIPSERVER=1,80","OK",300))
  Serial.println("CIPSERVER - OK");
  if(wyslij("AT+CWSAP=\"Tenso\",\"mypassword\",5,2","OK",3000))
  Serial.println("CWSAP - OK");
  mySerial.println("AT+CWSAP?");
  Serial.println(mySerial.readString());
  mySerial.println("AT+CIFSR");
  Serial.println(mySerial.readString());
//  if(wyslij("AT+CWDHCP=0,0","OK",3000))
//  Serial.println("CWDHCP - OK");
//  mySerial.println("AT+CWLAP");
//  Serial.println(mySerial.readString());
//  if(wyslij("AT+CIPMODE=0","OK",100))
//  Serial.println("CIPMODE - OK");
//  if(wyslij("AT+CIPMUX=1","OK",100))
//  Serial.println("CIPMUX - OK");
//  if(wyslij("AT+CWJAP=\"703a\",\"$ylwusi@007\"","OK",5000))
//  Serial.println("Polaczono z siecia");
//  if(wyslij("AT+CIPSERVER=1,80","OK",5000))
//  Serial.println("Uruchomiono serwer");
//  mySerial.println("AT+CIFSR");
//  Serial.println(mySerial.readString());
}

char klient[1];
char bufor[70];
String strona;

void loop() {
  // put your main code here, to run repeatedly:
  int flexSensorReading = analogRead(flexSensorPin);
//  while(mySerial.available() > 0){
  if (mySerial.available()){
    if(mySerial.find("+IPD,")){
      delay(1000);
//      mySerial.readBytesUntil(',',klient,1);
      int connectionId = mySerial.read()-48;
      klient[0] = connectionId;
      Serial.println();
      Serial.print("Zapytanie ID: ");
      Serial.println(klient[0]);
      strona = "<html><head><title>TEST</title><meta http-equiv=\"refresh\" content=\"7\" ></head><body><h2> Odczyt z tensometru: " + (String)flexSensorReading + "</h2></body></html>";
      sprintf(bufor,"AT+CIPSEND=%c,%d",klient[0],strona.length());
      if(wyslij(bufor,">",100)) Serial.println("Zadanie wyslania...");
      if(wyslij(strona,"OK",100)); Serial.println("Wyslano dane");

      sprintf(bufor,"AT+CIPCLOSE=%c",klient[0]);
      if(wyslij(bufor,"OK",100)) Serial.println("Zamknieto polaczenie");
    }
  }
  if(flexSensorReading > 400 && flexSensorReading <= 600){
    digitalWrite(11,HIGH);
    digitalWrite(12,LOW);
    digitalWrite(13,LOW);
  }
  if((flexSensorReading > 200 && flexSensorReading <= 400)
    ||(flexSensorReading > 600 && flexSensorReading <= 800)){
    digitalWrite(11,LOW);
    digitalWrite(12,HIGH);
    digitalWrite(13,LOW);
  }
  if(flexSensorReading <= 200 || flexSensorReading > 800){
    digitalWrite(11,LOW);
    digitalWrite(12,LOW);
    digitalWrite(13,HIGH);
  }
//  mySerial.println("AT+CWLIF");
//  Serial.println(mySerial.readString());
//  delay(4000);
}

boolean wyslij(String Komenda_AT, char *Odpowiedz_AT, int czas_czekania){
  mySerial.println(Komenda_AT);
  delay(czas_czekania);
  while(mySerial.available() > 0){
    if (mySerial.find(Odpowiedz_AT)) return 1;
  }
  return 0;
}
