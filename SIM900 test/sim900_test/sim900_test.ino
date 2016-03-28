#include <SoftwareSerial.h>

SoftwareSerial mySerial(10,11);//RX,TX

void setup()
{
 mySerial.begin(9600);               // the GPRS baud rate   
 Serial.begin(9600);                 // the GPRS baud rate   
}

void loop()
{
 if (mySerial.available())
   Serial.write(mySerial.read());
 if (Serial.available())
   mySerial.write(Serial.read());  

}
