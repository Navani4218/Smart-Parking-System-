#include <Servo.h>
Servo myservo_1;
Servo myservo_2;
int trigPin_1 = 7;    // TRIG pin
int echoPin_1 = 8;    // ECHO pin
int trigPin_2 = 9;    // TRIG pin
int echoPin_2 = 10;
int ir_sensor_pin_1 = 2;
int ir_sensor_pin_2 = 3;

float duration_us, distance;
void setup() {
  Serial.begin(9600);
  pinMode(trigPin_1, OUTPUT);
  pinMode(echoPin_1, INPUT);
  pinMode(trigPin_2, OUTPUT);
  pinMode(echoPin_2, INPUT);
  pinMode(ir_sensor_pin_1, INPUT);
  pinMode(ir_sensor_pin_2, INPUT);
  myservo_1.attach(6);
  myservo_2.attach(13);
  myservo_1.write(0);
  myservo_2.write(0);
}

void loop() {
  servo_1();
  servo_2();
  int p_1 = getDistance(trigPin_1,echoPin_1);
  int p_2 = getDistance(trigPin_2,echoPin_2);
  if (p_1 <= 4 & p_2 <= 4){
    Serial.println("Slot_1 is occupied");
    Serial.println("Slot_2 is occupied");
  }
  else if(p_1 >4 & p_2 <=4){
    Serial.println("Slot_1 is free");
    Serial.println("Slot_2 is occupied");
  }
  else if(p_1 <=4 & p_2 >4){
 Serial.println("Slot_1 is occupied");
    Serial.println("Slot_2 is free");
  }
  else{
    Serial.println("Slot_1 is free");
    Serial.println("Slot_2 is free");
  }
}
int getDistance(int trig,int echo){
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  duration_us = pulseIn(echo, HIGH);
  distance = 0.017 * duration_us;
  return distance;
}
void servo_1(){
  int pos =0;
    if (digitalRead(ir_sensor_pin_1)== LOW) // if Pin logic is HIGH
  {
    Serial.println("Object_1 detected");
    for (pos = 0; pos <= 90; pos += 1)
    { 
      myservo_1.write(pos);              // tell servo to go to position in variable 'pos'
      delay(15);                       // waits 15 ms for the servo to reach the position
    }
    for (pos = 90; pos >= 0; pos -= 1)
    { 
      myservo_1.write(pos);              // tell servo to go to position in variable 'pos'
      delay(15);                       // waits 15 ms for the servo to reach the position
    }
      delay(250);
  }
}
void servo_2(){
  int pos = 0;
    if (digitalRead(ir_sensor_pin_2)== LOW) // if Pin logic is HIGH
  {
    Serial.println("Object detected");
    myservo_2.write(pos);              // tell servo to go to position in variable 'pos'
    delay(5000);
    myservo_2.write(pos);              // tell servo to go to position in variable 'pos'
    delay(250);
  }
}