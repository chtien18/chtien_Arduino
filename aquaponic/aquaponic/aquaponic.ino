/* ***********************************************************************************************
*******************************************Aquaponic**********************************************
irrigation(): pin22
using lowpower library

*/


#include <LowPower.h>
#include <iGarden.h>
#include <Wire.h>

int led=13;
int flag=0;

void setup() {
  pinMode(led,OUTPUT);
  Serial.begin(9600);
  iGarden.initIrrigation(1); //Initialize irrigation 1
}

void loop() {
  
  if (flag==0){
    iGarden.irrigationON(1);
    digitalWrite(led,HIGH);
     send_status();
    
    flag=1;
    sleep_4_minute();


  }
  
  if (flag==1){
    iGarden.irrigationOFF(1);
    send_status();
    
    flag=0;
    sleep_120_minute();
    
 
  }
   
}

void sleep_4_minute(){
  digitalWrite(led,LOW);
  for(int i=0;i<=29;i++){
  LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);
  }
}

void sleep_120_minute(){
  digitalWrite(led,LOW);
  for (int i=0;i<=900;i++){
    LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);
  }
}

void send_status(){
  
  if (flag==0){
        Serial.println("irrigationON");
  }
  else Serial.println("irrigationOFF");
  
  Serial.println(flag);
  delay(100);
}
