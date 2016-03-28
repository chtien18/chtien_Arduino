#ifndef iGarden_included
#define	iGarden_included

#include <Arduino.h>
//#include "DHT22.h"
#include "DHT.h"
#include "RTClib.h"
#include "Wire.h"


// sensor
#define soilMoisturePin A7
#define luminosityPin A0

#define MON 1
#define TUE 2
#define WED 3
#define THU 4
#define FRI 5
#define SAT 6
#define SUN 7

//#define DHT22_PIN 4
#define AM2301_PIN 5
#define DHTTYPE DHT21



#define irrigation1 22
#define irrigation2 7
#define irrigation3 9

// Library interface description
class iGardenClass
{

public:

	iGardenClass();

	//Sensor initializing functions
	void initSensors(void);    //Initializing necessary for all the sensors

	//Sensor reading functions	
	int readSoilMoisture(void);     //Returns the value of the soil moisture sensor

	float readAirTemperature(void); //Returns the temperature value of the DHT21 sensor
	float readAirHumidity(void);    //Returns the humidity value of the DHT21 sensor
	int readLuminosity(void);       //Returns the value of the LDR sensor

	//RTC functions
	void initRTC(void);	      //Initializing necessary for the RTC
	void setTime(void); 	      //Get the computer's time and date
	DateTime getTime(void);		  //Get a struct with current time and date
	void printTime(DateTime now); //Serial print the struct obtained with getTime

	//Irrigation functions
	void initIrrigation(int out); //Initializing necessary for irrigation with the number “out”
	void irrigationON(int out);   //Turns on the irrigation with the number “out”
	void irrigationOFF(int out);  //Turns off the irrigation with the number “out”

};

extern iGardenClass iGarden;
#endif
