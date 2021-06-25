long duration;
double distance_fromhand;
int echo = 2;
int trig = 3;
#define length 15
#define time 50

  double distance()
  {
    digitalWrite(trig,LOW);
    delay(2);
    
    digitalWrite(trig,HIGH);
    delay(10);
    digitalWrite(trig,LOW);

    duration = pulseIn(echo,HIGH);
    distance_fromhand = duration * 0.017 ;
    return distance_fromhand;
    
  } 

void setup() {
  pinMode(trig,OUTPUT);
  pinMode(echo,INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  int count = 0;
   
    if(distance() < length)// if person shows hand
    {
      digitalWrite(LED_BUILTIN,HIGH);
      if(distance() < length){

      for(int i = 0; i <=time; i++)   
      {                 s
          delay(0.25);
          if(distance() > length)
          {
            break;
          }
      }                                      
      }
      
      digitalWrite(LED_BUILTIN,LOW);
          if(distance() < length)
          {
            while(distance() < length)
            {
              digitalWrite(LED_BUILTIN,LOW);
              if(distance() > length){
                break;
              }
            }
            
          }
          
    }
    if(count == 1){
      asm volatile ("jmp 0");
    }
    count ++;
 
}
