#include <Servo.h>
// #include"LCD.h"
// #include"LIDAR.h"
#include "Adafruit_VL53L0X.h"
#include <LiquidCrystal_I2C.h>

#define LIDAR1_ADDRESS 0x30

// angled one
#define LIDAR2_ADDRESS 0x31

//xshut pins
#define LIDAR1_XSHUT 7

// angled one
#define LIDAR2_XSHUT 8


LiquidCrystal_I2C lcd(0x27, 16, 2);

Adafruit_VL53L0X lox1 = Adafruit_VL53L0X();
Adafruit_VL53L0X lox2 = Adafruit_VL53L0X();

Servo servo;

int const openTrigPin = 6;  // Green
int const openEchoPin = 5;  // Blue

int const motorPin = 3;  // Motor

VL53L0X_RangingMeasurementData_t measure1;
VL53L0X_RangingMeasurementData_t measure2;

void setup() {
  Serial.begin(115200);

  // wait until serial port opens for native USB devices
  while (! Serial) { delay(1); }

  pinMode(LIDAR1_XSHUT, OUTPUT);
  pinMode(LIDAR2_XSHUT, OUTPUT);

  Serial.println(F("Shutdown pins inited..."));

  digitalWrite(LIDAR1_XSHUT, LOW);
  digitalWrite(LIDAR2_XSHUT, LOW);

  Serial.println(F("Both in reset mode...(pins are low)"));
  
  
  Serial.println(F("Starting..."));

  // all reset
  digitalWrite(LIDAR1_XSHUT, LOW);    
  digitalWrite(LIDAR2_XSHUT, LOW);
  delay(10);

  Serial.println("reset both lidar");

  // all unreset
  digitalWrite(LIDAR1_XSHUT, HIGH);
  digitalWrite(LIDAR2_XSHUT, HIGH);
  delay(10);

  Serial.println("unreset both lidar");

  // activating LOX1 and resetting LOX2
  digitalWrite(LIDAR1_XSHUT, HIGH);
  digitalWrite(LIDAR2_XSHUT, LOW);

  Serial.println("activating lidar1");

  // initing LOX1
  if(!lox1.begin(LIDAR1_ADDRESS)) {
    Serial.println(F("Failed to boot first VL53L0X"));
    while(1);
  }
  
  Serial.println("lidar 1 inited");
  delay(10);

  // activating LOX2
  digitalWrite(LIDAR2_XSHUT, HIGH);
  delay(10);

  //initing LOX2
  if(!lox2.begin(LIDAR2_ADDRESS)) {
    Serial.println(F("Failed to boot second VL53L0X"));
    while(1);
  }
  Serial.println("lidar 2 inited");

/*
  // initLCD();
  lcd = LiquidCrystal_I2C(0x27, 16, 2);
  lcd.init();                  // initialize the lcd
  lcd.backlight();             // Turn on backlight
  lcd.print("hello, world!");  // Print a message to the LCD
  */

  // pinMode(openTrigPin, OUTPUT);
  // pinMode(openEchoPin, INPUT);
  // pinMode(fillTrigPin, OUTPUT);
  // pinMode(fillEchoPin, INPUT);

  //servo.attach(motorPin);

  //servo.write(180);
}
void loop() {
  // runLidar();
  Serial.println("am i even making it past init :[");
  lox1.rangingTest(&measure1, false);
  lox2.rangingTest(&measure2, false);

  // calculate accurate measurement of angled lox2
  double measure2MilliAdjusted = measure2.RangeMilliMeter * cos(45);

  Serial.println(F("measure 1: "));
  Serial.println(measure1.RangeMilliMeter);

  Serial.println(F("measure 2: "));
  Serial.println(measure2MilliAdjusted);

  // runLCD();
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(0, 1);  // set the cursor to column 0, line 1
  // print the number of seconds since reset:
  lcd.print("Distance:");
  lcd.print((measure1.RangeMilliMeter + measure2.RangeMilliMeter)/2);

  // when remaining space is <= 20 mm
  if (measure1.RangeMilliMeter <= 20)
  {
    lcd.setCursor(0, 1);
    lcd.print("Empty Me!");
  }
  else
  {
    lcd.setCursor(0, 1);
    lcd.print("");
  }


  int open_Duration, open_Distance;
  digitalWrite(openTrigPin, HIGH);
  delay(1);
  digitalWrite(openTrigPin, LOW);              // Measure the pulse input in echo pin
  open_Duration = pulseIn(openEchoPin, HIGH);  // Distance is half the duration devided by 29.1 (from datasheet)
  open_Distance = (open_Duration / 2) / 29.1;  // if distance less than 0.5 meter and more than 0 (0 or less means over range)

  //Open Trash
  if (abs(open_Distance) < 10) {
    servo.write(80);
    delay(3000);
  }
  // Close Trash
  else {
    servo.write(0);
    delay(100);
  }

  // Ultrasonic sensor for detecting Trash fill
  int fill_Duration, fill_Distance;
  // digitalWrite(fillTrigPin, HIGH);
  // delay(1);
  // digitalWrite(fillTrigPin, LOW);              // Measure the pulse input in echo pin
  // fill_Duration = pulseIn(fillEchoPin, HIGH);  // Distance is half the duration devided by 29.1 (from datasheet)
  // fill_Distance = (fill_Duration / 2) / 29.1;  // if distance less than 0.5 meter and more than 0 (0 or less means over range)

  // TODO Display "Fill" once a certain fill_distance is reached for a certain amount of times

  Serial.print("Open: ");
  Serial.print(abs(open_Distance));

  Serial.print("        ");

  Serial.print("Fill: ");
  Serial.print(abs(fill_Distance));
  Serial.println();
  delay(100);
}
