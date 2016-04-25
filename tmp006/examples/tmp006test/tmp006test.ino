#include <Wire.h>
#include "TMP006.h"

void setup()
{
  TMP006.begin();                // join i2c bus (address optional for master)
  Serial.begin(9600);          // start serial communication at 9600bps
}

double reading = 0;
void loop()
{
   TMP006.begin();
   TMP006.setmode(mode1);
   reading=TMP006.gettmp();
   Serial.println(reading);
   delay(250);
}

