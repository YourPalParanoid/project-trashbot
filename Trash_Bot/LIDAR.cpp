/*
#include"LIDAR.h"
#include<Arduino.h>

// initialize the Lidars
// first sensor is at 0x29
Adafruit_VL53L0X lox = Adafruit_VL53L0X();

void initLidar()
{
  Serial.println("Adafruit VL53L0X test");
  if (!lox.begin()) {
    Serial.println(F("Failed to boot VL53L0X"));
    while(1);
  }

  Serial.println(F("Lidar Booted :]\n\n"));
}

VL53L0X_RangingMeasurementData_t runLidar()
{
  VL53L0X_RangingMeasurementData_t measure;

  lox.rangingTest(&measure, false);

  if(measure.RangeStatus != 4)
  {
    Serial.print("Distance (mm): ");
    Serial.println(measure.RangeMilliMeter);
  }
  else
  {
    Serial.println("Out of Range :[");
  }
}
*/