//#include <SoftwareSerial.h>
//
//SoftwareSerial mySerial(2,3);
//
//void setup() {
//  // put your setup code here, to run once:
//  Serial.begin(9600);
//  mySerial.begin(9600);
//}
//
//void loop() {
//  // put your main code here, to run repeatedly:
//  if(mySerial.available()){
//    while(mySerial.available()){
//      char c = mySerial.read();
//      Serial.write(c);
//    }
//  }
//
//  if(Serial.available()){
//    delay(1000);
//    String command="";
//    while(Serial.available()){
//      command += (char)Serial.read();
//    }
//    mySerial.println(command);
//  }
//}

#include <SoftwareSerial.h>

SoftwareSerial mySerial(2,3);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  mySerial.begin(9600);

  while(!wyslij("AT","OK",100)){
    Serial.println("Blad komunikacji!");
    delay(1000);
  }
  Serial.println("Rozpoczeto komunikacje!");

  if(wyslij("AT+CWMODE=1","OK",100))
  Serial.println("CWMODE - OK");
  if(wyslij("AT+CIPMODE=0","OK",100))
  Serial.println("CIPMODE - OK");
  if(wyslij("AT+CIPMUX=1","OK",100))
  Serial.println("CIPMUX - OK");
  if(wyslij("AT+CWJAP=\"703a\",\"$ylwusi@007\"","OK",5000))
  Serial.println("Polaczono z siecia");
  if(wyslij("AT+CIPSERVER=1,80","OK",5000))
  Serial.println("Uruchomiono serwer");

  mySerial.println("AT+CIFSR");
  Serial.println(mySerial.readString());
}

char klient[1];
char bufor[50];
String strona;

void loop() {
  // put your main code here, to run repeatedly:
  while(mySerial.available() > 0){
    if(mySerial.find("+IPD,")){
      mySerial.readBytesUntil(',',klient,1);
      Serial.println();
      Serial.print("Zapytanie ID: ");
      Serial.println(klient[0]);

      strona = "<html><head><title>TEST</title></head><body><h2>Testujemy</h2></body></html>";
      sprintf(bufor,"AT+CIPSEND=%c,%d",klient[0],strona.length());
      if(wyslij(bufor,">",100)) Serial.println("Zadanie wyslania...");
      if(wyslij(strona,"OK",100)); Serial.println("Wyslano dane");

      sprintf(bufor,"AT+CIPCLOSE=%c",klient[0]);
      if(wyslij(bufor,"OK",100)) Serial.println("Zamknieto polaczenie");
    }
  }
}

boolean wyslij(String Komenda_AT, char *Odpowiedz_AT, int czas_czekania){
  mySerial.println(Komenda_AT);
  delay(czas_czekania);
  while(mySerial.available() > 0){
    if (mySerial.find(Odpowiedz_AT)) return 1;
  }
  return 0;
}

