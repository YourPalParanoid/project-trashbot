#include<Servo.h> 
Servo servo; 

int const openTrigPin = 6; // Green
int const openEchoPin = 5; // Blue

int const fillTrigPin = 11; // Orange
int const fillEchoPin = 10; // Yellow

int const motorPin = 3; // Motor 

void setup() 
{ 
  pinMode(openTrigPin, OUTPUT);  
  pinMode(openEchoPin, INPUT);
  pinMode(fillTrigPin, OUTPUT);  
  pinMode(fillEchoPin, INPUT);

  Serial.begin(115200);  
  servo.attach(motorPin); 

  //servo.write(180);
} 
void loop() 
{        
  int open_Duration, open_Distance; 
  digitalWrite(openTrigPin, HIGH);  
  delay(1); 
  digitalWrite(openTrigPin, LOW);// Measure the pulse input in echo pin 
  open_Duration = pulseIn(openEchoPin, HIGH);// Distance is half the duration devided by 29.1 (from datasheet) 
  open_Distance = (open_Duration/2) / 29.1;// if distance less than 0.5 meter and more than 0 (0 or less means over range)
  
  //Open Trash
  if (abs(open_Distance) < 10) {
    servo.write(80);
    delay(3000);
  }
  // Close Trash
  else
  {
    servo.write(0);
    delay(100);
  }

  // Ultrasonic sensor for detecting Trash fill
  int fill_Duration, fill_Distance; 
  digitalWrite(fillTrigPin, HIGH);  
  delay(1); 
  digitalWrite(fillTrigPin, LOW);// Measure the pulse input in echo pin 
  fill_Duration = pulseIn(fillEchoPin, HIGH);// Distance is half the duration devided by 29.1 (from datasheet) 
  fill_Distance = (fill_Duration/2) / 29.1;// if distance less than 0.5 meter and more than 0 (0 or less means over range)

  // TODO Display "Fill" once a certain fill_distance is reached for a certain amount of times

  Serial.print("Open: ");
  Serial.print(abs(open_Distance));

  Serial.print("        ");

  Serial.print("Fill: ");
  Serial.print(abs(fill_Distance));
  Serial.println();
  delay(100); 
}
