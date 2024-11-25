// 11-25-2024
#include <Stepper.h>
#include <SoftwareSerial.h>

#define upBtn_pin 6 // in
#define upBtnLed_pin 8 // out
#define lowBtn_pin 13 // in
#define lowBtnLed_pin 7 // out

#define topMicroSwitch_pin 4 // top stopper
#define lowMicroSwitch_pin 5 // bot stopper

#define motorIn1_pin 10 // out
#define motorIn2_pin 11 // out
#define motorIn3_pin 12 // out
#define motorIn4_pin 9 // out
#define motorSpeedPot_pin 1 // input potentiometer pin A1
#define motorSpeed_stepPerRot 100 // steps per rotation
int motorSpeed_set = 30;
int motorSpeed_pev = 0;
int motorSpeed_now = 0;

Stepper stepper = Stepper(motorSpeed_stepPerRot, motorIn1_pin, motorIn3_pin, motorIn2_pin, motorIn4_pin);

void setup() {
  Serial.begin(9600);
  
  // set pins
  // outpput: push button LEDs
  pinMode(upBtnLed_pin, OUTPUT);
  pinMode(lowBtnLed_pin, OUTPUT);
  // input: push buttons switch
  pinMode(upBtnLed_pin, INPUT);
  pinMode(lowBtnLed_pin, INPUT);
  // stepper motor: output
  stepper.setSpeed(motorSpeed_set);
  pinMode(motorIn1_pin, OUTPUT);
  pinMode(motorIn2_pin, OUTPUT);
  pinMode(motorIn3_pin, OUTPUT);
  pinMode(motorIn4_pin, OUTPUT);
  // stepper motor: input analogue 
  pinMode(motorSpeedPot_pin,m INPUT); // potentiometer
  // top & lower stopper micro switches: input
  pinMode(topMicroSwitch_pin, INPUT);
  pinMode(lowMicroSwitch_pin, INPUT);
}

void loop() {
  motor_speed_now = analogRead(motor_speed_pin);  // pot

  stepper.step(motor_speed_now - motor_speed_pev);
  motor_speed_pev = motor_speed_now; // save prev val
}
