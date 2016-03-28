// **** INCLUDES *****
#include "LowPower.h"

int led=13;
void setup()
{
    // No setup is required for this library
    pinMode(led,OUTPUT);
}

void loop() 
{
    // Enter power down state for 8 s with ADC and BOD module disabled 
    digitalWrite(led, HIGH); 
    LowPower.powerDown(SLEEP_1S, ADC_OFF, BOD_OFF); // instead of delay(1000) ; 
    digitalWrite(led, LOW); 
    LowPower.powerDown(SLEEP_1S, ADC_OFF, BOD_OFF); // instead of delay(1000) ; 
    // Do something here
    // Example: Read sensor, data logging, data transmission.
}
