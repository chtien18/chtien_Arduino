// **** INCLUDES *****
//*****this project is the timer
// turn on every hour. 
// RTC DS1307
// analog pin 4 to SDA. Connect Arduino analog pin 5 to SCL.

#include "LowPower.h"
#include <Wire.h>
#include <Time.h>
#include <DS1307RTC.h>

void setup()
{
  Serial.begin(9600);
  //while(!Serial);
  delay(200);
  pinMode(13,OUTPUT);
  pinMode(12,OUTPUT);
}

void loop() 
{

  
  // ATmega328P, ATmega168
  LowPower.idle(SLEEP_8S, ADC_OFF, TIMER2_OFF, TIMER1_OFF, TIMER0_OFF, SPI_OFF, USART0_OFF, TWI_OFF);


  // Do something here
  // Example: Read sensor, data logging, data transmission.
  tmElements_t tm;
  if (RTC.read(tm)) {
    Serial.print("Ok, Time = ");
    print2digits(tm.Hour);
    Serial.write(':');
    int My_Minute=tm.Minute;
    print2digits(My_Minute);
    
    Serial.write(':');
    print2digits(tm.Second);
    int My_Second=tm.Second;
    //print2digits(My_Second);
    
    Serial.print(", Date (D/M/Y) = ");
    Serial.print(tm.Day);
    Serial.write('/');
    Serial.print(tm.Month);
    Serial.write('/');
    Serial.print(tmYearToCalendar(tm.Year));
    Serial.println();
      if (My_Minute==0 || My_Minute==1)
    //if (My_Second==0 || My_Second==1)
        {
          digitalWrite(13,HIGH);
          //digitalWrite(12,HIGH);
          delay(180000); //delay 5 minutes
          digitalWrite(13,LOW);
          //digitalWrite(12,LOW);
        }
  } 
  else {
    if (RTC.chipPresent()) {
      Serial.println("The DS1307 is stopped.  Please run the SetTime");
      Serial.println("example to initialize the time and begin running.");
      Serial.println();
    } else {
      Serial.println("DS1307 read error!  Please check the circuitry.");
      Serial.println();
    }
    delay(9000);
  }

  delay(600);
  
}

void print2digits(int number) {
  if (number >= 0 && number < 10) {
    Serial.write('0');
  }
  Serial.print(number);
}
