#include <Adafruit_MotorShield.h>

Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
Adafruit_DCMotor *right_motor = AFMS.getMotor(1);
Adafruit_DCMotor *left_motor = AFMS.getMotor(2);
int right_motor_speed = 142;
int left_motot_speed = 150;
int turn_90 = 2159;
int moving_time = 2000;
int first = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); // set up Serial library at 9600 bps
  Serial.println("Adafruit Motorshield v2 - DC Motor test!");

  AFMS.begin();
}

int count = 0;

void loop() {

  if (first == 0){
    delay (3000);
    first ++;
  }
  // put your main code here, to run repeatedly:
  while (1){
    
  move_straight(right_motor_speed, left_motot_speed, 1000);
  turn(right_motor_speed, left_motot_speed, 90);
  
  }
}

void move_straight(int right_motor_speed, int left_motot_speed, int moving_time) {
  Serial.println("Adafruit moving straight.");
  right_motor->setSpeed(right_motor_speed);
  left_motor->setSpeed(left_motot_speed);
  left_motor->run(FORWARD);
  right_motor->run(BACKWARD);
  delay(moving_time);
}

void turn(int right_motor_speed, int left_motot_speed, int angle) {

  Serial.println("Adafruit turn " + String(angle) + "angle!");
  
  right_motor->setSpeed(right_motor_speed);
  left_motor->setSpeed(left_motot_speed);
  
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
  delay(moving_time);
}
