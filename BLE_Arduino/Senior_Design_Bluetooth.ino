#include <SoftwareSerial.h>

const int buttonPin = 5; 
const int ledPin =  13; 

SoftwareSerial mySerial(2, 3);

int buttonState = 0;  
byte buf[2] = {1,2};  

void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT);
}

void loop() {
  buttonState = digitalRead(buttonPin);


  if (buttonState == HIGH) {

    digitalWrite(ledPin, HIGH);
    mySerial.print(2, DEC);
    //Serial.print(2);
    //Serial.write(2);
    //mySerial.write(2);
  } else {
    digitalWrite(ledPin, LOW);
    mySerial.print(1, DEC);
    //Serial.print(1);
    //Serial.write(1);
    //mySerial.write(1);
  }
  //mySerial.read();
  delay(100);
}
