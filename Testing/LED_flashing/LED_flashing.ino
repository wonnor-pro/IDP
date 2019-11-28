#include <Adafruit_MotorShield.h>
//#include <chrono>


const int RLED_Pin = 5;
const int OLED_Pin = 4;

int led_status = LOW;
int if_led_flashing = true;
int led_count = 0;


void setup() {

  // Initialise LED
  pinMode(RLED_Pin, OUTPUT);
  digitalWrite (RLED_Pin, LOW);
  pinMode(OLED_Pin, OUTPUT);
  digitalWrite (OLED_Pin, LOW);
  
  // initialize timer2
  noInterrupts();           // disable all interrupts
  TCB0.CTRLB = TCB_CNTMODE_INT_gc; // Use timer compare mode
  TCB0.CCMP = 65000; // It's clocked at 250000 ticks per second; Value to compare with. This is 1/10th of the tick rate, so 25000 is 10 Hz
  TCB0.INTCTRL = TCB_CAPT_bm; // Enable the interrupt
  TCB0.CTRLA = TCB_CLKSEL_CLKTCA_gc | TCB_ENABLE_bm; // Use Timer A as clock, enable timer
  interrupts();             // enable all interrupts
  
  Serial.begin(9600); // Starts the serial communication
  Serial.println("Lawnmower Test!!!");

}


void loop() {
  while(1){}
  }


// Everytime the time interrupt happens, getting here
ISR(TCB0_INT_vect)
{
   // Do something
   Serial.println(String(led_count));
   if (led_count%4 == 0){
     if (led_status == LOW) 
     {Serial.println("Flash"); digitalWrite (RLED_Pin, HIGH);digitalWrite (OLED_Pin, HIGH); led_status = HIGH;}
     else {digitalWrite (RLED_Pin, LOW);digitalWrite (OLED_Pin, LOW); led_status = LOW;}
     led_count = led_count % 4; // 0.5 Hz
   }
   led_count = led_count + 1;
   //Clear interrupt flag
   TCB0.INTFLAGS = TCB_CAPT_bm;
}
