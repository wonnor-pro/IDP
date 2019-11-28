#include <Adafruit_MotorShield.h>
//#include <chrono>

Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
Adafruit_DCMotor *right_motor = AFMS.getMotor(1);
Adafruit_DCMotor *left_motor = AFMS.getMotor(2);
Adafruit_DCMotor *mine_motor = AFMS.getMotor(3);

// defines pins numbers
const int trigPin = 12;
const int echoPin = 11;
const int buttonpin = 0;

// trigger
// defines pins numbers
const int trigPin_T = 9;
const int echoPin_T = 8;

// defines variables
int right_motor_speed = 188;
int left_motor_speed = 200;
int turn_90 = 1619;
int moving_time;
int moving_straight_time = 3000;
int moving_straight_time_start = 3500;
long duration;
int count = 0;
int average = 0;
int average_T = 0;
int threshold = 20;
int threshold_T = 5;
int dep_threshold = 10;
bool moving = false;
int first = 0;
int connor = 0;
int a = 0;
int buttonState;
int temp;
int harsh;
int var3 = 0;
unsigned long time_1;
unsigned long time_2;
unsigned long time_3;
unsigned long time_4;
unsigned long d_time1;
unsigned long d_time2;

void setup() {
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input

  pinMode(trigPin_T, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin_T, INPUT); // Sets the echoPin as an Input

  pinMode(buttonpin, INPUT);
  
  Serial.begin(9600); // Starts the serial communication

  Serial.println("Lawnmower Test!!!");

  AFMS.begin();
}

void move_straight(int right_motor_speed, int left_motor_speed) {
  //Serial.println("Adafruit moving straight.");
  right_motor->setSpeed(right_motor_speed);
  left_motor->setSpeed(left_motor_speed);
  left_motor->run(FORWARD);
  right_motor->run(BACKWARD);
}

void move_back(int right_motor_speed, int left_motor_speed) {
  //Serial.println("Adafruit moving straight.");
  right_motor->setSpeed(right_motor_speed);
  left_motor->setSpeed(left_motor_speed);
  left_motor->run(BACKWARD);
  right_motor->run(FORWARD);
}

void stop_motor(){
  right_motor->setSpeed(0);
  left_motor->setSpeed(0);
}

void turn(int right_motor_speed, int left_motor_speed, int angle) {
  //Serial.println("Adafruit turn " + String(angle) + "angle!");
  right_motor->setSpeed(right_motor_speed);
  left_motor->setSpeed(left_motor_speed);
  if (angle < 0) {
      right_motor->run(BACKWARD);
      left_motor->run(BACKWARD);
      angle = -angle;
    }
  else{
      right_motor->run(FORWARD);
      left_motor->run(FORWARD);
    }
  moving_time = angle * ((turn_90) / 90);
  delay(moving_time);
  //Serial.println(String(moving_time));
}

int getdistance(){
  int distance1;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance1= duration*0.034/2;
  // Prints the distance on the Serial Monitor
//  
//  Serial.print("Distance: ");
//  Serial.println(distance1);
  
  return distance1;
}

int getdistance_T(){
  int distance1;
  digitalWrite(trigPin_T, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin_T, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin_T, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin_T, HIGH);
  // Calculating the distance
  distance1= duration*0.034/2;
  // Prints the distance on the Serial Monitor

  Serial.print("Distance: ");
  Serial.println(distance1);
  
  return distance1;
}

void resetminemotor(){
  buttonState = digitalRead(buttonpin);
  while(buttonState==0){
    mine_motor->setSpeed(100);
    mine_motor->run(FORWARD);
    buttonState = digitalRead(buttonpin);
    if (buttonState==1){
      mine_motor->setSpeed(0);
      mine_motor->run(FORWARD);
    }
  }
  delay(2000);
}

void mineflip(){
  while (harsh==0){
  buttonState = digitalRead(buttonpin);
  temp = buttonState;
  Serial.println(String(buttonState));
  delay(100);
  buttonState = digitalRead(buttonpin);
  if (temp!=buttonState){
    a++;
  }
  if (a==4){
    mine_motor->setSpeed(0);
    delay(1000);
    mine_motor->setSpeed(100);
    mine_motor->run(BACKWARD);
    delay(1000);
    mine_motor->setSpeed(0);
    harsh=1;
  }
}
}

