#define SONAR_TRIGGER_PIN     4
#define SONAR_ECHO_PIN        5

int current_distance=0;

unsigned int measure_distance()
{
   // Trigger the SRF05:
   digitalWrite(SONAR_TRIGGER_PIN, HIGH);
   delayMicroseconds(10);
   digitalWrite(SONAR_TRIGGER_PIN, LOW);

   // Wait for Echo Pulse
   unsigned long pulse_length = pulseIn(SONAR_ECHO_PIN, HIGH);

   // Ensure the ultrasonic "beep" has faded away
   delay(50);

   // Convert Pulse to Distance (inches) 
   // pulse_length/58 = cm or pulse_length/148 = inches
   return( (unsigned int) (pulse_length / 58) );
}

void setup()
{
   pinMode(SONAR_TRIGGER_PIN, OUTPUT);
   pinMode(SONAR_ECHO_PIN, INPUT);
   Serial.begin(9600);
}

void loop()
{
  if(Serial.available()>0){
   int incomingbyte=Serial.read();
   current_distance = measure_distance();
   
   if (incomingbyte== 97){
   String data =String(current_distance);
   Serial.print(data);
   }
   else{

  String json=buildJson();
  char jsonStr[200];
  json.toCharArray(jsonStr,200);
  Serial.print(jsonStr);
   
  
   }
   delay(20);

  }
}

String buildJson() {
  String data = "{";
  data+="\"ID\": \"Arduino Ultrasoud\",";
  data+="\"Water_level\": ";
  data+=(int)current_distance;
  data+="}";
  data+="\n";
  return data;
}
