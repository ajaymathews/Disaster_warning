#include <LiquidCrystal.h> 
#include <SoftwareSerial.h> 
#include <TinyGPS.h> 
float lat = 10.053,lon = 76.37; // create variable for latitude and longitude object  
SoftwareSerial gpsSerial(3,4);//rx,tx 
LiquidCrystal lcd(A0,A1,A2,A3,A4,A5); 
TinyGPS gps; // create gps object 
void setup(){ 
Serial.begin(9600); // connect serial 
gpsSerial.begin(9600); // connect gps sensor 
lcd.begin(16,2); 
} 
void loop(){ 
  while(gpsSerial.available()){ // check for gps data 
  if(gps.encode(gpsSerial.read()))// encode gps data 
  {  
  gps.f_get_position(&lat,&lon); // get latitude and longitude 
  lcd.clear(); 
  lcd.setCursor(1,0); 
  lcd.print("GPS Signal"); 
  lcd.setCursor(1,0); 
  lcd.print("LAT:"); 
  lcd.setCursor(5,0); 
  lcd.print(lat); 
  lcd.setCursor(0,1); 
  lcd.print(",LON:"); 
  lcd.setCursor(5,1); 
  lcd.print(lon); 
 } 
} 
String latitude = String(lat,6); 
String longitude = String(lon,6);   
Serial.println(latitude+";"+longitude); 
delay(1000); 
} 
