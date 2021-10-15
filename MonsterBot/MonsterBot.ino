// Declaring Varables
const int steering1 = 2;
const int steering2 = 3;
const int frontmotor1 = 4;
const int frontmotor2 = 5;
const int rearmotor1 = 8;
const int rearmotor2 = 9;
const int headlight = 6;

bool fwdstate = false;

int value = 0;

// Defining Functions
void turnLeft();
void turnRight();
void straight();
void forward();
void reverse();
void brake();

void setup() 
{
  pinMode(steering1 , OUTPUT);
  pinMode(steering2 , OUTPUT);
  pinMode(rearmotor1,OUTPUT);
  pinMode(rearmotor2,OUTPUT);
  pinMode(frontmotor1,OUTPUT);
  pinMode(frontmotor2,OUTPUT);
  pinMode(headlight,OUTPUT);

  brake();
  straight();
  digitalWrite(headlight, LOW);
  fwdstate = false;
  Serial.begin(9600);
}



void loop()
{
  if(Serial.available() > 0){ // Checks whether data is comming from the serial port
    value = Serial.read(); // Reads the data from the serial port
 }
 delay(10);

// Drive
  if (value == '1') 
  {
   forward();
  }
  else if (value == '3')
  {
    reverse();
  }
  else if( value == '0' || value == '2')
  {
    brake();
  }

// Steer
  if(value == '5')
  {
    turnRight();
  }  
  else if(value == '7')
  {
    turnLeft();
  }
  else if(value == '4' || value == '6')
  {
    straight();
  }

// FourWheel Drive
  if(value == 57)
  {
    fwdstate = true;
  }
  else if(value == 56)
  {
    fwdstate = false;
  }

// Headlight
  if(value == 59)
  {
    digitalWrite(headlight, HIGH);
  }
  else if(value == 58)
  {
    digitalWrite(headlight, LOW);
  }
}

// Steering Functions
void turnLeft()
{
  digitalWrite(steering1,LOW);
  digitalWrite(steering2,HIGH);
}
void turnRight()
{
  digitalWrite(steering1,HIGH);
  digitalWrite(steering2,LOW);
}
void straight()
{  
  digitalWrite(steering1,LOW);
  digitalWrite(steering2,LOW);
}

// Driving Functions
void forward()
{  
  digitalWrite(rearmotor1,LOW);
  digitalWrite(rearmotor2,HIGH);

  if(fwdstate)
  {
  digitalWrite(frontmotor1,LOW);
  digitalWrite(frontmotor2,HIGH);
  }
  else 
  {
  digitalWrite(frontmotor1,LOW);
  digitalWrite(frontmotor2,LOW);
  }
}
void reverse()
{  
  digitalWrite(rearmotor1,HIGH);
  digitalWrite(rearmotor2,LOW);
  if(fwdstate)
  {
  digitalWrite(frontmotor1,HIGH);
  digitalWrite(frontmotor2,LOW);
  }
  else 
  {
  digitalWrite(frontmotor1,LOW);
  digitalWrite(frontmotor2,LOW);
  }
}
void brake()
{  
  digitalWrite(rearmotor1,LOW);
  digitalWrite(rearmotor2,LOW);
  digitalWrite(frontmotor1,LOW);
  digitalWrite(frontmotor2,LOW);
}
