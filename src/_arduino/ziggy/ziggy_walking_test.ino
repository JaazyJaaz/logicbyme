#include <Servo.h>

// SERVOs
Servo rightfoot;
Servo righthigh;
Servo leftfoot;
Servo leftthigh;
// Servo neck;
int pos;

void setup() {
  Serial.begin(9600);
  //servo setup
  rightfoot.attach(6);
  righthigh.attach(7);
  leftfoot.attach(2);
  leftthigh.attach(3);
  // neck.attach(6);
  //led
  pinMode(10, OUTPUT);
}

void loop() {
  digitalWrite(10, LOW);    // turn the LED off by making the voltage LOW

  ////////////////////SERVO//////////////////////////////
  //zero out servos to 90 degrees
  rightfoot.write(90);
  righthigh.write(90);
  leftfoot.write(90);
  leftthigh.write(90);
  //neck.write(90);
  delay(2000);


  //1. tilt right foot out
  rightfoot.write(70);
  righthigh.write(90);
  leftfoot.write(90);
  leftthigh.write(90);
  delay(1000);

  //2. tilt left theigh forward & push with foot
  rightfoot.write(70);
  righthigh.write(90); 
  leftfoot.write(90); 
  leftthigh.write(160); //forward
  delay(1000);

  //3. tilt right theigh back
  rightfoot.write(90);
  righthigh.write(120);
  leftfoot.write(90);
  leftthigh.write(90);
  delay(2000);

  //3. tilt right theigh back
  rightfoot.write(90);
  righthigh.write(120);
  leftfoot.write(90);
  leftthigh.write(120);
  delay(2000);

  //blink led
  digitalWrite(10, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);              // wait for a second
  digitalWrite(10, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);              // wait for a second
  //////////////////////3-23

    //left foot
  rightfoot.write(90);
  righthigh.write(90);
  leftfoot.write(120);
  leftthigh.write(90);
  delay(500);

  rightfoot.write(90);
  righthigh.write(90);
  leftfoot.write(120);
  leftthigh.write(60);
  delay(500);
  
      //blink led
  digitalWrite(10, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(500);              // wait for a second
  digitalWrite(10, LOW);    // turn the LED off by making the voltage LOW
  delay(500);              // wait for a second

//test 
  // init pos
  rightfoot.write(90);
  righthigh.write(90);
  leftfoot.write(90);
  leftthigh.write(90);
  delay(1000); 
//right foot
  rightfoot.write(120);
  righthigh.write(90);
  leftfoot.write(90);
  leftthigh.write(90);
  delay(1500); // pause 1.5 seconds
  // reset pos
  rightfoot.write(90);
  righthigh.write(90);
  leftfoot.write(90);
  leftthigh.write(90);
  delay(1000);

//left foot
  rightfoot.write(90);
  righthigh.write(90);
  leftfoot.write(120);
  leftthigh.write(90);
  delay(1500); // pause 1.5 seconds
  // reset
  rightfoot.write(90);
  righthigh.write(90);
  leftfoot.write(90);
  leftthigh.write(90);
  delay(1000);

//right thigh
  rightfoot.write(90);
  righthigh.write(120);
  leftfoot.write(90);
  leftthigh.write(90);
  delay(1500); // pause 1.5 seconds
  // reset
  rightfoot.write(90);
  righthigh.write(90);
  leftfoot.write(90);
  leftthigh.write(90);
  delay(1000);

//left thigh
  rightfoot.write(90);
  righthigh.write(90);
  leftfoot.write(90);
  leftthigh.write(120);
  delay(1000);
  // reset
  rightfoot.write(90);
  righthigh.write(90);
  leftfoot.write(90);
  leftthigh.write(90);
  delay(1000);

      //blink led
  digitalWrite(10, HIGH);   
  delay(500);           
  digitalWrite(10, LOW);    
  delay(500);              
      //blink led
  digitalWrite(10, HIGH);  
  delay(500);              
  digitalWrite(10, LOW);   
  delay(500);             
      //blink led
  digitalWrite(10, HIGH);   
  delay(500);              
  digitalWrite(10, LOW);    
  delay(500);              

    //3.
    rightfoot.write(90);
    righthigh.write(110);
    leftfoot.write(115);
    leftthigh.write(110);
    delay(500);

    rightfoot.write(90);
    righthigh.write(70);
    leftfoot.write(115);
    leftthigh.write(70);
    delay(1500);

    rightfoot.write(90);
    righthigh.write(70);
    leftfoot.write(90);
    leftthigh.write(70);
    delay(1500);
     
    //1. tilt right foot out
    rightfoot.write(70);
    righthigh.write(90);
    leftfoot.write(90);
    leftthigh.write(90);
    delay(500);

    //2. tilt left theigh forward
    rightfoot.write(70);
    righthigh.write(90);
    leftfoot.write(90);
    leftthigh.write(110);
    delay(500);

    //3. tilt right theigh back
    rightfoot.write(70);
    righthigh.write(110);
    leftfoot.write(90);
    leftthigh.write(110);
    delay(1500);


    //4. tilt left foot out
    rightfoot.write(90);
    righthigh.write(110);
    leftfoot.write(110);
    leftthigh.write(110);
    delay(500);

    //5. tilt right thigh to int
    rightfoot.write(90);
    righthigh.write(90);
    leftfoot.write(110);
    leftthigh.write(110);
    delay(500);

    //6. tilt left foot to int
    rightfoot.write(90);
    righthigh.write(90);
    leftfoot.write(90);
    leftthigh.write(110);
    delay(500);

    //4. tilt right foot out
    rightfoot.write(65);
    righthigh.write(110);
    leftfoot.write(90);
    leftthigh.write(110);
    delay(500);

    //5. tilt right to int pos
    rightfoot.write(90);
    righthigh.write(110);
    leftfoot.write(90);
    leftthigh.write(110);
    delay(500);

  //////////test each servo////////////

    //tilt right foot in
    rightfoot.write(110);
    righthigh.write(90);
    leftfoot.write(90);
    leftthigh.write(90);
    delay(2000);

    //zero out servos to 90 degrees
    rightfoot.write(90);
    righthigh.write(90);
    leftfoot.write(90);
    leftthigh.write(90);
    //neck.write(90);
    delay(1000);

    //tilt left thigh back
    rightfoot.write(90);
    righthigh.write(110);
    leftfoot.write(90);
    leftthigh.write(90);
    delay(2000);

    /////////////////
    //zero out servos to 90 degrees
    rightfoot.write(90);
    righthigh.write(90);
    leftfoot.write(90);
    leftthigh.write(90);
    //neck.write(90);
    delay(1000);

    //tilt left foot out
    rightfoot.write(90);
    righthigh.write(90);
    leftfoot.write(110);
    leftthigh.write(90);
    delay(2000);

    //zero out servos to 90 degrees
    rightfoot.write(90);
    righthigh.write(90);
    leftfoot.write(90);
    leftthigh.write(90);
    //neck.write(90);
    delay(1000);

    //tilt left thigh forward
    rightfoot.write(90);
    righthigh.write(90);
    leftfoot.write(90);
    leftthigh.write(110);
    delay(1000);

    //tilt left thigh back
    rightfoot.write(90);
    righthigh.write(90);
    leftfoot.write(90);
    leftthigh.write(50);
    delay(1000);

    //moving the left theigh forward
    rightfoot.write(110);
    righthigh.write(90);
    leftfoot.write(90);
    leftthigh.write(50);
    delay(1000);

    //move right thigh back & tilt right foot back
    rightfoot.write(90);
    righthigh.write(120);
    leftfoot.write(90);
    leftthigh.write(50);
    delay(1000);

    //untilt foot
    rightfoot.write(90);
    righthigh.write(90);
    leftfoot.write(140);
    leftthigh.write(150);
    delay(1000);

    //tilt left foot & move rigt hip
    rightfoot.write(90);
    righthigh.write(90);
    leftfoot.write(90);
    leftthigh.write(150);
    delay(500);

    //untilt foot
    rightfoot.write(90);
    righthigh.write(90);
    leftfoot.write(90);
    leftthigh.write(90);
    delay(1000);

    //tilt foot
    righthigh.write(90);
    rightfoot.write(150);
    leftfoot.write(90);
    leftthigh.write(90);
    delay(1000);

    //move hip
    righthigh.write(140);
    rightfoot.write(150);
    leftfoot.write(90);
    leftthigh.write(90);
    delay(1000);

    righthigh.write(140);
    rightfoot.write(90);
    leftfoot.write(90);
    leftthigh.write(90);
    delay(1000);

    righthigh.write(90);
    rightfoot.write(90);
    leftfoot.write(90);
    leftthigh.write(90);
    delay(1000);

    rightfoot.write(90);
    righthigh.write(80);
    leftfoot.write(115);
    leftthigh.write(100);
    delay(1500);

    rightfoot.write(90);
    righthigh.write(70);
    leftfoot.write(90);
    leftthigh.write(70);
    delay(1500);
}