void loop() {

  if (first==0) {
    delay(3000);
    resetminemotor();
    delay(1000);
    move_straight(right_motor_speed, left_motor_speed);
    delay(moving_straight_time_start);
    turn(right_motor_speed, left_motor_speed, -90);
    stop_motor();
    first ++;
    }


  //Put into Fn
  int distance = 0;
  for (int i=0; i<5; i++){
    distance = distance + getdistance(); 
//    Serial.print(" sum");
//    Serial.println(distance);
    delay(10);}
  average = distance / 5;

//  Serial.print("--------------- Average: ");
//  Serial.println(average);



  //Put into Fn
  int distance_T = 0;
  for (int i=0; i<5; i++){
    distance_T = distance_T + getdistance_T(); 
    Serial.println("    distance: " + String(distance_T));
    delay(10);}
  average_T = distance_T / 5;
  Serial.println("    average: " + String(average_T));

  // trigerred
  if (average_T < threshold_T) {
   connor = 1;
   }

  // Wall
  if (connor == 0){
    if (average > threshold) {
    move_straight(right_motor_speed, left_motor_speed);
    }
    
    if (average < threshold) {
      Serial.println(String(count == 0));
      Serial.println(String(count == 1));
      if (count == 0){
        turn(right_motor_speed, left_motor_speed, 90); //Turns right
        move_straight(right_motor_speed, left_motor_speed);
        delay(moving_straight_time);
        turn(right_motor_speed, left_motor_speed, 90); //Turns right
        count ++;
        }
      else{
        turn(right_motor_speed, left_motor_speed, -90); //Turns left
        move_straight(right_motor_speed, left_motor_speed);
        delay(moving_straight_time);
        turn(right_motor_speed, left_motor_speed, -90); //Turns left
        count --;
      }
  }
  }

  if (connor == 1){
    stop_motor();
    delay(1000);

    mine_motor->setSpeed(100);
    mine_motor->run(FORWARD); 
    right_motor->setSpeed(25);
    left_motor->setSpeed(25);
    right_motor->run(BACKWARD);
    left_motor->run(FORWARD);
    a = 0;
    harsh = 0;   
    mineflip();
    delay(1000);
    if (count==0){
      turn(right_motor_speed, left_motor_speed, 90);
    }
    if (count==1){
      turn(right_motor_speed, left_motor_speed, -90);
    }
      stop_motor();
      time_1 = millis();
      move_back(right_motor_speed, left_motor_speed);
      while(1){
        int distance_drop = 0;
        for (int i=0; i<5; i++){
        distance_drop = distance_drop + getdistance_T(); 
        //Serial.println("    distance: " + String(distance_T));
        delay(10);}
        int average_drop = distance_drop / 5;
        if (average_drop<threshold){
          break;
          }
        }
      time_2 = millis();
      d_time1 = time_2 - time_1;
      turn(right_motor_speed, left_motor_speed, -90);
      stop_motor();
      time_3 = millis();
      move_straight(right_motor_speed, left_motor_speed);
      var3 = 0;
      while(var3==0){
        int distance_drop = 0;
        for (int i=0; i<5; i++){
        distance_drop = distance_drop + getdistance(); 
        //Serial.println("    distance: " + String(distance_T));
        delay(10);}
        int average_drop = distance_drop / 5;
        if (average_drop<dep_threshold){
          time_4 = millis();
          d_time2 = time_4 - time_3;
          stop_motor();
          delay(1000);
          resetminemotor();
          delay(1000);
          move_back(right_motor_speed, left_motor_speed);
          delay(d_time2);
          turn(right_motor_speed, left_motor_speed, 90);
          move_straight(right_motor_speed, left_motor_speed);
          delay(d_time1);
          if (count==0){
            turn(right_motor_speed, left_motor_speed, -90);
            var3=1;
          }
          if (count==1){
            turn(right_motor_speed, left_motor_speed, 90);
            var3=1;
          }
          }
        }
    }
    connor = 0;
  }
