/* pinout
 *  GPS 
 *  VCC - 5V
 *  RX - TX(DIG 9)
 *  TX- RX (DIG 8)
 *  GND - GND
 *  
 *  
 *  DHT- ARD
 *  S - DIG 10
 *  MIDDLE - 5V
 *  R_SIDE - GND
 *  
 *  ADXL- ARD
 *  VCC - 3.3V
 *  GND - GND
 *  SCL- SCL
 *  SDA- SDA
 *  
 *  FLAME - ARD
 *  AO - A0
 *  + - 3.3V
 *  G - GND
 *  
 *  WATER_LVL - ARD
 *  ONE PIN - 3.3V 
 *  ANOTHER PIN - 11 DIG
 *  
 *  GAS SENSOR - ARD
 *  A0 - ANALOG 1(A5)
 *  GND- GND
 *  VCC - 3.3V
 *  
 *  
 *  INITIAL RELAY
 *  IN-DIG 5
 *  VCC-5V
 *  GND - GND
 *  
 *  FINAL_RELAY
 *  IN - DIG 3
 *  VCC- 5V
 *  GND - GND
 */



#include <SimpleDHT.h>
#include <LiquidCrystal.h> 
#include <SoftwareSerial.h> 
#include <TinyGPS++.h>
#include <Wire.h>
#include <SparkFun_ADXL345.h>         // SparkFun ADXL345 Library
float latt = 10.053,lonn = 76.37; // create variable for latitude and longitude object  
SoftwareSerial gpsSerial(8,9);//rx,tx
ADXL345 adxl = ADXL345(); 
int pinDHT11 = 10;
const int sensorMin = 0;     // sensor minimum
const int sensorMax = 1024;
const byte switchPin = 11;
const byte initial_break = 4;
const byte final_break = 5;

SimpleDHT11 dht11(pinDHT11);
TinyGPSPlus gps;
//SoftwareSerial gpsSerial(8,9);//rx,tx

void setup() {
  Serial.begin(9600);
  gpsSerial.begin(9600);
  const byte switchPin = 11;// Start the serial terminal
  adxl.powerOn(); 
  adxl.setRangeSetting(2);
  adxl.setSpiBit(0);
  pinMode (switchPin, INPUT);
  pinMode (initial_break, INPUT);
  pinMode (final_break, INPUT);
  Serial.println();
  pinMode(5, OUTPUT);
  pinMode(3, OUTPUT);
  digitalWrite(3,LOW);
  digitalWrite(5,LOW);
  
}

void loop() {
  byte temperature = 0;
  byte humidity = 0;
  int x,y,z;
  adxl.readAccel(&x, &y, &z);
  gps.encode(Serial.read());
  Serial.print("Latitude = ");  
  Serial.println(latt); 
  Serial.print("Longitude = "); 
  Serial.println(lonn);
  delay(300);            
  int err = SimpleDHTErrSuccess;
  if ((err = dht11.read(&temperature, &humidity, NULL)) != SimpleDHTErrSuccess) {
    Serial.print("Read DHT11 failed, err=");
    Serial.println(err);
    delay(1000);
  }
  Serial.print("Temperature : ");
  Serial.print((int)temperature);
  Serial.println(" *C, ");   
  Serial.print("Humidity : ");
  Serial.print((int)humidity);
  Serial.println(" H");       
  if(temperature > 40)
  {
    Serial.println("ALERT : OVER HEAT");
    digitalWrite(5,HIGH);
    Serial.println("ALERT GENERATED");
    delay(2000);
    digitalWrite(5,LOW);
  }  
  if(z<-248)
  {
    Serial.println("ALERT :     EARTHQUAKE DETECTED");
    digitalWrite(3,HIGH);
     digitalWrite(5,HIGH);
    Serial.println("ALERT GENERATED");
    delay(2000);
    digitalWrite(5,LOW);   
  }

  if (digitalRead (switchPin) == HIGH)
     {
 //    Serial.println ("WATER_LEVEL:NORMAL");
 //    delay (1000); 
     }
  else
  {
    Serial.println("ALERT :  WATER_LEVEL: RISING.. ");
    digitalWrite(5,HIGH);
    Serial.println("ALERT GENERATED");
    delay(2000);
    digitalWrite(5,LOW);
  }
  
    int gasReading = analogRead(A5);
      if(gasReading>43)
      {    
        Serial.println("GAS ALERT : NORMAL"); 
      }
    int flameReading = analogRead(A0);
      if(flameReading<35)
      {
        Serial.println("ALERT :  FIRE DETECTED");
        digitalWrite(5,HIGH);
        Serial.println("ALERT GENERATED");
        delay(2000);
        digitalWrite(5,LOW);
      }
      Serial.println("");


delay(1000);    
 
}
