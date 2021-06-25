void setup() {
 
 pinMode(8, INPUT);// set pin as input
 pinMode(9, OUTPUT);
 pinMode(2,OUTPUT);

}

void loop() {
  int count = 0;
   int detect = digitalRead(8);// read obstacle status and store it into "detect"

    if(detect == LOW)// if person shows hand
    {
      digitalWrite(9,HIGH);
      digitalWrite(2,HIGH);
      if(detect == LOW){

      for(int i = 0; i <=240; i++)   
      {                 
          delay(1);
          if(digitalRead(8)!= LOW)
          {
            break;
          }
      }                                      
      }
      
      digitalWrite(9,LOW);
      digitalWrite(2,LOW);
          if(digitalRead(8) == LOW)
          {
            while(digitalRead(8) != HIGH)
            {
              digitalWrite(9,LOW);
              digitalWrite(2,LOW);
              if(digitalRead(8) == HIGH){
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
