#include <Stepper.h>
#include <SoftwareSerial.h>

const int stepsPerRevolution = 2038;
Stepper rangeFinder = Stepper(stepsPerRevolution, 10, 12, 11, 9);
const int upperBtn_pin = 6;
const int upperBtnLed_pin = 8;
const int lowerBtn_pin = 13;
const int lowerBtnLed_pin = 7;

void setup() {
  pinMode(upperBtn_pin, INPUT);
  pinMode(upperBtnLed_pin, OUTPUT);
  pinMode(lowerBtn_pin, INPUT);
  pinMode(lowerBtnLed_pin, OUTPUT);
}

void loop() {
  Serial.begin(9600);  // buad

  digitalWrite(upperBtnLed_pin, HIGH);
  digitalWrite(lowerBtnLed_pin, HIGH);

  bool upperBtnPress = digitalRead(upperBtn_pin) == 1;
  bool lowerBtnPress = digitalRead(lowerBtn_pin) == 1;

  // move motor forward n back
  rangeFinder.setSpeed(10);              // rpm
  rangeFinder.step(stepsPerRevolution);  // CW
  delay(15000);
  rangeFinder.step(-stepsPerRevolution);  // CCW
  delay(15000);
}