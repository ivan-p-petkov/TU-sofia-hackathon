#define BLYNK_TEMPLATE_ID "TMPL4d9KbSh5U"
#define BLYNK_DEVICE_NAME "Kitchen switch"

#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = "RXkEx-dkznUGcfps_p_ImnAeCayIuF_Q";    //kitchen switch
char ssid[] = "VIVACOM_FiberNet_5D07";
char pass[] = "8331977148";

#define relayPin D2
#define pushButtonPin D1

int relayState = LOW;
int pushButtonState = HIGH;

BlynkTimer timer;

void setup() {
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);

  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, relayState);

  pinMode(pushButtonPin, INPUT_PULLUP);
}

BLYNK_WRITE(V1) {
  int buttonState = param.asInt();
  if (buttonState == 1) {
    relayState = HIGH;
  } else {
    relayState = LOW;
  }
  digitalWrite(relayPin, relayState);
}

void checkPushButton() {
  int newPushButtonState = digitalRead(pushButtonPin);
  if (newPushButtonState != pushButtonState) {
    delay(50);
    newPushButtonState = digitalRead(pushButtonPin);
    if (newPushButtonState != pushButtonState) {
      pushButtonState = newPushButtonState;
      if (pushButtonState == LOW) {
        relayState = !relayState;
        digitalWrite(relayPin, relayState);
        Blynk.virtualWrite(V1, relayState);
      }
    }
  }
}

void loop() {
  Blynk.run();
  timer.run();

  checkPushButton();
}
