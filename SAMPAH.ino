// C++ code
//
#include <Servo.h>
#define ALARM1 20
#define ALARM2 9
#define LED_CLOSE 3             
#define LED_OPEN 4
#define LED_FULL 5
#define US1E 6
#define US1T 7
#define US2E 12
#define US2T 13
#define SERVO 11


int distance1, distance2, length1, length2;
bool isOpen = false;
Servo servo;

void setup()
{
  Serial.begin(9600);
  pinMode(LED_CLOSE, OUTPUT);
  pinMode(LED_OPEN, OUTPUT);
  pinMode(LED_FULL, OUTPUT);
  pinMode(US1E, INPUT);
  pinMode(US1T, OUTPUT);
  pinMode(US2E, INPUT);
  pinMode(US2T, OUTPUT);
  servo.attach(SERVO);
}

void loop()
{
  //sensor luar
  digitalWrite(US1T, LOW);
  delay(200);
  digitalWrite(US1T, HIGH);
  delay(200);
  digitalWrite(US1T, LOW);
  length1 = pulseIn(US1E, HIGH);
  distance1 = (length1/2)/30;
  
  Serial.print("d1: ");
  Serial.print(distance1);
  Serial.println(" cm");
  
  if(distance1<=ALARM1){
  	digitalWrite(LED_CLOSE, LOW);
    digitalWrite(LED_OPEN, HIGH);
    servo.write(80);
    delay(1500);
    isOpen = true;
  }
  else{
  	digitalWrite(LED_CLOSE, HIGH);
    digitalWrite(LED_OPEN, LOW);
    servo.write(0);
    if(isOpen){
    	delay(1500);
      	isOpen = false;
    }
  }
  delay(200);
    
  //sensor dalam
  if(servo.read()==0){
    digitalWrite(US2T, LOW);
    delay(200);
    digitalWrite(US2T, HIGH);
    delay(200);
    digitalWrite(US2T, LOW);
    length2 = pulseIn(US2E, HIGH);
    distance2 = (length2/2)/30;

    Serial.print("d2: ");
    Serial.print(distance2);
    Serial.println(" cm");

    if(distance2<=ALARM2){
      digitalWrite(LED_FULL, HIGH);
      delay(200);
    }
    else{
      digitalWrite(LED_FULL, LOW);
      delay(200);
    }
  }
}