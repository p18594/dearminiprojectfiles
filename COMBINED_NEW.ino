#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>
#include "Adafruit_Sensor.h"
 
char auth[] = "7Z-lKeNldylSoFgzdxMo6zdbxG3t5aJ_"; 
 
// Your WiFi credentials.
// Set password to "" for open networks.

char ssid[] = "qthough";
char pass[] = "11111111";

 boolean LEDStatus=false;
#define BLYNK_PRINT Serial
#define DHTPIN 0          // D3
int sense_Pin = A0; // sensor input at Analog pin A0/D0

int value;
// Uncomment whatever type you're using!
#define DHTTYPE DHT11     // DHT 11
//#define DHTTYPE DHT22   // DHT 22, AM2302, AM2321
//#define DHTTYPE DHT21   // DHT 21, AM2301
 
DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timer;
 
// This function sends Arduino's up time every second to Virtual Pin (5).
// In the app, Widget's reading frequency should be set to PUSH. This means
// that you define how often to send data to Blynk App.
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
     value= analogRead(A0);
   //value= value/10;
   value = 1024-value;
  // Serial.println(value);
   
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
pinMode(14,OUTPUT);   //en1   D5
pinMode(12,OUTPUT);    //en2   D6
pinMode(16,OUTPUT);   //in1    D0
pinMode(5,OUTPUT);    //in2   D1
//pinMode(4,OUTPUT);    //in2   D2
digitalWrite(14,HIGH);
digitalWrite(12,HIGH);

  // Debug console
  Serial.begin(9600);
 
  Blynk.begin(auth, ssid, pass);
  // You can also specify server:
  //Blynk.begin(auth, ssid, pass, "blynk-cloud.com", 8442);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8442);
 
  dht.begin();
 
  // Setup a function to be called every second
  timer.setInterval(100L, sendSensor);


}
 
void loop()
{
  Blynk.run();
  timer.run();
  if(value>300)
  { 
    digitalWrite(16,HIGH);
    digitalWrite(5,LOW);  
    delay(5000);
    }
    else
    {    digitalWrite(16,LOW);
    digitalWrite(5,LOW);  
      }
}
