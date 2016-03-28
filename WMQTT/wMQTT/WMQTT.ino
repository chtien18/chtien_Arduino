//this sketch is used to test MQTT protocol
//connect Arduino to MQTT broker via GPRS module - SIMCOM (SIM800, SIM900)

#include <mqtt.h>
#include <SoftwareSerial.h>


char atCommand[50];
byte mqttMessage[127];
int mqttMessageLength=0;

String gsmStr = "            ";
String gprsStr = "          ";
char mqttSubject[50];
int index = 0;
byte data1;
boolean smsReady = false;
boolean smsSent = false;
boolean gprsReady = false;
boolean mqttSent = false;

SoftwareSerial GPRS(10, 11);
int sentCount = 0;

void setup() {
  pinMode(13,OUTPUT);
  Serial.begin(19200); //for debug port
  GPRS.begin(19200); // for GPRS module

}

void loop() {
  delay(3000);
  
  Serial.println("Checking if GPRS is ready");
  gprsReady = isGPRSReady();
  if (gprsReady==true){
    Serial.println("GPRS OK");
    }
  else{
    Serial.println("GPRS fail");
    } 
    
 // while(1);//wait here forever
}


boolean isGPRSReady(){
      GPRS.println("AT");
      delay(5000);
      GPRS.println("AT+CGATT?");
      index = 0;
      if (GPRS.available()){

          while (GPRS.available()){
          data1 =GPRS.read();
          //Serial.write(data1);
          gprsStr[index++] = data1;
          }
      }

      Serial.println("Check OK");
      Serial.print("gprs str = ");
      Serial.println(gprsStr);
      Serial.println("-------------");
      Serial.println(gprsStr.indexOf("+CGATT: 1"));
      if (gprsStr.indexOf("+CGATT: 1") > -1){
      Serial.println("GPRS OK");
      return true;
      }
      else {
      Serial.println("GPRS NOT OK");
      return false;
      }
}

