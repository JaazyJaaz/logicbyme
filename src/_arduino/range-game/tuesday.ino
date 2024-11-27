#include <Stepper.h>
#define motorIn1_pin 10 // out
#define motorIn2_pin 11 // out
#define motorIn3_pin 12 // out
#define motorIn4_pin 9 // out
#define motorSpeedPot_pin A1 // input potentiometer pin A1
// btns & their LEDs
#define upBtn_pin 8 // in
#define upBtnLed_pin 6 // out
#define lowBtn_pin 7 // in
#define lowBtnLed_pin 13 // out
bool isUpBtnPressed = false;
bool isLowBtnPressed = false;



int stepCount = 0;         // number of steps the motor has taken

int stepsPerRevolution = 150;  // change this to fit the number of steps per revolution
int steps = 150;
//int step_speed = 100; // rpm
int maxStepSpeed = 200;
bool isMovingUp = false;
bool isFrozen = false;
Stepper myStepper = Stepper(stepsPerRevolution, motorIn1_pin, motorIn3_pin, motorIn2_pin, motorIn4_pin);

int motorSpeedPot_now = 0;

void setup() {
  // set the speed at 60 rpm:
  myStepper.setSpeed(150);
  // initialize the serial port:
  Serial.begin(9600);

  // output: push button LEDs
  pinMode(upBtnLed_pin, OUTPUT);
  pinMode(lowBtnLed_pin, OUTPUT);
  // input: push buttons switch
  pinMode(upBtn_pin, INPUT_PULLUP);
  pinMode(lowBtn_pin, INPUT_PULLUP);
}

int prevPot = 0;
void loop() {
  Serial.println("~~~~~loop start");
  digitalWrite(upBtnLed_pin, HIGH);
  digitalWrite(lowBtnLed_pin, HIGH);
  isUpBtnPressed = digitalRead(upBtn_pin) == 0;
  isLowBtnPressed = digitalRead(lowBtn_pin) == 0;
  motorSpeedPot_now = analogRead(motorSpeedPot_pin); // motor speed

  Serial.print("isUpBtnPressed: "); Serial.println(isUpBtnPressed);
  Serial.print("isLowBtnPressed: "); Serial.println(isLowBtnPressed);
  Serial.print("~~~~~~motorSpeedPot_now: "); Serial.println(motorSpeedPot_now);
  
  if (prevPot != motorSpeedPot_now) {
    Serial.println("updating motor speed...");
    int motorSpeed = map(motorSpeedPot_now, 0, 1024, 0, maxStepSpeed );
    myStepper.setSpeed(motorSpeed);
    prevPot = motorSpeedPot_now;
  }


  if (isUpBtnPressed) {
    Serial.println("~~~~~~up btn pressed");
    delay(400);
    isMovingUp = !isMovingUp;
  }
  if (isLowBtnPressed) {
    Serial.println("~~~~~low btn pressed");
    delay(500);
    isFrozen = !isFrozen;
  }

  int dir = isMovingUp ? steps : -steps;
  // step one step:
  if (!isFrozen) {
    Serial.println("~~~~~Range Finder is MOVING");
    myStepper.step(dir);
    Serial.print("steps:"); Serial.println(stepCount);
    stepCount++;
  } else {
    Serial.println("~~~~~Range Finder is FROZEN");
  }
}