// LED1 = D8 = 15 , LED2 = D6 = 12 , LED3 = D2 = 4 , FAN = D1 = 5
#define BLYNK_PRINT Serial    // Comment this out to disable prints and save space
//#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "s0hUDieHK5E9HpX0iXHOfhSDgaDF5YVc";

// led pin config

void setup()
{
  Serial.begin(115200);
  Blynk.begin(auth, "KINGYJ", "ymbj2000");
  pinMode(5,OUTPUT);
  Serial.println(digitalRead(5));
  pinMode(4,OUTPUT);
  Serial.println(digitalRead(4));
  pinMode(0,OUTPUT);
  Serial.println(digitalRead(0));
  pinMode(2,OUTPUT);
  Serial.println(digitalRead(2));
  pinMode(14,OUTPUT);
  Serial.println(digitalRead(14));// BYLNK Connection Status D5
  pinMode(12,OUTPUT);
  Serial.println(digitalRead(12));// Automate Room D6

  digitalWrite(5,LOW);
  digitalWrite(4,LOW);
  digitalWrite(0,LOW);
  digitalWrite(2,LOW);
  digitalWrite(14,LOW);
  digitalWrite(12,LOW);
}

void loop()
{ 
  Blynk.run();
}
