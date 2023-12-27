#include <dht.h>
#include "MQ135.h"
#include <Servo.h> 


int servoPin = 7; 
Servo Servo1; 
const int ldrPin = A2;
int gasPin=A4;
int sensorData;
dht DHT;
const int pirPin = 8; 
// int pirState = LOW;

#define DHT11_PIN 9

void setup(){
  Serial.begin(9600);
  pinMode(gasPin,INPUT);    
  Servo1.attach(servoPin); 

  pinMode(pirPin, INPUT);


}

void loop(){

  //DHT 11

  int chk = DHT.read11(DHT11_PIN);
  Serial.print("Temperature = ");
  Serial.print(DHT.temperature);
  Serial.println(" °C");

  Serial.print("Humidity = ");
  Serial.print(DHT.humidity);
  Serial.println(" %");
  // delay(3000);

  // MQ135

  sensorData = analogRead(gasPin);       
  Serial.print("Air Quality:");
  Serial.print(sensorData , DEC);               
  Serial.println(" PPM");
  // delay(3000);


if (sensorData <= 400 ) {
  Serial.println("Good air quality");
} else {
  Serial.println("Air quality may be compromised");
}
  // delay(3000);


  // // Read the PIR sensor value
   int pirState = digitalRead(pirPin);
  
  if (pirState == HIGH) {
    Serial.println("Motion detected!");
    delay(1000);  // You can adjust the delay to control the LED duration
  } else {
        Serial.println(" NO Motion detected!");

  }



//SERVO
  Servo1.write(0); 
  delay(1000); 
  // Make servo go to 90 degrees 
  Servo1.write(90); 
  delay(1000); 
   // Make servo go to 180 degrees 
  Servo1.write(0); 
  
  delay(1000); 
    
  //LDR
  int ldrValue = analogRead(ldrPin);
   Serial.print("Light Intensity : " );

  // // Print the light level to the serial monitor
  Serial.println(ldrValue);
  // delay(4000); 

  delay(3000);
}