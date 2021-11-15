int state = 0;
int a;
int mic = 3;
int buzzer = 6;
int soilsensor = A0;
int sensorthreshold = 800;
int b;
#include<dht.h>
#include"DHT.h"
#define dht_apin A1
dht DHT;
void setup()
{
  pinMode(2, INPUT);
  digitalWrite(2, HIGH);
  pinMode(9, INPUT);
  digitalWrite(9, HIGH);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(mic, INPUT);
  pinMode(6, OUTPUT);
  pinMode(A0, INPUT);
  Serial.println("DHT humidity and temperature sensor");
  pinMode(buzzer, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  Serial.begin(38400);

}
void loop()
{
  a = digitalRead(mic);
  pinMode(soilsensor, INPUT);
  b = analogRead(A0);
  Serial.println(b);
  digitalWrite(6, HIGH);
  DHT.read11(dht_apin);
  Serial.print("current humidity= ");
  Serial.print(DHT.humidity);
  Serial.println("%");
  Serial.print("temperature= ");
  Serial.print(DHT.temperature);
  Serial.println("c");
  if (a == LOW)
  {
    Serial.println("baby is crying & cradle is moving");
    digitalWrite(2, HIGH);
    digitalWrite(4, HIGH);
    digitalWrite(5, LOW);
    state = 0;
    if (b < sensorthreshold)
    {
      digitalWrite(6, LOW);
      Serial.println(b);
      Serial.println("buzzer is  on");
      delay(10000);
    }
    if (DHT.humidity > 58)
    {
      digitalWrite(9, HIGH);
      digitalWrite(7, HIGH);
      digitalWrite(8, LOW);
    }

  }
  if (a == HIGH)
  {
    {
      Serial.println("baby isnt crying");
      delay(1000);
    }
    if (Serial.available() > 0)
    {
      state = Serial.read();
    }
    if (state == '1')
    {
      digitalWrite(2, HIGH);
      digitalWrite(4, HIGH);
      digitalWrite(5, HIGH);
      Serial.println("cradle stopped");
      state = 0;
    }
    if (state == '2')
    {
      digitalWrite(6, HIGH);
      Serial.println("buzzer IS OFF");

    }
    if (state == '3')
    {
      digitalWrite(9, HIGH);
      digitalWrite(7, HIGH);
      digitalWrite(8, HIGH);
      Serial.println("fan is off");
      state = 0;
    }
  }

}

