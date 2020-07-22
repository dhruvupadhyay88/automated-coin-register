#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C  lcd(0x27,2,1,0,4,5,6,7); 
void setup()
{
  // activate LCD module
  lcd.begin (16,2); // for 16 x 2 LCD module
  lcd.setBacklightPin(3,POSITIVE);
  lcd.setBacklight(HIGH);
}

void loop()
{
  lcd.home (); // set cursor to 0,0
  lcd.print(" tronixlabs.com"); 
  lcd.setCursor (0,1);        // go to start of 2nd line
  lcd.print(millis());
  delay(1000);
  lcd.setBacklight(LOW);      // Backlight off
  delay(250);
  lcd.setBacklight(HIGH);     // Backlight on
  delay(1000);
}
