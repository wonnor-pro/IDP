#include <Adafruit_MotorShield.h>

Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
Adafruit_DCMotor *mine_motor = AFMS.getMotor(3);

const int buttonpin = 0; // Motor underneath

int buttonState;
int a;
int if_north_up;
int temp;

void setup() {
  // put your setup code here, to run once:

  // Botton underneath
  pinMode(buttonpin, INPUT);

    // Initialise Serial communication
  Serial.begin(9600);
  Serial.println("Robot Test!!!");

  // Motor
  AFMS.begin();
  
}


// ----------------------------------------------------------------
// Minemotor

void reset_minemotor(){
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

void initialise_minemotor(){
  mine_motor->setSpeed(100);
  mine_motor->run(FORWARD); 
  a = 0;
} // initialise_minemotor

// ----------------------------------------------------------------

void flip_mine(){
  
  while (if_north_up == 0){
    buttonState = digitalRead(buttonpin);
    temp = buttonState;
//    Serial.println(String(buttonState));
    delay(100);
    buttonState = digitalRead(buttonpin);
    if (temp!=buttonState){a++; Serial.println(String("A changed ") + String(a));}
  
    if (a==6){
      Serial.println(String("Stop"));
      mine_motor->setSpeed(0);
      delay(1000);
      mine_motor->setSpeed(100);
      mine_motor->run(BACKWARD);
      delay(1000);
      mine_motor->setSpeed(0);
      if_north_up=2;

//  while (if_north_up == 1){
//    mine_motor->setSpeed(100);
//    mine_motor->run(BACKWARD);
//    delay(1000);
//    mine_motor->setSpeed(0);
//    if_north_up=2;
  //}
    
    } // if
  } // while
  
} // flip_mine


void loop() {
  // put your main code here, to run repeatedly:


    delay (5000);
    
    // Initialise Mine motor
    initialise_minemotor();

    // Detecting if north-up
    if_north_up = 0; //this var 0 will be replaced by hall sensor reading

    // flip_mine if not
    if (if_north_up == 0){a=0; flip_mine();}
    delay(1000);

    if (if_north_up == 1){a=0; flip_mine();}
    delay(1000);

    delay (10000);
}
