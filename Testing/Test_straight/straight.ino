#include <Adafruit_MotorShield.h>

Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
Adafruit_DCMotor *right_motor = AFMS.getMotor(1);
Adafruit_DCMotor *left_motor = AFMS.getMotor(2);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); // set up Serial library at 9600 bps
  Serial.println("Adafruit Motorshield v2 - DC Motor test!");

  AFMS.begin();
}

int count = 0;

void loop() {
  // put your main code here, to run repeatedly:
  while (1){
  right_motor->setSpeed(96);
  left_motor->setSpeed(100);

  left_motor->run(FORWARD);
  right_motor->run(BACKWARD);
  delay(2500);}
}
