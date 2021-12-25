#include "Arduino.h"
#include <ACReader.h>

ACReader *signalRot;
ACReader *signalWeiss;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  signalRot = new ACReader(A0, 60);
  signalWeiss = new ACReader(A1, 60);
  Serial.println("ACReader Test started.");
}

void loop() {
  // put your main code here, to run repeatedly:
  unsigned long now = millis();
  currentMeter->tick(now);

  static unsigned long outputDelay = 0;
  if (now > outputDelay) {
    outputDelay = now + 1000;
    Serial.print("Act value rot: ");
    Serial.print(signalRot->getActValue());
    Serial.print(", average value: ");
    Serial.println(signalRot->getAverageValue());
    Serial.print(", Act value weiss: ");
    Serial.print(signalWeiss->getActValue());
    Serial.print(", average value: ");
    Serial.println(signalWeiss->getAverageValue());
  }
}