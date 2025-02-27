#include <Servo.h>

// SERVOs
Servo rightfoot;
Servo righthigh;
Servo leftfoot;
Servo leftthigh;
int pos;

void setup() {
  //servo setup
  rightfoot.attach(6);
  righthigh.attach(7);
  leftfoot.attach(2);
  leftthigh.attach(3);
}

void loop() {
  // initialize position to 90
  rightfoot.write(90);
  righthigh.write(90);
  leftfoot.write(90);
  leftthigh.write(90);
  delay(1000);
  
// turn only right foot
// edit which to move
  rightfoot.write(90);
  righthigh.write(120);
  leftfoot.write(90);
  leftthigh.write(90);
  delay(1000);
}