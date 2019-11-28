#include <Adafruit_MotorShield.h>
const int buttonpin = 0;
Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
Adafruit_DCMotor *mine_motor = AFMS.getMotor(3);

int buttonState;
int temp;

void setup() {
  // put your setup code here, to run once:
  pinMode(buttonpin, INPUT);
  Serial.begin(9600); // Starts the serial communication
  AFMS.begin();


}

void loop() {
  // put your main code here, to run repeatedly:
  delay(100);
  mine_motor->setSpeed(100);
  mine_motor->run(FORWARD);
  buttonState = digitalRead(buttonpin);
  if (buttonState!=temp){
    Serial.println("A Has been incremented!");
  }
  Serial.println(String(buttonState));
  temp = buttonState;
}
