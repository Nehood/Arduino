#include <SoftwareSerial.h>

#define DEBUG true

SoftwareSerial esp8266(2,3);
int flexSensorPin = A0;

int motorPin1 =  9;    // One motor wire connected to digital pin 5
int motorPin2 =  10;    // One motor wire connected to digital pin 6

void setup() {
  Serial.begin(9600);
  esp8266.begin(9600);
  
  pinMode(motorPin1, OUTPUT); 
  pinMode(motorPin2, OUTPUT);
  
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

      float force = 0;
      float brake;
      if (flexSensorReading>400 && flexSensorReading<450) force = 0;
      if (flexSensorReading<400) force = (400 - flexSensorReading) * 0.05;
      if (flexSensorReading>450) force = (flexSensorReading - 450) * 0.05;
      brake = force * 4.1;
      
      String content; //wyraz, ktory odsylamy
      content = "<html><head><title>TEST</title><meta http-equiv=\"refresh\" content=\"7\" ></head>"
      "<body><h1> Odczyt z tensometru: " + (String)force + "N</h1></br><h1> Hamulec ustawiony na: " + (String)brake +"%</h1></body></html>";

      sendCIPData(connectionId,content);

      rotateLeft(50);
    
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

void rotateLeft(int speedOfRotate){
  analogWrite(motorPin1, speedOfRotate); //rotates motor
  digitalWrite(motorPin2, LOW);    // set the Pin motorPin2 LOW
  delay(1000); //waits
  digitalWrite(motorPin1, LOW);    // set the Pin motorPin1 LOW
}

void rotateRight(int speedOfRotate){
  analogWrite(motorPin2, speedOfRotate); //rotates motor
  digitalWrite(motorPin1, LOW);    // set the Pin motorPin1 LOW
  delay(1000); //waits
  digitalWrite(motorPin2, LOW);    // set the Pin motorPin2 LOW
}

