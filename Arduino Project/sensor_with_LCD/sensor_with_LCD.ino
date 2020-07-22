#include <Keypad.h>

#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>


LiquidCrystal_I2C  lcd(0x27,2,1,0,4,5,6,7); // 0x27 is the I2C bus address for an unmodified backpack
int amount = 0;
int temp = 0;
int x_value=8;
int sum = 0;
int change = 0;
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

Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

 


 



void setup() {
  pinMode (A0, INPUT);
  pinMode (A3, INPUT);
  pinMode (A6, INPUT);
  pinMode (A8, INPUT);
  pinMode (A12, INPUT);
  
  lcd.begin(16, 2); // begins connection to the LCD module
  lcd.setBacklightPin(3,POSITIVE);
  lcd.setBacklight(HIGH);
}
int value_dime;
int value_nickel;
int value_quarter;
int value_loonie;
int value_toonie;
int count = 1;
unsigned long sensor_delay = 0;
unsigned long numpad_delay = 0;
void loop() {
  
  if(millis() - sensor_delay >= 1000) {
    sensor_delay = millis();
    value_dime = analogRead(A0); // reads the analog input from the IR distance sensor
    value_nickel = analogRead(A3);
    value_quarter = analogRead(A6);
    value_loonie = analogRead(A8);
    value_toonie = analogRead(A12);
  
    lcd.setCursor(0, 0); // sets the cursor of the LCD module to the first line
    lcd.print("Sum");
    lcd.setCursor(4,0);
    lcd.print("$");
    lcd.setCursor(5, 0); // sets the cursor of the LCD module to the fourth character
    lcd.print(amount);
    lcd.setCursor(9,0);
    lcd.print("C:$");
    lcd.setCursor(0, 1); // sets the cursor of the LCD module to the first line
    lcd.print("Change");
    lcd.setCursor(7,1);
    lcd.print("$");
     // prints analog value on the LCD module
    if ((value_dime) < 900)
    {
      amount += 10;
      temp += 10;
    }
    if ((value_nickel) < 900)
    {
      amount += 5;
      temp += 5;
    }
    if ((value_quarter) < 900)
    {
      amount += 25;
      temp += 25;
    }
    if ((value_loonie) < 900)
    {
      amount += 100;
      temp += 100;
    }
    if ((value_toonie) < 900)
    {
      amount += 200;
      temp += 200;
    }
  }

  if(millis() - numpad_delay >= 100) {
    numpad_delay = millis();
    char customKey = customKeypad.getKey();
    if (customKey){
      
      if (count = 1){
        lcd.setCursor(x_value,1);
        lcd.print(customKey);
        sum += customKey*1000;
        x_value++;
        count++;
      }
      if (count = 2){
        lcd.setCursor(x_value,1);
        lcd.print(customKey);
        sum += customKey*100;
        x_value++;
        count++;
      }
      if (count = 3){
        lcd.setCursor(x_value,1);
        lcd.print(customKey);
        sum += customKey*10;
        x_value++;
        count++;
      }
      if (count = 4){
        lcd.setCursor(x_value,1);
        lcd.print(customKey);
        sum += customKey*1;
        x_value++;
        count++;
      }
      if (count > 4){
       change = temp - sum;
       y = 0;
       lcd.setCursor(12,0);
       lcd.print(change);
       x_value = 8;
       count = 0;
       s
       
        
      }
      
    }
    


        
       
    }
}

  
