int Light=9;
int Motor=10;

void setup() {
 pinMode(Light,OUTPUT);
 pinMode(Motor,OUTPUT);
 Serial.begin(9600);

 digitalWrite(Light,HIGH);// off Light
 digitalWrite(Motor,HIGH); //off Motor
}

void loop() {
     if (Serial.available()>0){
        int byte_in=Serial.read();
        switch(byte_in) {
              case 'a': //Light on
              
                digitalWrite(Light,LOW);
                break;

              case 'b': //Light off
                digitalWrite(Light,HIGH);
                break;

              case 'c': //Motor on
                digitalWrite(Motor,LOW);
                break;

              case 'd': //motor off
                digitalWrite(Motor,HIGH);
                break;      
        }
     }
}
