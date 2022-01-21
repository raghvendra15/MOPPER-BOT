#include <SoftwareSerial.h>
SoftwareSerial BT(2, 3);    //TX, RX respetively For BT
String readdata;
int trigPin = 4;      // trig pin of HC-SR04
int echoPin = 5;
const int button=6;
 int revleft= 12;       //REVerse motion of Left motor
int fwdleft = 13; 
                             //ForWarD motion of Left motor
int fwdright = 10;       //ForWarD motion of Left motor
int revright = 11;
int MOPfwd= 9;
int  Brushfwd= 8;
int Pump=7;//WATER PUMP MOTOR PIN(CONTROLLED BY RELAY)
int buttonState=0;

int duration = 0;
int distance = 0;

void setup() 
{
 BT.begin(9600);
 Serial.begin(9600);
 pinMode(revleft, OUTPUT);
 pinMode(fwdleft, OUTPUT);
 
 pinMode(fwdright,OUTPUT);   //right motors forward
pinMode(revright,OUTPUT);   //right motors reverse
pinMode(MOPfwd, OUTPUT); 
pinMode( Brushfwd, OUTPUT);
pinMode(Pump, OUTPUT);
pinMode(button, INPUT);
 pinMode(trigPin, OUTPUT);         // set trig pin as output
  pinMode(echoPin, INPUT);
}

void loop(){
  buttonState=digitalRead(button);
  if (buttonState == HIGH){
 
  while (BT.available()>0)
      { 

  char c = BT.read(); 
  readdata += c; 
      } 
  if (readdata.length() > 0) 
      {
   Serial.println(readdata);
    delay(100); 
  if(readdata == "F") 
  {
   digitalWrite(fwdleft, HIGH);
    digitalWrite(revleft, LOW);
    
     digitalWrite(fwdright, HIGH);
      digitalWrite(revright, LOW);
   delay(100);
  }
  
  else if(readdata == "B")
  {
  digitalWrite(fwdleft, LOW);
    digitalWrite(revleft, HIGH);
     digitalWrite(fwdright, LOW);
      digitalWrite(revright, HIGH);
   delay(100);
  }

   else if(readdata == "L")
  {
   digitalWrite(fwdright,LOW);
  digitalWrite(revright,HIGH);
  digitalWrite(fwdleft,HIGH);
  digitalWrite(revleft,LOW);
  
   delay(100);
  }

   else if(readdata == "R")
  {
     digitalWrite(fwdright,HIGH);
  digitalWrite(revright,LOW);
  digitalWrite(fwdleft,LOW);
  digitalWrite(revleft,HIGH);
   delay(100);
  }
   
   else if(readdata == "S")
  {
   digitalWrite(fwdright,LOW);
  digitalWrite(revright,LOW);
  digitalWrite(fwdleft,LOW);
  digitalWrite(revleft,LOW);
  
   delay(100);
  }

 else if(readdata == "X")
  {
  digitalWrite(MOPfwd,HIGH);
  digitalWrite(Pump,HIGH);
  delay(100);
  }
    else if(readdata == "x")
  {
     digitalWrite(MOPfwd,LOW);
     digitalWrite(Pump,LOW);
  delay(100);
  }
  
    else if(readdata == "V")
  {
   digitalWrite(Brushfwd,HIGH);
   Serial.println("tested hhhhhhhhhh");
  delay(100);
  }
      else if(readdata == "v")
  {
     digitalWrite(Brushfwd,LOW);
     Serial.println("tested ttttttttttt");
  delay(100);
  }
     }
     readdata="";
 }
//===============================================================================================
      
 else {
    digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  // Displays the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
    // If you dont get proper movements of your robot then alter the pin numbers
  if (distance >20)            
  {
    digitalWrite(fwdright, HIGH);                    // move forward
    digitalWrite(revright, LOW);
    digitalWrite(fwdleft, HIGH);                                
    digitalWrite(revleft, LOW); 
    delay(1000); 
    digitalWrite(MOPfwd, HIGH);
    digitalWrite( Brushfwd, HIGH);
    digitalWrite(Pump, HIGH);                                                   
  }

  if (distance < 20)
  {
    digitalWrite(MOPfwd, LOW);
    digitalWrite(Brushfwd, LOW);
    digitalWrite(Pump,LOW);
    delay(100);
    digitalWrite(fwdright, HIGH);       
    digitalWrite(revright, LOW);   //turn right
    digitalWrite(revleft, HIGH);                                 
    digitalWrite(fwdleft, LOW);
    
    delay(1500);
  }
 }

}
