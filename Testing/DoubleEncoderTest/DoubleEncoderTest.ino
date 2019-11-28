

#include <Adafruit_MotorShield.h>

Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_DCMotor *left_motor = AFMS.getMotor(1);

const int lencoder = 1;
const int rencoder = 7;
int buttonStateleft;
int buttonStateright;

void setup() {
  // put your setup code here, to run once:
  pinMode(lencoder, INPUT);
  pinMode(rencoder, INPUT);
  Serial.begin(9600); // Starts the serial communication
  AFMS.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  left_motor->setSpeed(50);
  left_motor->run(BACKWARD);
  buttonStateleft = digitalRead(lencoder);
  buttonStateright = digitalRead(rencoder);
  Serial.println(String(buttonStateleft));
  //Serial.println(String(buttonStateright));
  if (buttonStateleft == 1){
    if (buttonStateright == 1){
      Serial.println("Both sensors blocked");
    }
  }
}
