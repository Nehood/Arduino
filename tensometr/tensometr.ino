int flexSensorPin = A0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int flexSensorReading = analogRead(flexSensorPin); 

  Serial.println(flexSensorReading);
  delay(250);
}
