// Arduino pins
#define leftMotor1 4
#define leftMotor2 5
#define leftMotorEnable 6
#define rightMotor1 2
#define rightMotor2 3
#define rightMotorEnable 7
#define leftEcho 11 
#define leftTrig 10
#define rightEcho 13
#define rightTrig 12
#define frontEcho 9
#define frontTrig 8 

// Bot movements
int X = 0, Y = 0, Dir = 0;
void stop()
{
  digitalWrite(leftMotor1,LOW);
  digitalWrite(leftMotor2,LOW);
  digitalWrite(rightMotor1,LOW);
  digitalWrite(rightMotor2,LOW);
}
void forward()
{
  digitalWrite(leftMotor1,LOW);
  digitalWrite(leftMotor2,HIGH);
  digitalWrite(rightMotor1,HIGH);
  digitalWrite(rightMotor2,LOW);
  delay(800);
  stop();

  if(Dir == 0)
  {
    Y += 1;
  }
  else if(Dir == 90)
  {
    X += 1;
  }
  else if(Dir == 180)
  {
    Y -= 1;
  }
  else if(Dir == -90)
  {
    X -= 1;
  }
}
void right()
{
  digitalWrite(leftMotor1,LOW);
  digitalWrite(leftMotor2,HIGH);
  digitalWrite(rightMotor1,LOW);
  digitalWrite(rightMotor2,HIGH);
  delay(700);
  stop();
  if(Dir == 0 || Dir == 90 || Dir == -90)
  {
    Dir += 90;
  }
  else if(Dir == 180)
  {
    Dir = -90;
  }
}
void left()
{
  digitalWrite(leftMotor1,HIGH);
  digitalWrite(leftMotor2,LOW);
  digitalWrite(rightMotor1,HIGH);
  digitalWrite(rightMotor2,LOW);
  delay(700);
  stop();

  if(Dir == 0 || Dir == 90 || Dir == 180)
  {
    Dir -= 90;
  }
  else if(Dir == -90)
  {
    Dir = 180;
  }
}

// Obstacle detection
bool rightWall,frontWall,leftWall;
void ping(int trig)
{
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(5);
  digitalWrite(trig, LOW);
}
double distance(int echo)
{
  double duration = pulseIn(echo, HIGH);
  double distance = duration/29/2;
  return distance;
}
void wall()
{
  stop();
  ping(frontTrig);
  long frontDist = distance(frontEcho);
  if(frontDist <= 8)
  {
    frontWall = true;
  }
  ping(rightTrig);
  long rightDist = distance(rightEcho);
  if(rightDist <= 4)
  {
    rightWall = true;
  }
  ping(leftTrig);
  long leftDist = distance(leftEcho);
  if(leftDist <= 4)
  {
    leftWall = true;
  }
  Serial.println("left: ");
  Serial.println(leftDist);

  Serial.println("right: ");
  Serial.println(rightDist);

  Serial.println("front: ");
  Serial.println(frontDist);
  Serial.print("\n");
  Serial.print("\n");
}

bool reverse = false;
void junction()
{
  reverse = false;
  if(!frontWall && !rightWall && !leftWall)
  {
    forward();
    explore();
    right();
    explore();
    forward();
    explore();

    reverse = true;
    right();
    explore();
    return;
  }
  else if(frontWall && !rightWall && !leftWall)
  {
    left();
    explore();
    forward();
    explore();

    reverse = true;
    left();
    explore();
    return;
  }
  else if(!frontWall && rightWall && !leftWall)
  {
    forward();  
    explore();
    right();
    explore();

    reverse = true;
    right();
    explore();
    return;
  }
  else if(!frontWall && !rightWall && leftWall)
  {
    forward();  
    explore();
    left();
    explore();


    reverse = true;
    right();
    explore();
    return;
  }
  else
  {
    return;
  }

}

void explore()
{
  while(true)
  {
    if(!frontWall && rightWall && leftWall)
    {
      forward();
    }
    if(rightWall && frontWall && !leftWall)
    {
      left();
      forward();
    }
    else if(leftWall && frontWall && !rightWall)
    {
      right();
      forward();
    }
    else if(frontWall && rightWall && leftWall)
    {
      right();
      right();
      reverse = true;
      explore();
      return;
    }
    else if(!reverse)
    {
      junction();
      return;
    }
    else
    {
      return;
    }
  }
}

void setup() {
  Serial.begin(9600);
  pinMode(leftMotor1,OUTPUT);
  pinMode(leftMotor2,OUTPUT);
  pinMode(rightMotor1,OUTPUT);
  pinMode(rightMotor1,OUTPUT);
  pinMode(leftTrig,OUTPUT);
  pinMode(rightTrig,OUTPUT);
  pinMode(frontTrig,OUTPUT);
  pinMode(leftEcho,INPUT);
  pinMode(rightEcho,INPUT);
  pinMode(frontEcho,INPUT);
  pinMode(leftMotorEnable,OUTPUT);
  pinMode(rightMotorEnable,OUTPUT);
  // junction();
  digitalWrite(leftMotorEnable,HIGH);
  digitalWrite(rightMotorEnable,HIGH);

}

void loop() {
  wall();
  junction();
}
