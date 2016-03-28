int rcPin=10;
int relay=13;
int ch1=0;
void setup() {
  // put your setup code here, to run once:
    pinMode(rcPin,INPUT);
    pinMode(relay,OUTPUT);
    Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
   ch1=pulseIn(rcPin, HIGH);
   Serial.print("Chanel: ");
   Serial.println(ch1);
   delay(200);
   
   if (ch1>1600){
   digitalWrite(relay,HIGH);
 }
   
   else {
     digitalWrite(relay,LOW);
   }
}
