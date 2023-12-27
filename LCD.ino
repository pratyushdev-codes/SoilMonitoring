#include <dht.h>
#include "MQ135.h"
#include <Servo.h>
#include <LiquidCrystal.h>

int servoPin = 7;
Servo Servo1;
const int ldrPin = A2;
int gasPin = A4;
int sensorData;
dht DHT;
const int pirPin = 8;
int pirState = LOW;

#define DHT11_PIN 9

// Define the LCD display
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {
  Serial.begin(9600);
  pinMode(gasPin, INPUT);
  Servo1.attach(servoPin);
  pinMode(pirPin, INPUT);

  // Initialize the LCD
  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Sensor Data:");
  lcd.setCursor(0, 1);
  lcd.print("Motion: NO");
  delay(2000);
}

void loop() {
  // DHT11
  int chk = DHT.read11(DHT11_PIN);
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(DHT.temperature);
  lcd.print(" C  ");
  lcd.setCursor(0, 1);
  lcd.print("Humidity: ");
  lcd.print(DHT.humidity);
  lcd.print(" %  ");
  Serial.print("Temp: ");
  Serial.print(DHT.temperature);
  Serial.print(" C  ");

  // Serial.setCursor(0, 1);
  Serial.print("Humidity: ");
  Serial.print(DHT.humidity);
  Serial.print(" %  ");
  
  // MQ135
  sensorData = analogRead(gasPin);
  lcd.setCursor(0, 2);
  lcd.print("Air Quality: ");
  lcd.print(sensorData, DEC);
  lcd.print(" PPM  ");
  Serial.print("Air Quality: ");
  Serial.print(sensorData, DEC);
  Serial.print(" PPM  ");

  if (sensorData <= 400) {
    lcd.setCursor(0, 3);
    lcd.print("Good air quality  ");
    Serial.print("Good air quality  ");
  } else {
    lcd.setCursor(0, 3);
    lcd.print("Air quality may be compromised  ");
    Serial.print("Air quality may be compromised  ");
  }

  // Read the PIR sensor value
  pirState = digitalRead(pirPin);
  lcd.setCursor(0, 1);
  if (pirState == HIGH) {
    lcd.print("Motion: YES");
    Serial.println("Motion detected!");
  } else {
    lcd.print("Motion: NO");
    Serial.println("NO Motion detected!");
  }

  //SERVO
  Servo1.write(0);
  delay(1000);
  Servo1.write(90);
  delay(1000);
  Servo1.write(0);
  delay(1000);

  //LDR
  int ldrValue = analogRead(ldrPin);
  lcd.setCursor(0, 0);
  lcd.print("Light Level: ");
  lcd.print(ldrValue);
  lcd.print("  ");
  Serial.print("Light Level: ");
  Serial.print(ldrValue);
  Serial.print("  ");
  
  delay(3000);
}
