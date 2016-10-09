int motorPin = 9; // The pin connected to the transistor base
int speed = 200; // A value in the range [0..255] which represents the
// speed of the motor

void setup()
{
  pinMode(motorPin, OUTPUT);
}

void loop()
{
  analogWrite(motorPin, speed);
}
