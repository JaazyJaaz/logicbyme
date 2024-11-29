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
int buttonPressedDelay = 400; // ms

int stepCount = 0;         // number of steps the motor has taken
int maxStepCount = 10000;
int stepsPerRevolution = 150;  // change this to fit the number of steps per revolution
int stepsPerLoop = 150;
int maxStepSpeed = 200;
int initialStepperSpeed = 150;

int motorSpeedPot_now = 0;
int prevPot = 0;

bool isMovingUp = false;
bool isFrozen = false;

Stepper myStepper = Stepper(stepsPerRevolution, motorIn1_pin, motorIn3_pin, motorIn2_pin, motorIn4_pin);

bool tryMoveStepper(int steps)
{
  if ((steps > 0 && stepCount + steps <= maxStepCount) 
    || (steps < 0 && stepCount - steps >= 0))
  {
    myStepper.step(steps);
    stepCount += steps;
    return true;
  }
  return false;
}

void handlePotentiometer()
{
  motorSpeedPot_now = analogRead(motorSpeedPot_pin); // motor speed
  Serial.print("~~~~~~motorSpeedPot_now: "); Serial.println(motorSpeedPot_now);

  if (prevPot != motorSpeedPot_now) {
    Serial.println("updating motor speed...");
    int motorSpeed = map(motorSpeedPot_now, 0, 1024, 0, maxStepSpeed );
    myStepper.setSpeed(motorSpeed);
    prevPot = motorSpeedPot_now;
  }
}

void handleUpperButton()
{
  isUpBtnPressed = digitalRead(upBtn_pin) == 0;  
  Serial.print("isUpBtnPressed: "); Serial.println(isUpBtnPressed);

  if (isUpBtnPressed) {
    Serial.println("~~~~~~up btn pressed");
    delay(buttonPressedDelay);
    isMovingUp = !isMovingUp;
  }
}

void handleLowerButton()
{
  isLowBtnPressed = digitalRead(lowBtn_pin) == 0;
  Serial.print("isLowBtnPressed: "); Serial.println(isLowBtnPressed);

  if (isLowBtnPressed) {
    Serial.println("~~~~~low btn pressed");
    delay(buttonPressedDelay);
    isFrozen = !isFrozen;
  }
}

void setup() {
  // set the speed at 60 rpm:
  myStepper.setSpeed(initialStepperSpeed);
  // initialize the serial port:
  Serial.begin(9600); // I wanted to make this a variable but held myself back

  // output: push button LEDs
  pinMode(upBtnLed_pin, OUTPUT);
  pinMode(lowBtnLed_pin, OUTPUT);
  // input: push buttons switch
  pinMode(upBtn_pin, INPUT_PULLUP);
  pinMode(lowBtn_pin, INPUT_PULLUP);
}

void loop() {
  Serial.println("~~~~~loop start");
  digitalWrite(upBtnLed_pin, HIGH);
  digitalWrite(lowBtnLed_pin, HIGH);
  
  handlePotentiometer();

  handleUpperButton();

  handleLowerButton();

  int dir = isMovingUp ? stepsPerLoop : -stepsPerLoop;
  // step one step:
  if (!isFrozen) {
    Serial.println("~~~~~Range Finder is MOVING");
    bool didStepperMove = tryMoveStepper(dir);
    Serial.print("steps attempted:"); 
    Serial.println(stepCount);
    Serial.print("Did stepper move:");
    Serial.print(didStepperMove);
  } else {
    Serial.println("~~~~~Range Finder is FROZEN");
  }
}