

// https://docs.arduino.cc/learn/built-in-libraries/software-serial/
#include <Stepper.h>
#include <SoftwareSerial.h>
//#include <string>
//#include <iostream> // cout << "text here to console"

//-----------------------------
const int powerSwitch_pin = 1; // switch
const int powerLed_pin = 2; // if game is turned on?

const int gameStatusLed_pin = 3; // on/off visual LED indicator
const int gameStatusButton_pin = 3; // on/off start game

const int rangeFinderLed_pin = 4; // button to stop range finger
const int rangeFinderButton_pin = 5; // control range finder

//-----------------------------------

enum GameStatus {
  OFF = 0,
  CHILLIN,
  ACTIVE,
  FROZEN,
  RESET
};

enum GameStatus stat;
bool isGamePowered = false;

// stepper motor control ----------------------
/* 5V Stepper Motor - ULN2003 Driver Board
   Pins entered in sequence IN1-IN3-IN2-IN4 for proper step sequence */
const int stepsPerRevolution = 2038;
Stepper rangeFinder = Stepper(stepsPerRevolution, 10, 12, 11, 13);

int rangeFinderPos_init = 0;
int rangeFinderPos = 0; // put read ir value here

// bool freezeOverride = false; // jaa delete dont think it is needed

void setup() {
  Serial.begin(9600); // serial comm 9600 buad rate
  stat = RESET;
  // stepper motor pins set in library

  pinMode(powerSwitch_pin, INPUT); // power switch
  pinMode(powerLed_pin, OUTPUT); // power light indicator

  pinMode(gameStatusLed_pin, OUTPUT); // is in game light indicator
  pinMode(gameStatusButton_pin, INPUT); // enum states

  pinMode(rangeFinderLed_pin, OUTPUT); // led light for range finder control btn
  pinMode(rangeFinderButton_pin, INPUT); // RangeFinder Button
}


void getPowerStatus() {
  bool powerSwitch = digitalRead(powerSwitch_pin) == 1;
  if (powerSwitch && !isGamePowered) {
    isGamePowered = true;
    goto reset_label; // game just turned on
  } else {
    stat = GameStatus::OFF;
  }
}

bool getRangeFinderButtonStatus() {
  // called when in active mode to check when to freeze motor
  bool isBtnPressed = digitalRead(rangeFinderButton_pin) == 1;
  if (stat = GameStatus::ACTIVE) { // only works when actively playing
    // freezeOverride = true;
    stat =  (isBtnPressed == 1) ? GameStatus::FROZEN : GameStatus::ACTIVE;
  } else {
    // do nothing?
  }
  return isBtnPressed;
}

bool getStatusButtonStatus() {
  // returns if stat got changed
  bool isBtnPressed = digitalRead(gameStatusButton_pin) == 1;
  bool rtnVal = false;

  if (isBtnPressed) {
    switch (stat) {
      case GameStatus::OFF:
        rtnVal = false;
        break;
      case GameStatus::CHILLIN:
        stat = GameStatus::ACTIVE;
        rtnVal = true;
        break;
      case GameStatus::ACTIVE:
        stat = GameStatus::FROZEN;
        rtnVal = true;
        break;
      case GameStatus::FROZEN:
        stat = GameStatus::RESET;
        rtnVal = true;
        break;
      case GameStatus::RESET:
        // continue reseting? dont let it interrupt
        rtnVal = false;
                 break;
                 default:
                 break;
    }
  }
  return rtnVal;
}


void loop() {
  // !!jaa: figure out how to read isGamePowered all the time without delay
  switch (stat) {
    case GameStatus::OFF:
      Serial.println("game is turned off.");
      getPowerStatus();
      
      digitalWrite(gameStatusLed_pin, LOW); 
      digitalWrite(rangeFinderLed_pin, LOW);
      break;

    case GameStatus::CHILLIN: // init
      getPowerStatus();
      getStatusButtonStatus();
      // chillin at the bottom of the scale
      // -- check position of range finder if not at bottom goto RESET
      // if not at bottom goto reset or set enum to reset
      digitalWrite(gameStatusLed_pin, LOW); // game status LED = OFF or super slow blink??
      digitalWrite(rangeFinderLed_pin, HIGH);
      break;

    case GameStatus::ACTIVE:
      getPowerStatus();
      bool shouldStopRangeFinder = getRangeFinderButtonStatus(); // listen for RangeFinder btn
      getStatusButtonStatus(); // for override
      // stop range finder
      If (this.shouldStopRangeFinder) {
        goto freeze_label;
      }
      // note: should we check current position to make sure at reset
      digitalWrite(gameStatusLed_pin, HIGH);
      digitalWrite(rangeFinderLed_pin, HIGH);
      // start moving RangeFinder- Rotate CW at 15 RPM
      rangeFinder.setSpeed(15);
      rangeFinder.step(stepsPerRevolution);
      delay(150);
      break;

    case GameStatus::FROZEN:
freeze_label:
      if (stat != GameStatus::FREOZEN) {
        stat = GameStatus::FROZEN;
      }
      getPowerStatus();
      getStatusButtonStatus(); // if clicked goto reset
      digitalWrite(gameStatusLed_pin, HIGH);
      digitalWrite(rangeFinderLed_pin, LOW); // turn off range finder btn led indicator

      // did you win? we may be able to check using one ir sensor
      break;

    case GameStatus::RESET:
reset_label:
      if (stat != GameStatus::RESET) {
        stat = GameStatus::RESET;
      }
      getPowerStatus();
      getStatusButtonStatus();

      digitalWrite(gameStatusLed_pin, HIGH);
      digitalWrite(rangeFinderLed_pin, LOW);

      // is range finder reset to bottom?
      // start moving RangeFinder down Rotate CCW at 15 RPM
      rangeFinder.setSpeed(15);
      rangeFinder.step(-stepsPerRevolution);
      delay(150);
      break;
  }
} // main loop

