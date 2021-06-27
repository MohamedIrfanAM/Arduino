/* 
   Kunju Feeder
   By Mohamed Irfan
*/

#include <Servo.h>

Servo feedingServo;  

// Global Variables
int startingAngle = 0;    
int feedRate = 70;
int thresholdSound = 900;
unsigned long maxTime = 300000;
int servoPin = 9;
int ledPin = 7;
int buzzerPin = 8;
#define micPin A0

void feed()
{
  for (startingAngle = 0; startingAngle <= feedRate; startingAngle += 1)
  { 
    feedingServo.write(startingAngle);            
    delay(1);                       
  }
  delay(10);
  for (startingAngle = feedRate; startingAngle >= 0; startingAngle -= 1) 
  { 
    feedingServo.write(startingAngle);              
    delay(1);                       
  }
}
unsigned long previousTime = 0;
void frighten()
{
  digitalWrite(ledPin,HIGH);
  digitalWrite(buzzerPin,HIGH);
}

void unFrighten()
{
  digitalWrite(ledPin,LOW);
  digitalWrite(buzzerPin,LOW);
}

void setup() 
{
  feedingServo.attach(servoPin);
  feedingServo.write(0);
  pinMode(ledPin,OUTPUT); 
  pinMode(buzzerPin,OUTPUT); 
  
  Serial.begin(9600);
}

void loop() 
{
  
  while((analogRead(micPin)) > thresholdSound)
  {
//    Serial.println("High Sound");
//    Serial.print(analogRead(micPin)*50);
    previousTime = millis();
    frighten();
    delay(1500);
    if((analogRead(micPin)) < thresholdSound)
    {
//      Serial.println("Low Sound");
//      Serial.print(analogRead(micPin)*50);
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
  //Serial.println(currentTime-previousTime);
}
