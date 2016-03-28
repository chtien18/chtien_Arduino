#include <SDISerial.h>
#include <string.h>
#define DATA_PIN 2
SDISerial connection(DATA_PIN);
char output_buffer[125]; // just for uart prints
char tmp_buffer[4];

//initialize variables
void setup(){
      connection.begin();
      Serial.begin(9600);//so we can print to standard uart
      //small delay to let the sensor do its startup stuff
      delay(3000);//3 seconds should be more than enough
}

//main loop
void loop(){
    //print to uart
    Serial.println("Begin Command: ?M!");

    //send measurement query (M) to the first device on our bus
    char* resp = connection.sdi_query("1I!",1000);//1 second timeout
    //this really just returns a message that tells you the maximum wait before the measurement is ready

    sprintf(output_buffer,"RECV: %s",resp?resp:"No Response Recieved!!");
    Serial.println(output_buffer);
    delay(10000);//sleep for 10 seconds before the next read
}
