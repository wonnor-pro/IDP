#include <Adafruit_MotorShield.h>
const int buttonpin = 0;
Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
Adafruit_DCMotor *mine_motor = AFMS.getMotor(3);

int harsh = 0;
int a = 0;
int b = 0;
int temp = 0;
int buttonState = 0;
int shiv = 0;


void setup() {
  // put your setup code here, to run once:
  pinMode(buttonpin, INPUT);
  Serial.begin(9600); // Starts the serial communication
  AFMS.begin();

}

void loop() {
  // put your main code here, to run repeatedly:
  while (shiv==0){
  function2();
  shiv++;
  }
  
  if (harsh==0){
  mine_motor->setSpeed(100);
  mine_motor->run(FORWARD);
  buttonState = digitalRead(buttonpin);
  Serial.println(String(buttonState));
  }

  if (harsh==1){
    mine_motor->setSpeed(0);
    delay(1000);
    mine_motor->setSpeed(100);
    mine_motor->run(BACKWARD);
    delay(1000);
    mine_motor->setSpeed(0);
    harsh=2;
  }

 while (harsh==0){
  function();
}
}

void function(){
  buttonState = digitalRead(buttonpin);
  temp = buttonState;
  Serial.println(String(buttonState));
  delay(100);
  buttonState = digitalRead(buttonpin);
  if (temp!=buttonState){
    a++;
    Serial.println("A Has been incremented!");
  }
  if (a==4){
    harsh = 1;
  }
}

void function2(){
  buttonState = digitalRead(buttonpin);
  while(buttonState==0){
    Serial.println("IN THE LOOP");
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
