/*
 * 
 * Author: Tien Cao-hoang
 * Website: http://chtien.xyz
 * 
 * Grove soil moisture sensor is conected to Arduino.  
 * The soil moisture is displayed on LCD
 */

// include the library code:
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

int soil_moisture_pin = A15;    // select the input pin for the soil moisture signal pin
int soil_moisture_value = 0;    // variable to store the value coming from the sensor
int desired_moisture =600;      

int button_pin =A0;
int button_value=0;

int relay = 22;                 // relay pin  
void setup() {
  pinMode(soil_moisture_pin,INPUT);
  pinMode(button_pin,INPUT);
  // set up the LCD's number of columns and rows: 
  lcd.begin(16, 2);
  Serial.begin(9600);
  
  // Print a message to the LCD.
 

  //set relay as an output
  pinMode(relay,OUTPUT);
  digitalWrite(relay,LOW); 
}

void loop() {
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(0,0);
  lcd.print("Soil moisture:");
   
  lcd.setCursor(0, 1);
  soil_moisture_value = analogRead(soil_moisture_pin);            
  lcd.print(soil_moisture_value);

  lcd.setCursor(8,1);
  button_value=analogRead(button_pin);
  Serial.println(button_value);

  if (button_value>700 && button_value<730)
  {
         lcd.clear();
         lcd.print("desired moisture");
         lcd.setCursor(0,1);
         lcd.print(desired_moisture);
         delay(2000);
         button_value=analogRead(button_pin);
         while(button_value>800 && button_value!=132 && button_value!=307 )
            {
              button_value=analogRead(button_pin); 
              if (button_value==132) 
                {
                  desired_moisture++;
                  delay(500);
                  button_value=analogRead(button_pin); 
                  lcd.setCursor(0,1);
                  lcd.print(desired_moisture); 
                }
              if (button_value==307) 
                {
                  desired_moisture--; 
                  delay(500);
                  button_value=analogRead(button_pin); 
                  lcd.setCursor(0,1);
                  lcd.print(desired_moisture); 
                 }
              delay(20);
            }
         lcd.clear();
         
  }
  
  if (soil_moisture_value<desired_moisture) digitalWrite(relay,LOW); //turn on relay
  else digitalWrite(relay,HIGH);//turn off relay
  
  delay(1000);
}

