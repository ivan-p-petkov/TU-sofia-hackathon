#define BLYNK_TEMPLATE_ID "TMPL4d9KbSh5U"
#define BLYNK_DEVICE_NAME "Kitchen socket"

#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = "your auth";
char ssid[] = "your ssid";
char pass[] = "your pass";

#define relayPin D2

int relay1State = LOW;

BlynkTimer timer;

void setup() {
  
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  pinMode(relayPin, OUTPUT);
}


BLYNK_WRITE(V1)
{
  int buttonState = param.asInt();
  if(buttonState == 1){
    digitalWrite(relayPin, HIGH);
  }
  else{
    digitalWrite(relayPin, LOW);
  }
}


void loop()
{
  Blynk.run();
  timer.run();
}
