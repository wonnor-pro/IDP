// defines pins numbers
const int trigPin = 4;
const int echoPin = 3;
const int trigPin_F = 11;
const int echoPin_F = 10;
// defines variables
long duration;
int distance;

void setup() {
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  pinMode(trigPin_F, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin_F, INPUT); // Sets the echoPin as an Input
  Serial.begin(9600); // Starts the serial communication
}

void loop() {
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance= duration*0.034/2;
//  Serial.print("Duratiobn: ");
//  Serial.println(duration);
  // Prints the distance on the Serial Monitor
  Serial.print("B-Distance: ");
  Serial.println(distance);

    // Clears the trigPin
  digitalWrite(trigPin_F, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin_F, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin_F, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin_F, HIGH);
  // Calculating the distance
  distance= duration*0.034/2;
//  Serial.print("Duratiobn: ");
//  Serial.println(duration);
  // Prints the distance on the Serial Monitor
  Serial.print("F-Distance: ");
  Serial.println(distance);
  Serial.println("=======================================================");
  delay(500);

}
