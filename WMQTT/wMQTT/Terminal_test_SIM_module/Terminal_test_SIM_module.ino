//Serial Relay - Arduino will patch a 
//serial link between the computer and the GPRS Shield
//at 19200 bps 8-N-1
//Computer is connected to Hardware UART
//GPRS Shield is connected to the Software UART 
#include <SoftwareSerial.h>
SoftwareSerial GPRS(10, 11);
unsigned char buff[64]; // buff array for data recieve over serial port
int count=0;     // counter for buff array 
void setup()
{
 GPRS.begin(19200);               // the GPRS baud rate   
 Serial.begin(19200);             // the Serial port of Arduino baud rate.
}
void loop()
{
 if (GPRS.available())              // if date is comming from softwareserial port ==> data is comming from gprs shield
 {
   while(GPRS.available())          // reading data into char array 
   {
     buff[count++]=GPRS.read();     // writing data into array
     if(count == 64)break;
    }
    Serial.println("----------respone----------");
   Serial.write(buff,count);            // if no data transmission ends, write buff to hardware serial port
   Serial.println(buff[1]);
   Serial.println("---------------------------");
   clearbuffArray();              // call clearbuffArray function to clear the storaged data from the array
   count = 0;                       // set counter of while loop to zero
 }
 if (Serial.available())            // if data is available on hardwareserial port ==> data is comming from PC or notebook
   GPRS.write(Serial.read());       // write it to the GPRS shield
}
void clearbuffArray()              // function to clear buff array
{
 for (int i=0; i<count;i++)
   { buff[i]=NULL;}                  // clear all index of array with command NULL
}
