// IDP Project 28 Nov 2019
// Group 205

#include <Adafruit_MotorShield.h>

Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
Adafruit_DCMotor *right_motor = AFMS.getMotor(1);
Adafruit_DCMotor *left_motor = AFMS.getMotor(2);
Adafruit_DCMotor *mine_motor = AFMS.getMotor(3);

// defines pins numbers
const int trigPin = 12;  // Ultrasound sensor
const int echoPin = 11;  // Ultrasound sensor
const int buttonpin = 0; // Motor underneath
const int RLED_Pin = 5;  // LED_R
const int OLED_Pin = 4;  // LED_O

// Trigger
// defines pins numbers
const int trigPin_T = 9;
const int echoPin_T = 8;

// Moving motor variables
int right_motor_speed = 188;
int left_motor_speed = 200;
int turn_90 = 1619;
int moving_time;
int moving_straight_time_start = 3500;
int moving_straight_time = 3000;

// Determine turning left/right; 
int count = 0; 

// Distance Variable (Front Ultrasound)
int threshold = 20;
int collection_wall_threshold = 10;
long duration; // Ultrasound


// Trigger Variables
int threshold_T = 5;

// Status Variable
int if_first = 1;
int if_mine = 0;
int if_north_up = 0;
int if_in_collection = 0;
int buttonState; // botton for motor underneath

int a = 0;

// LED flashing variables
int led_status = LOW;

// Timer variable
unsigned long time_1;
unsigned long time_2;
unsigned long time_3;
unsigned long time_4;
unsigned long d_time1;
unsigned long d_time2;

// ===========================================================================================
// SETUP

void setup() {
  
  // Front Ultrasound Sensor
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  // Trigger
  pinMode(trigPin_T, OUTPUT);
  pinMode(echoPin_T, INPUT);
  
  // Botton underneath
  pinMode(buttonpin, INPUT);
  
  // Initialise LED
  pinMode(RLED_Pin, OUTPUT);
  digitalWrite (RLED_Pin, LOW);
  pinMode(OLED_Pin, OUTPUT);
  digitalWrite (OLED_Pin, LOW);
  
  // initialise timer2
  noInterrupts();                     // disable all interrupts
  TCB0.CTRLB = TCB_CNTMODE_INT_gc;    // Use timer compare mode
  TCB0.CCMP = 65000;                  // 65000 for approximately 2Hz
  TCB0.INTCTRL = TCB_CAPT_bm;         // Enable the interrupt
  TCB0.CTRLA = TCB_CLKSEL_CLKTCA_gc | TCB_ENABLE_bm; // Use Timer A as clock, enable timer
  interrupts();                       // enable all interrupts

  // Initialise Serial communication
  Serial.begin(9600);
  Serial.println("Robot Test!!!");

  // Motor
  AFMS.begin();
  
}

// ===========================================================================================
// FUNCTIONS

// ----------------------------------------------------------------
// Motor

void move_straight(int right_motor_speed, int left_motor_speed) {
  
  right_motor->setSpeed(right_motor_speed);
  left_motor->setSpeed(left_motor_speed);
  
  left_motor->run(FORWARD);
  right_motor->run(BACKWARD);
  
} // move_straight

// ----------------------------------------------------------------

void move_back(int right_motor_speed, int left_motor_speed) {
  
  right_motor->setSpeed(right_motor_speed);
  left_motor->setSpeed(left_motor_speed);
  
  left_motor->run(BACKWARD);
  right_motor->run(FORWARD);
  
} // move_back

// ----------------------------------------------------------------

void stop_motor(){
  
  right_motor->setSpeed(0);
  left_motor->setSpeed(0);
  
} // stop_motor

// ----------------------------------------------------------------

void turn(int right_motor_speed, int left_motor_speed, int angle) {
  
  right_motor->setSpeed(right_motor_speed);
  left_motor->setSpeed(left_motor_speed);
  
  if (angle < 0) {
      right_motor->run(BACKWARD);
      left_motor->run(BACKWARD);
      angle = -angle;
    } // if
    
  else{
      right_motor->run(FORWARD);
      left_motor->run(FORWARD);
    } // else

  moving_time = angle * ((turn_90) / 90);
  delay(moving_time);

} // turn

// ----------------------------------------------------------------
// Ultrasound

int get_single_distance(int trigPin, int echoPin){
  
  int distance_1;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance_1 = duration*0.034/2;
  
  return distance_1;
  
} // get_single_distance

// ----------------------------------------------------------------

int get_average_distance(int trigPin, int echoPin){

  int distance = 0;
  for (int i=0; i<5; i++){
    distance = distance + get_single_distance(trigPin, echoPin); 
    delay(10);
  } // for - getting sum of five readings from the ultrasound sensor
  
  // Take average
  int average = distance / 5;

  return average;
  
} // get_average_distance

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
  right_motor->setSpeed(25);
  left_motor->setSpeed(25);
  right_motor->run(BACKWARD);
  left_motor->run(FORWARD);
  a = 0;
} // initialise_minemotor

// ----------------------------------------------------------------

void flip_mine(){
  
  while (if_north_up == 0){
    buttonState = digitalRead(buttonpin);
    int temp = buttonState;
    Serial.println(String(buttonState));
    delay(100);
    buttonState = digitalRead(buttonpin);
    if (temp!=buttonState){a++;}
  
    if (a==4){
      mine_motor->setSpeed(0);
      delay(1000);
      mine_motor->setSpeed(100);
      mine_motor->run(BACKWARD);
      delay(1000);
      mine_motor->setSpeed(0);
      if_north_up=1;
    } // if
  } // while
  
} // flip_mine

