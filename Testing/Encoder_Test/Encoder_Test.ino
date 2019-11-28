const int coder = 1;
int buttonState;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); // Starts the serial communication
  Serial.println("Lawnmower Test!!!");
  pinMode(coder, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  buttonState = digitalRead(coder);
  Serial.println(String(buttonState));
}
