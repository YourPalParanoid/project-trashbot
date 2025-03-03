#include <Servo.h>
Servo servo;

int const trigPin = 6;  //green
int const echoPin = 5;  //blue

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(115200);
  servo.attach(3);
  servo.write(180);
}
void loop() {
  int duration, distance;
  digitalWrite(trigPin, HIGH);
  delay(1);
  digitalWrite(trigPin, LOW);         // Measure the pulse input in echo pin
  duration = pulseIn(echoPin, HIGH);  // Distance is half the duration devided by 29.1 (from datasheet)
  distance = (duration / 2) / 29.1;   // if distance less than 0.5 meter and more than 0 (0 or less means over range)

  // Open Trash
  if (distance < 10) {
    servo.write(90);
    delay(3000);
  }
  // Close Trash
  else {
    servo.write(0);
    delay(100);
  }

  //servo.write(0);

  Serial.println(distance);
  delay(100);
}