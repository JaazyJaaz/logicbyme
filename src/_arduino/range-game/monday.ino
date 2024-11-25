// 11-25-2024
// control stepper
// top btn = change dir
// bottom button = toggle moving
// btn leds on  

#include <Stepper.h>
#define motorIn1_pin 10 // out
#define motorIn2_pin 11 // out
#define motorIn3_pin 12 // out
#define motorIn4_pin 9 // out
// btn leds
#define upBtn_pin 8 // in
#define upBtnLed_pin 6 // out
#define lowBtn_pin 7 // in
#define lowBtnLed_pin 13 // out
bool isUpBtnPressed = false;
bool isLowBtnPressed = false;
const int stepsPerRevolution = 200;  // change this to fit the number of steps per revolution

Stepper myStepper = Stepper(stepsPerRevolution, motorIn1_pin, motorIn3_pin, motorIn2_pin, motorIn4_pin);


int stepCount = 0;         // number of steps the motor has taken


void setup() {
  // set the speed at 60 rpm:
  myStepper.setSpeed(140);
  // initialize the serial port:
  Serial.begin(9600);

  // output: push button LEDs
  pinMode(upBtnLed_pin, OUTPUT);
  pinMode(lowBtnLed_pin, OUTPUT);
  // input: push buttons switch
  pinMode(upBtn_pin, INPUT_PULLUP);
  pinMode(lowBtn_pin, INPUT_PULLUP);
}

bool b_CW = false;
bool b_stop = false;
void loop() {
  Serial.println("~~~~~loop start");
  digitalWrite(upBtnLed_pin, HIGH); 
  digitalWrite(lowBtnLed_pin, HIGH); 
  isUpBtnPressed = digitalRead(upBtn_pin) == 0;
  isLowBtnPressed = digitalRead(lowBtn_pin) == 0;
  Serial.print("isUpBtnPressed: "); Serial.println(isUpBtnPressed);
  Serial.print("isLowBtnPressed: "); Serial.println(isLowBtnPressed);

  if (isUpBtnPressed) {
    delay(500);
    b_CW = !b_CW;
  }
  if (isLowBtnPressed) {
    delay(500);
    b_stop = !b_stop;
  }

  int dir = b_CW ? 100 : -100;
  // step one step:
  if(!b_stop) {
  myStepper.step(dir);
  Serial.print("steps:");
  Serial.println(stepCount);
  stepCount++;
  }else {
    Serial.println("STOP");
    }

}