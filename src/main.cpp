#include "Arduino.h"
#include <ACReader.h>

ACReader *signalRot;
ACReader *signalWeiss;

void setup() {
  Serial.begin(115200);

  // Initialize every ACReader object. Each object should
  // have an A/D port and a cycle time in milliseconds.
  // The cycle time should be slightly larger than one
  // period of the AC signal.
  signalRot = new ACReader(A0, 25);
  signalWeiss = new ACReader(A1, 25);
  Serial.println("ACReader Test started.");
}

void loop() {
  // Every ACReader object has to be updated at
  // least every millisecond.
  unsigned long now = millis();
  signalRot->tick(now);
  signalWeiss->tick(now);

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