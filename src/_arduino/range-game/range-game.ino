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

bool isUpperButtonPressed = false;
int upperButtonTimePress = 0;
int upperButtonTimePressLimit = 0;
int upperButtonClicks = 0;
int upperButtonEffectiveClicks = 0;
int allowableDoubleClickDelay = 1000; // ms
bool isLowerButtonPressed = false;
int buttonPressedDelay = 200; // ms

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

void resetPosition()
{
  if (stepCount > 0)
  {
    Serial.println("resetting pointer position...");
    myStepper.step(-stepCount);
  }
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
  // TODO: Figure out how to break this into simpler functions
  // TODO: Break this out into a general purpose library (don't use for buttons that need instant response!)
  isUpperButtonPressed = digitalRead(upBtn_pin) == 0;  
  Serial.print("isUpperButtonPressed: "); Serial.println(isUpperButtonPressed);
  
  if (isUpperButtonPressed){
    delay(buttonPressedDelay);

    if (upperButtonClicks == 0) {
      upperButtonTimePress = millis();
      upperButtonTimePressLimit = upperButtonTimePress + allowableDoubleClickDelay;    
      upperButtonClicks = 1;
    }
    else if (upperButtonClicks == 1 && millis() < upperButtonTimePressLimit){
      Serial.println("Upper Button Pressed twice");

      //set variables back to 0
      upperButtonTimePress = 0;
      upperButtonTimePressLimit = 0;
      upperButtonClicks = 0;      
    }
    else if (upperButtonClicks == 1 && upperButtonTimePressLimit != 0 && millis() > upperButtonTimePressLimit)
    {
      Serial.println("Upper Button Pressed once");
      isMovingUp = !isMovingUp;

      //set variables back to 0
      upperButtonTimePress = 0;
      upperButtonTimePressLimit = 0;
      upperButtonClicks = 0;  
    }
  }
}

void handleLowerButton()
{
  isLowerButtonPressed = digitalRead(lowBtn_pin) == 0;
  Serial.print("isLowerButtonPressed: "); Serial.println(isLowerButtonPressed);

  if (isLowerButtonPressed) {
    Serial.println("~~~~~lower button pressed");
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

  int stepsToMove = isMovingUp ? stepsPerLoop : -stepsPerLoop;
  // step one step:
  if (!isFrozen) {
    Serial.println("~~~~~Range Finder is MOVING");
    bool didStepperMove = tryMoveStepper(stepsToMove);
    Serial.print("Steps attempted:"); Serial.println(stepsToMove);
    Serial.print("Did stepper move:"); Serial.println(didStepperMove);
    Serial.print("Current step count:"); Serial.println(stepCount);
  } else {
    Serial.println("~~~~~Range Finder is FROZEN");
  }
}