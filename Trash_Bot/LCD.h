#ifndef LCD_H
#define LCD_H

#include <LiquidCrystal_I2C.h>

void initLCD();
void runLCD();
bool i2CAddrTest(uint8_t addr);

#endif
