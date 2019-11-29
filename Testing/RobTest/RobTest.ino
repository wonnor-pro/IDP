#include <Adafruit_MotorShield.h>
Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
Adafruit_DCMotor *right_motor = AFMS.getMotor(1);
Adafruit_DCMotor *left_motor = AFMS.getMotor(2);
Adafruit_DCMotor *mine_motor = AFMS.getMotor(3);

void setup() {
  // put your setup code here, to run once:
  AFMS.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  right_motor->setSpeed(25);
  left_motor->setSpeed(25);
  mine_motor->setSpeed(100);
  left_motor->run(FORWARD);
  right_motor->run(BACKWARD);
  mine_motor->run(FORWARD);
}
