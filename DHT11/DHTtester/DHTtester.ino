// Example testing sketch for various DHT humidity/temperature sensors
// Written by ladyada, public domain

#include "DHT.h"

#define DHTPIN 2     // what digital pin we're connected to

// Uncomment whatever type you're using!
//#define DHTTYPE DHT11   // DHT 11
#define DHTTYPE DHT11   // DHT 22  (AM2302), AM2321
//#define DHTTYPE DHT21   // DHT 21 (AM2301)

// Connect pin 1 (on the left) of the sensor to +5V
// NOTE: If using a board with 3.3V logic like an Arduino Due connect pin 1
// to 3.3V instead of 5V!
// Connect pin 2 of the sensor to whatever your DHTPIN is
// Connect pin 4 (on the right) of the sensor to GROUND
// Connect a 10K resistor from pin 2 (data) to pin 1 (power) of the sensor

// Initialize DHT sensor.
// Note that older versions of this library took an optional third parameter to
// tweak the timings for faster processors.  This parameter is no longer needed
// as the current DHT reading algorithm adjusts itself to work on faster procs.
DHT dht(DHTPIN, DHTTYPE);

float h=0;
float t=0;
float f=0;
void setup() {
  Serial.begin(9600);
 // Serial.println("DHTxx test!");

  dht.begin();
}

void loop() {
  // Wait a few seconds between measurements.
  delay(2000);
  if (Serial.available()>0){
    int incomingbyte=Serial.read();
   // Serial.println(incomingbyte,DEC);
  
  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // Compute heat index in Fahrenheit (the default)
  float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);

  String json=buildJson();
  char jsonStr[200];
  json.toCharArray(jsonStr,200);
  Serial.print(jsonStr);
  }
 
}

String buildJson() {
  String data = "{";
 // data+="\n";
 // data+= "\"d\": {";
 // data+="\n";
  data+="\"ID\": \"Arduino DHT11\",";
 // data+="\n";
  data+="\"temperature (F)\": ";
  data+=(float)f;
  data+= ",";
  //data+="\n";
  data+="\"temperature (C)\": ";
  data+=(float)t;
  data+= ",";
  //data+="\n";
  data+="\"humidity\": ";
  data+=(float)h;
  //data+="\n";
  data+="}";
  data+="\n";
  //data+="}";
  return data;
}
