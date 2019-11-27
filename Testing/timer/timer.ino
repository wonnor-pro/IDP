unsigned long time_1;
unsigned long time_2;
unsigned long d_time;

void setup() {
  Serial.begin(9600);
}
void loop() {
  Serial.print("Time: ");
  
  time_1 = millis();
  delay(1000);
  time_2 = millis();

  d_time = time_2 - time_1;
  
  Serial.println(time_1); //prints time since program started
  Serial.print("Delta Time: ");
  Serial.println(d_time); //prints time since program started
  delay(1000);          // wait a second so as not to send massive amounts of data
}
