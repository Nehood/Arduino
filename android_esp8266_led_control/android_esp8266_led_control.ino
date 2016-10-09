#include <SoftwareSerial.h>

#define DEBUG true

SoftwareSerial esp8266(2,3);

void setup() {
  Serial.begin(9600);
  esp8266.begin(9600);

  pinMode(11,OUTPUT);
  digitalWrite(11,LOW);

  pinMode(12,OUTPUT);
  digitalWrite(12,LOW);

  pinMode(13,OUTPUT);
  digitalWrite(13,LOW);

  pinMode(10,OUTPUT);
  digitalWrite(10,LOW);

  sendCommand("AT+RST\r\n",2000,DEBUG); //reset
  sendCommand("AT+CWMODE=1\r\n",1000,DEBUG);  //set as acces point
  sendCommand("AT+CWJAP=\"703a\",\"$ylwusi@007\"\r\n",3000,DEBUG);
  delay(10000);
  sendCommand("AT+CIFSR\r\n",1000,DEBUG); //get ip address
  sendCommand("AT+CIPMUX=1\r\n",1000,DEBUG);  //multiconnections
  sendCommand("AT+CIPSERVER=1,80\r\n",1000,DEBUG);

  Serial.println("Server ready");
}

void loop() {
  // put your main code here, to run repeatedly:
  if (esp8266.available()){
    if (esp8266.find("+IPD,")){
      delay(1000);  //czekaj na reszte przesylu
      //pobierz ID do pozniejszego rozlaczenia
      int connectionId = esp8266.read()-48; //zmiana kodu z ASCII

      esp8266.find("pin="); //przesuwamy sie do pin=

      int pinNumber = (esp8266.read()-48);  //pobieramy pierwsza wartosc
      int secondNumber = (esp8266.read()-48);
      if(secondNumber>=0 && secondNumber<=9){
        pinNumber *= 10;
        pinNumber += secondNumber;
      }

      digitalWrite(pinNumber, !digitalRead(pinNumber));  //sprytny zapis

      String content; //wyraz, ktory odsylamy
      content = "Pin ";
      content += pinNumber;
      content += " is ";
      if (digitalRead(pinNumber)) content += "ON";
      else content += "OFF";

      sendHTTPResponse(connectionId,content);

      String closeCommand = "AT+CIPCLOSE=";//zamykanie polaczenia
      closeCommand += connectionId;
      closeCommand += "\r\n";

      sendCommand(closeCommand,1000,DEBUG);//operacja zamykania
    }
  }
}

String sendData(String command, const int timeout, boolean debug){
  String response = "";

  int dataSize = command.length();
  char data[dataSize];
  command.toCharArray(data,dataSize);

  esp8266.write(data,dataSize);
  if(debug){
    Serial.println("\r\n===== HTTP Response from Arduino =====");
    Serial.write(data,dataSize);
    Serial.println("\r\n======================================");
  }

  long int time = millis();

  while((time+timeout) > millis()){
    while(esp8266.available()){
      char c = esp8266.read();
      response += c;
    }
  }

  if(debug) Serial.print(response);
  return response;
}

void sendHTTPResponse(int connectionId, String content){
  String httpResponse;
  String httpHeader;

  httpHeader = "HTTP/1.1 200 OK\r\nContent-Type: text/html; charset=UTF-8\r\n"; 
     httpHeader += "Content-Length: ";
     httpHeader += content.length();
     httpHeader += "\r\n";
     httpHeader +="Connection: close\r\n\r\n";
     httpResponse = httpHeader + content + " "; // There is a bug in this code: the last character of "content" is not sent, I cheated by adding this extra space
     sendCIPData(connectionId,httpResponse);
}

void sendCIPData(int connectionId, String data)
{
   String cipSend = "AT+CIPSEND=";
   cipSend += connectionId;
   cipSend += ",";
   cipSend +=data.length();
   cipSend +="\r\n";
   sendCommand(cipSend,1000,DEBUG);
   sendData(data,1000,DEBUG);
}

String sendCommand(String command, const int timeout, boolean debug)
{
    String response = "";
           
    esp8266.print(command); // send the read character to the esp8266
    
    long int time = millis();
    
    while( (time+timeout) > millis())
    {
      while(esp8266.available())
      {
        
        // The esp has data so display its output to the serial window 
        char c = esp8266.read(); // read the next character.
        response+=c;
      }  
    }
    
    if(debug)
    {
      Serial.print(response);
    }
    
    return response;
}

