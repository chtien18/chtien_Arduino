#include "iGarden.h" 
#include <Arduino.h>
//#include "DHT22.h"
#include "DHT.h"
#include "RTClib.h"
#include "Wire.h"

//DHT22 myDHT22(DHT22_PIN);      // Setup the DHT
DHT myDHT(AM2301_PIN, DHTTYPE);
RTC_DS1307 RTC;
bool s;

iGardenClass::iGardenClass()
{
}

//Sensor initializing functions:
void iGardenClass::initSensors(void){
	myDHT.begin();
}

//Sensor reading functions	
int iGardenClass::readSoilMoisture() {
	return analogRead(soilMoisturePin);
}

float iGardenClass::readAirTemperature(){ //Returns the temperature value of the DHT21 sensor
	delay(300);
	return myDHT.readTemperature(s);
}

float iGardenClass::readAirHumidity(){    //Returns the humidity value of the DHT21 sensor
	delay(300);
	return myDHT.readHumidity();
}

/*
float iGardenClass::readAirTemperature() {
	DHT22_ERROR_t errorCode;
	delay(2000);
	errorCode = myDHT22.readData(); // read data from sensor
	if (errorCode == DHT_ERROR_NONE) { // data is good
		return myDHT22.getTemperatureC(); // Get temperature reading
	}
}

float iGardenClass::readAirHumidity() {
	DHT22_ERROR_t errorCode;
	delay(2000);
	errorCode = myDHT22.readData(); // read data from sensor
	if (errorCode == DHT_ERROR_NONE) { // data is good
		return myDHT22.getHumidity();
	}
}*/



int iGardenClass::readLuminosity() {
	float luminosity = analogRead(luminosityPin);
	return ((luminosity / 1023) * 100); //cooking-hack
}


//RTC functions:
void iGardenClass::initRTC(void){
	Wire.begin();
	RTC.begin();
}

void iGardenClass::setTime(void){
	RTC.adjust(DateTime(__DATE__, __TIME__));
}

DateTime iGardenClass::getTime(void){
	return  RTC.now();
}

void iGardenClass::printTime(DateTime now){

	Serial.print(now.month(), DEC);
	Serial.print("/");

	Serial.print(now.day(), DEC);
	Serial.print("/");

	Serial.print(now.year(), DEC);
	Serial.print(" ");

	switch (now.dayOfWeek()) // Friendly printout the weekday
	{
	case 1:
		Serial.print("MON");
		break;
	case 2:
		Serial.print("TUE");
		break;
	case 3:
		Serial.print("WED");
		break;
	case 4:
		Serial.print("THU");
		break;
	case 5:
		Serial.print("FRI");
		break;
	case 6:
		Serial.print("SAT");
		break;
	case 7:
		Serial.print("SUN");
		break;
	}
	Serial.print(" ");

	if (now.hour()<10){
		switch (now.hour())
		{
		case 0:
			Serial.print("00");
			break;
		case 1:
			Serial.print("01");
			break;
		case 2:
			Serial.print("02");
			break;
		case 3:
			Serial.print("03");
			break;
		case 4:
			Serial.print("04");
			break;
		case 5:
			Serial.print("05");
			break;
		case 6:
			Serial.print("06");
			break;
		case 7:
			Serial.print("07");
			break;
		case 8:
			Serial.print("08");
			break;
		case 9:
			Serial.print("09");
			break;
		}
	}
	else{
		Serial.print(now.hour(), DEC);
	}

	Serial.print(":");

	if (now.minute()<10){
		switch (now.minute())
		{
		case 0:
			Serial.print("00");
			break;
		case 1:
			Serial.print("01");
			break;
		case 2:
			Serial.print("02");
			break;
		case 3:
			Serial.print("03");
			break;
		case 4:
			Serial.print("04");
			break;
		case 5:
			Serial.print("05");
			break;
		case 6:
			Serial.print("06");
			break;
		case 7:
			Serial.print("07");
			break;
		case 8:
			Serial.print("08");
			break;
		case 9:
			Serial.print("09");
			break;

		}
	}
	else{
		Serial.print(now.minute(), DEC);
	}

	Serial.print(":");

	if (now.second()<10){
		switch (now.second())
		{
		case 0:
			Serial.print("00");
			break;
		case 1:
			Serial.print("01");
			break;
		case 2:
			Serial.print("02");
			break;
		case 3:
			Serial.print("03");
			break;
		case 4:
			Serial.print("04");
			break;
		case 5:
			Serial.print("05");
			break;
		case 6:
			Serial.print("06");
			break;
		case 7:
			Serial.print("07");
			break;
		case 8:
			Serial.print("08");
			break;
		case 9:
			Serial.print("09");
			break;

		}
	}
	else{
		Serial.print(now.second(), DEC);
	}

}



//Irrigation functions:
void iGardenClass::initIrrigation(int out) {
	if (out == 1)
	{
		pinMode(irrigation1, OUTPUT);
		digitalWrite(irrigation1, LOW);
	}
	if (out == 2)
	{
		pinMode(irrigation2, OUTPUT);
		digitalWrite(irrigation2, LOW);
	}
	if (out == 3)
	{
		pinMode(irrigation3, OUTPUT);
		digitalWrite(irrigation3, LOW);
	}

}

void iGardenClass::irrigationON(int out) {
	if (out == 1)
	{
		digitalWrite(irrigation1, HIGH);
	}
	if (out == 2)
	{
		digitalWrite(irrigation2, HIGH);
	}
	if (out == 3)
	{
		digitalWrite(irrigation3, HIGH);
	}

}

void iGardenClass::irrigationOFF(int out) {
	if (out == 1)
	{
		digitalWrite(irrigation1, LOW);
	}
	if (out == 2)
	{
		digitalWrite(irrigation2, LOW);
	}
	if (out == 3)
	{
		digitalWrite(irrigation3, LOW);
	}

}



iGardenClass iGarden;
