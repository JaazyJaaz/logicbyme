#include <Arduino.h>

const int irSensor = 23;
int irReading;

void setup() {
  Serial.begin(115200);
  pinMode(irSensor, INPUT);
}

void loop () {
  irReading = digitalRead(irSensor);

 Serial.println(irReading);
  delay(300);
}
