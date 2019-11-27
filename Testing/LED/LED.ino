int led = LOW;

void setup() {
  Serial.begin(9600); //initialize serial COM at 9600 baudrate
  pinMode(LED_BUILTIN, OUTPUT); //make the LED pin (13) as output
  digitalWrite (LED_BUILTIN, LOW);
  
  // initialize timer2
  noInterrupts();           // disable all interrupts
  TCB0.CTRLB = TCB_CNTMODE_INT_gc; // Use timer compare mode
  TCB0.CCMP = 250000; // Value to compare with. This is 1/10th of the tick rate, so 10 Hz
  TCB0.INTCTRL = TCB_CAPT_bm; // Enable the interrupt
  TCB0.CTRLA = TCB_CLKSEL_CLKTCA_gc | TCB_ENABLE_bm; // Use Timer A as clock, enable timer
  interrupts();             // enable all interrupts

}

void loop() {
  while (1) {
    delay(1000);
  }
}


ISR(TCB0_INT_vect)
{
   // Do something
   Serial.println("Flashing");
   if (led == LOW) {digitalWrite (LED_BUILTIN, HIGH); led = HIGH;}
   else {digitalWrite (LED_BUILTIN, LOW); led = LOW;}
   // Clear interrupt flag
   TCB0.INTFLAGS = TCB_CAPT_bm;
}