// ----------------------------------------------------------------
// actions

void wall_action(){
  // count == 0, Turning right
  if (count == 0){
    turn(right_motor_speed, left_motor_speed, 90); //Turns right
    move_straight(right_motor_speed, left_motor_speed);
    delay(moving_straight_time);
    turn(right_motor_speed, left_motor_speed, 90); //Turns right
    count ++;
    } 

  // count == 1, Turning left
  else{
    turn(right_motor_speed, left_motor_speed, -90); //Turns left
    move_straight(right_motor_speed, left_motor_speed);
    delay(moving_straight_time);
    turn(right_motor_speed, left_motor_speed, -90); //Turns left
    count --;
  } // else
} // wall_action

// ===========================================================================================
// MAIN LOOP

void loop() {

  // --------------------------------------
  // INITIAL TURNING
  
  if (if_first == 1) {

    // Plug-in buffer
    delay(3000);
    reset_minemotor();
    delay(1000);

    // Go Straight for (moving_straight_time_start) time
    move_straight(right_motor_speed, left_motor_speed);
    delay(moving_straight_time_start);
    // Turn left
    turn(right_motor_speed, left_motor_speed, -90);
    stop_motor();

    // Unflag the status
    if_first = 0;
    
   } // if - initial turning
   

  // --------------------------------------
  // UPDATE ULTRASOUND DISTANCE (FRONT)
  
  int average = get_average_distance(trigPin, echoPin); 

  // --------------------------------------
  // UPDATE TRIGGER STATUS

  int average_T = get_average_distance(trigPin_T, echoPin_T); 
  // trigerred
  if (average_T < threshold_T) {if_mine = 1;}

  // --------------------------------------
  // UPDATE MINE STATUS

  // --------------------------------------
  // HANDLING MINE

  // If No Mine
  if (if_mine == 0){
    
    // NO Wall, Moving Straight
    if (average  > threshold) {move_straight(right_motor_speed, left_motor_speed);} // if
    // Wall, Turning
    if (average <= threshold) {wall_action();} // if average < threshold
    
  } // if_mine == 0


  // if Mine is detected
  if (if_mine == 1){

    // Turn off the LED
    digitalWrite (RLED_Pin, LOW);

    // Stop the Robot
    stop_motor();
    delay(1000);

    // Initialise Mine motor
    initialise_minemotor();

    // Detecting if north-up
    if_north_up = 0;

    // flip_mine if not
    if (if_north_up == 0){flip_mine();}
    delay(1000);
    
    // Turn to the wall
    if (count==0){turn(right_motor_speed, left_motor_speed,  90);}
    if (count==1){turn(right_motor_speed, left_motor_speed, -90);}
    stop_motor();

    // Move backwards until get to the wall
    time_1 = millis();
    move_back(right_motor_speed, left_motor_speed);
    while(1){
      int average_drop = get_average_distance(trigPin_T, echoPin_T);
      if (average_drop<threshold){break;}
    } // while
    time_2 = millis();
    
    // First time period
    d_time1 = time_2 - time_1;

    // Turning left (facing collection point)
    turn(right_motor_speed, left_motor_speed, -90);
    stop_motor();

    // Move straight until get to the wall
    time_3 = millis();
    move_straight(right_motor_speed, left_motor_speed);
    
    if_in_collection = 1;
    while(if_in_collection == 1){
      
      int average_drop = get_average_distance(trigPin, echoPin_T);

      // Stop at the wall
      if (average_drop < collection_wall_threshold){
        time_4 = millis();
        
        // Getting the Straight-move time period
        d_time2 = time_4 - time_3;
        
        stop_motor();
        delay(1000);
        
        // Release the mine
        reset_minemotor();
        delay(1000);
        
        // Move Back
        move_back(right_motor_speed, left_motor_speed);
        delay(d_time2);

        // Turn back - to the right (opposite to the wall)
        turn(right_motor_speed, left_motor_speed, 90);
        
        // Move back to the latest position
        move_straight(right_motor_speed, left_motor_speed);
        delay(d_time1);

        // Turn to the sweeping derection
        if (count == 0){turn(right_motor_speed, left_motor_speed, -90); if_in_collection = 1;} // if count == 0 (Turn left)
        if (count == 1){turn(right_motor_speed, left_motor_speed,  90); if_in_collection = 1;} // if count == 1 (Turn right)
        
      } // if stop at the wall
    } // if in collection
    
    // clear the mine_flag
    if_mine = 0;
    
  } // if mine is detected
  
} // Main loop ends


// ===========================================================================================
// TIME INTERRUPT

ISR(TCB0_INT_vect)
{

   // Flashing red if no mine
   if (if_mine == 0){
     if (led_status == LOW) {digitalWrite (RLED_Pin, HIGH); led_status = HIGH;} // if
     else {digitalWrite (RLED_Pin, LOW); led_status = LOW;} //else
   }

   // Flashing orange if no mine
   if (if_mine == 1){
     if (led_status == LOW) {digitalWrite (OLED_Pin, HIGH); led_status = HIGH;} // if
     else {digitalWrite (OLED_Pin, LOW); led_status = LOW;} // else
   }
   
   // Clear interrupt flag
   TCB0.INTFLAGS = TCB_CAPT_bm;
}
