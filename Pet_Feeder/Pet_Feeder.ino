/* 
   Kunju Feeder
   By Mohamed Irfan
*/

#include <Servo.h>

Servo feedingServo;  

// Global Variables
int startingAngle = 0;    
int feedRate = 75;
int thresholdSound = 600;
unsigned long maxTime = 120000;
int servoPin = 9;
int frightenPin = 2;
#define micPin A7

void feed()
{
  for (startingAngle = 0; startingAngle <= feedRate; startingAngle += 1)
  { 
    feedingServo.write(startingAngle);            
    delay(1);                       
  }
  delay(100);
  for (startingAngle = feedRate; startingAngle >= 0; startingAngle -= 1) 
  { 
    feedingServo.write(startingAngle);              
    delay(1);                       
  }
}
unsigned long previousTime = 0;
void frighten()
{
  digitalWrite(frightenPin,HIGH);
}

void unFrighten()
{
  digitalWrite(frightenPin,LOW);
}

void setup() 
{
  feedingServo.attach(servoPin);
  feedingServo.write(0);
  pinMode(frightenPin,OUTPUT); 
  
}

void loop() 
{
  while((analogRead(micPin)) > thresholdSound)
  {
    previousTime = millis();
    frighten();
    delay(3000);
    if((analogRead(micPin)) < thresholdSound)
    {
      unFrighten();
      break;
    }
  }

  unsigned long currentTime = millis();
  
  if((currentTime-previousTime) > maxTime)
  {
    previousTime = millis();
    feed();
  }
}
