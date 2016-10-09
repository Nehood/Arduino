#include <SoftwareSerial.h>

#define DEBUG true

SoftwareSerial esp8266(2,3);
int flexSensorPin = A0;

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

//  sendCommand("AT+RST\r\n",2000,DEBUG); //reset
//  sendCommand("AT+CWMODE=1\r\n",1000,DEBUG);  //set as acces point
//  sendCommand("AT+CWJAP=\"703a\",\"$ylwusi@007\"\r\n",3000,DEBUG);
//  delay(10000);
//  sendCommand("AT+CIFSR\r\n",1000,DEBUG); //get ip address
//  sendCommand("AT+CIPMUX=1\r\n",1000,DEBUG);  //multiconnections
//  sendCommand("AT+CIPSERVER=1,80\r\n",1000,DEBUG);
  //sendCommand("AT+CIPSTART=\"TCP\",\"modul.tensometr.org\",80\r\n",2000,DEBUG);
  sendCommand("AT+RST\r\n",2000,DEBUG); //reset
  sendCommand("AT+CWMODE=3\r\n",1000,DEBUG);
  sendCommand("AT+CIPMUX=1\r\n",1000,DEBUG);
  sendCommand("AT+CIPSERVER=1,80\r\n",1000,DEBUG);
  sendCommand("AT+CWSAP=\"modul\",\"mypassword\",6,2\r\n",5000,DEBUG);
  sendCommand("AT+CWSAP?\r\n",5000,DEBUG);
  sendCommand("AT+CIFSR\r\n",5000,DEBUG);
  Serial.println("Server ready");
}

char bufor[50];

void loop() {
  // put your main code here, to run repeatedly:
  int flexSensorReading = analogRead(flexSensorPin);
  if (esp8266.available()){
    if (esp8266.find("+IPD,")){
      delay(1000);  //czekaj na reszte przesylu
      //pobierz ID do pozniejszego rozlaczenia
      int connectionId = esp8266.read()-48; //zmiana kodu z ASCII

      String content; //wyraz, ktory odsylamy
      content = "<html><head><title>TEST</title><meta http-equiv=\"refresh\" content=\"7\" ></head><body><h2> Odczyt z tensometru: " + (String)flexSensorReading + "</h2></body></html>";;

      sendCIPData(connectionId,content);

    
      String closeCommand = "AT+CIPCLOSE=";//zamykanie polaczenia
      closeCommand += connectionId;
      closeCommand += "\r\n";

      sendCommand(closeCommand,1000,DEBUG);//operacja zamykania
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

