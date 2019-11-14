
#include <Adafruit_MotorShield.h>

Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
Adafruit_DCMotor *right_motor = AFMS.getMotor(1);
Adafruit_DCMotor *left_motor = AFMS.getMotor(2);

void setup() {
  Serial.begin(9600); // set up Serial library at 9600 bps
  Serial.println("Adafruit Motorshield v2 - DC Motor test!");

  AFMS.begin();
}

void loop() {

  Serial.println("Initialised");
  
  serialEvent();

  Serial.println("End Test");
  right_motor->run(RELEASE);
  left_motor->run(RELEASE);
  delay(300);
}

void run_motor(float motor_speed, Adafruit_DCMotor *motor)
{
  //-1 < motor_speed < 1 
  int abs_speed = (int)abs(motor_speed * 255);
  
  //set speed
  motor->setSpeed(abs_speed);

  //forwards or backwards
  if (motor_speed > 0){
    motor->run(FORWARD);
  }
  else{
    motor->run(BACKWARD);
  }
}

void serialEvent() {
  float dir, pace;
  int comma_index;
  String data;
  while (Serial.available()){
    // data format = "dir,pace"
    // -1 < dir < 1 & -1 < pace < 1
    data = Serial.readStringUntil('&');
  }
    comma_index = data.indexOf(',');

    // extract vals
    dir = data.substring(0, comma_index).toFloat();
    pace = data.substring(comma_index + 1).toFloat();

    // turn motors
    motor_control(dir, pace);
}

void motor_control(float dir, float pace) {
  float right_speed = 1;
  float  left_speed = 1;
    
//  if(dir >= 0){
//    right_speed = 1;
//    left_speed = 1 - 2 * dir;
//  }
//
//  else{
//    right_speed = 1 + 2 * dir;
//    left_speed = 1;
//  }

  //set speeds
  right_speed = right_speed * pace;
  left_speed = left_speed * pace;

  //run motors
  run_motor(right_speed, right_motor);
  run_motor(left_speed, left_motor);
  
//  feedback to pc
  Serial.println("(" + String(left_speed) + "," + String(right_speed) + ")");
}
