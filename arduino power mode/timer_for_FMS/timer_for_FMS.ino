/* ***********************************************************************************************
*******************************************Aquaponic**********************************************
irrigation(): pin22
using lowpower library

*/


#include <LowPower.h>

#include <Wire.h>

int led=13;
int flag=0;

void setup() {
  pinMode(led,OUTPUT);
  Serial.begin(9600);
 
}

void loop() {
    digitalWrite(led,HIGH);
    delay(120000);
    digitalWrite(led,LOW);
    sleep_54_minute();
    
  }
   

void sleep_54_minute(){
  digitalWrite(led,LOW);
  for (int i=0;i<=405;i++){
    LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);
  }
}

