#include <Adafruit_MotorShield.h>

Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
Adafruit_DCMotor *right_motor = AFMS.getMotor(1);
Adafruit_DCMotor *left_motor = AFMS.getMotor(2);
int right_motor_speed = 144;
int left_motor_speed = 150;
int turn_90 = 2156;
int moving_time = 2000;
int threshold = 10;

// defines pins numbers
const int trigPin = 12;
const int echoPin = 11;
// defines variables
long duration; // Ultrasound;
int distance; // Ultrasound;
int count = 0;
bool moving = 1;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); // set up Serial library at 9600 bps
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  Serial.println("Adafruit Motorshield v2 initialised!");

  AFMS.begin();
}

void loop() {

  while (1){
    
  if (!moving){
    moving = true;
    Serial.println("Start Moving");
    } // if

  if (moving){
  int sum_distance = 0;
  for (int i=0; i<5; i++) {
    sum_distance += get_distance(); 
    Serial.println(" Sum: " + String(sum_distance));
    delay(10);}
  
  sum_distance = sum_distance / 5;
  Serial.println(" Average: " + String(sum_distance));

  if (distance <= threshold){
    Serial.println("Approaching the wall");
    stop_motor();
    moving = 0;
    if (count%2 == 0) {
      turn(right_motor_speed, left_motor_speed, 90); 
      move_straight(right_motor_speed, left_motor_speed);
      delay(100);
      stop_motor();
      turn(right_motor_speed, left_motor_speed, 90); 
      count ++;}
    else {
      turn(right_motor_speed, left_motor_speed, -90); 
      move_straight(right_motor_speed, left_motor_speed);
      delay(100);
      stop_motor();
      turn(right_motor_speed, left_motor_speed, -90); 
      count ++;}
    } // if

  delay(200);}

  }
}

void stop_motor(){
  right_motor->setSpeed(0);
  left_motor->setSpeed(0);
  Serial.println("Motor stopped.");
  
}
void move_straight(int right_motor_speed, int left_motor_speed) {
  Serial.println("Moving straight.");
  right_motor->setSpeed(right_motor_speed);
  left_motor->setSpeed(left_motor_speed);
  left_motor->run(FORWARD);
  right_motor->run(BACKWARD);
}

void turn(int right_motor_speed, int left_motor_speed, int angle) {

  Serial.println("Robot turns " + String(angle) + "degrees angle!");
  
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
  Serial.println(String(moving_time));
}

int get_distance(){
  
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  
  // Calculating the distance
  distance = duration*0.034/2;
  
  // Prints the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  
  return distance;
}
