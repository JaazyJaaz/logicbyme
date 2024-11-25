
#include <Stepper.h>
#include <SoftwareSerial.h>

#define upperBtn_pin 6
#define upperBtnLed_pin 8
#define lowerBtn_pin 13
#define lowerBtnLed_pin 7


#define motor_in1_pin 10
#define motor_in2_pin 11
#define motor_in3_pin 12
#define motor_in4_pin 9

#define motor_potSpeed_pin 0 // pot pin
#define motor_stepPerRot 100 // steps per rotation
int motor_speed = 30;
int motor_speed_pev = 0;
int motor_speed_now = 0;

Stepper stepper = Stepper(motor_stepPerRot, motor_in1_pin, motor_in3_pin, motor_in2_pin, motor_in4_pin);



void setup() {
  Serial.begin(9600);
  stepper.setSpeed(30);
  // pinMode(ledPin, OUTPUT);
}

void loop() {
  motor_speed_now = analogRead(motor_speed_pin);  // pot

  stepper.step(motor_speed_now - motor_speed_pev);
  motor_speed_pev = motor_speed_now; // save prev val
}
