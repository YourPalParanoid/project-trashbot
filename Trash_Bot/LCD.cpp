/*
#include "LCD.h"
#include <Arduino.h>

// initialize the library with the numbers of the interface pins
// at address 0x27
// A5 is clock(scl), A4 is data(sda)
LiquidCrystal_I2C lcd(0x27, 16, 2);

void initLCD()
{
  if (!i2CAddrTest(0x27)) {
    lcd = LiquidCrystal_I2C(0x3F, 16, 2);
  }
  lcd.init();                // initialize the lcd
  lcd.backlight();           // Turn on backlight
  lcd.print("hello, world!");// Print a message to the LCD
}

void runLCD()
{
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(0, 1);// set the cursor to column 0, line 1
  // print the number of seconds since reset:
  lcd.print("Distance:");
  lcd.print(millis() / 1000);
}

bool i2CAddrTest(uint8_t addr) {
  Wire.begin();
  Wire.beginTransmission(addr);
  if (Wire.endTransmission() == 0) {
    return true;
  }
  return false;
}
*/