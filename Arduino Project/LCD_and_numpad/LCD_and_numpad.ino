#include <Keypad.h>

#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>


LiquidCrystal_I2C  lcd(0x27,2,1,0,4,5,6,7); // 0x27 is the I2C bus address for an unmodified backpack
int x = 0;
const byte ROWS = 4;
const byte COLS = 3;

char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};

byte rowPins[ROWS] = {8, 7, 6, 5};
byte colPins[COLS] =  {4, 3, 2};

Keypad kpd = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);
 



void setup() {
  
  lcd.begin(16, 2); // begins connection to the LCD module
  lcd.setBacklightPin(3,POSITIVE);
  lcd.setBacklight(HIGH);
}


void loop() {
  
 
  char customKey = customKeypad.getKey();
   if (customKey){
    
    lcd.setCursor(1, 0); 
    lcd.print(customKey);
  }
}
