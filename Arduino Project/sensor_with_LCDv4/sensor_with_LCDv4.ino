#include <Keypad.h>

#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h> 


LiquidCrystal_I2C  lcd(0x27,2,1,0,4,5,6,7); // 0x27 is the I2C bus address for an unmodified backpack
Servo myservo;
int amount = 0;
int temp = 0;
int x_value=7;
int sum = 0;
int clearr = '    ';
int change = 0;
const byte ROWS = 4;
const byte COLS = 3;
int pos = 82 ; 
int hole4 = 0;
int hole5 = 0;

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
  myservo.attach(34);
  
  lcd.begin(16, 2); // begins connection to the LCD module
  lcd.setBacklightPin(3,POSITIVE);
  lcd.setBacklight(HIGH);
int t = 1;
}
int value_dime;
int value_nickel;
int value_quarter;
int value_loonie;
int value_toonie;
int count = 1;
int t = 0;
unsigned long sensor_delay = 0;
unsigned long numpad_delay = 0;
void loop() {
 
  
  if(millis() - sensor_delay >= t) {
    t = 1;
    sensor_delay = millis();
    value_dime = analogRead(A3); // reads the analog input from the IR distance sensor
    value_nickel = analogRead(A8);
    value_quarter = analogRead(A12);
    value_loonie = analogRead(A6);
    value_toonie = analogRead(A0);
  
    lcd.setCursor(0, 0); // sets the cursor of the LCD module to the first line
    lcd.print("Sum");
    lcd.setCursor(4,0);
    lcd.print("$");
    lcd.setCursor(5, 0); // sets the cursor of the LCD module to the fourth character
    lcd.print(amount);
    lcd.setCursor(9,0);
    lcd.print("C:$");
    lcd.setCursor(0, 1); // sets the cursor of the LCD module to the first line
    lcd.print("Price");
    lcd.setCursor(6,1);
    lcd.print("$");
     // prints analog value on the LCD module
    if ((value_dime) < 920)
    {
      amount += 10;
      temp += 10;
      t = 1000;
      
      
    }
    if ((value_nickel) < 910)
    {
      amount += 5;
      temp += 5;
       t = 1000;
      
    }
    if ((value_quarter) < 900)
    {
      amount += 25;
      temp += 25;
       t = 1000;
      
    }
    if ((value_loonie) < 880)
    {
      amount += 100;
      temp += 100;
      t = 1000;
      hole4 = 1;
      hole5 = 0;
      
    }
    if ((value_toonie) < 920)
    {
      amount += 200;
      temp += 200;
      t = 1000;
      hole5 = 1;
      hole4 = 0;
      
    }
  }

 
    
    char customKey = customKeypad.getKey();
    if (customKey){
      
      if (customKey == '*'){
          
          t = 5000;
          
          lcd.setCursor(5,0);
          lcd.print(' ');
          lcd.setCursor(6,0);
          lcd.print(' ');
          lcd.setCursor(7,0);
          lcd.print(' ');
          lcd.setCursor(8,0);
          lcd.print(' ');
          amount = 0;
          temp = 0;
          for(pos = 82; pos >= 0; pos -= 1) // goes from 0 degrees to 180 degrees 
        {                                  // in steps of 1 degree 
           myservo.write(pos);              // tell servo to go to position in variable 'pos' 
           delay(7);                       // waits 15ms for the servo to reach the position 
        } 
          delay(2500);
          for(pos = 0; pos<=82; pos+=1)     // goes from 180 degrees to 0 degrees 
        {                                
           myservo.write(pos);              // tell servo to go to position in variable 'pos' 
           delay(7);                       // waits 15ms for the servo to reach the position 
        }
          
      }
      else if (customKey == '#' ) {                                       
        if (hole4 == 1){
         amount += 100;
         temp += 100;
         hole4 = 0;
        }
        if (hole5 == 1){
         amount -= 100;
         temp -= 100;
         hole5 = 0;
        
      }
      }
    
          
     
      else if (count == 1){
        lcd.setCursor(x_value,1);
        lcd.print(customKey);
        sum += (customKey-'0')*1000;
        x_value++;
        count++;
      }
      else if (count == 2){
        lcd.setCursor(x_value,1);
        lcd.print(customKey);
        sum += (customKey-'0')*100;
        x_value++;
        count++;
      }
      else if (count == 3){
        lcd.setCursor(x_value,1);
        lcd.print(customKey);
        sum += (customKey-'0')*10;
        x_value++;
        count++;
      }
      else  {
        lcd.setCursor(x_value,1);
        lcd.print(customKey);
        sum += (customKey-'0')*1;
        change = temp - sum;
        temp = 0;
        sum = 0;
        lcd.setCursor(12,0);
        lcd.print(change);
        delay (4000);
        lcd.setCursor(7,1);
        lcd.print(' ' );
        lcd.setCursor(8,1);
        lcd.print(' ' );
        lcd.setCursor(9,1);
        lcd.print(' ' );
        lcd.setCursor(10,1);
        lcd.print(' ' );
        lcd.setCursor(12,0);
        lcd.print(' ' );
        lcd.setCursor(13,0);
        lcd.print(' ' );
        lcd.setCursor(14,0);
        lcd.print(' ' );
        lcd.setCursor(15,0);
        lcd.print(' ' );
        change = 0;
        count = 1;
        x_value = 7;
          
        
    }
     
    }

}

    
     
       
       
       
        

    
  
    
    


        
       
    


  
