#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>
#include "Adafruit_Sensor.h"

char auth[] = "7Z-lKeNldylSoFgzdxMo6zdbxG3t5aJ_"; 
 

char ssid[] = "Ece2";
char pass[] = "Vinod@Ece2";

 boolean LEDStatus=false;
#define BLYNK_PRINT Serial
#define DHTPIN 0          // D3
int sense_Pin = A0; // sensor input at Analog pin A0/D0
#define DHTTYPE DHT11     // DHT 11
int value;
DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timer;

void sendSensor()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature();   // or dht.readTemperature(true) for Fahrenheit

     //Fahrenheit
    //T(°F) = T(°C) × 9/5 + 32
    t = ( t * 1.8 ) + 32;
    //Serial.print("Fahrenheit = ");
    //Serial.print(converted);
    //Print degree symbol
    //Serial.write(176); 
    //Serial.println("F");

 Serial.print("SOUND LEVEL : ");
   value= analogRead(A0);
   value = 1024-value;
   Serial.println(value);
   
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
    
  }
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V5, t);
  Blynk.virtualWrite(V6, h);
  Blynk.virtualWrite(V4,value);

}
 
void setup()
{
  // Debug console
  Serial.begin(9600);
 
  Blynk.begin(auth, ssid, pass);
 
  dht.begin();
 
  // Setup a function to be called every second
  timer.setInterval(100L, sendSensor);

}
 
void loop()
{
  Blynk.run();
  timer.run();
}
