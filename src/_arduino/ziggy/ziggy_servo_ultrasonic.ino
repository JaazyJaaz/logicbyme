//*
 * Digital Pin connections
 * 01: -
 * 02: left thigh       *servo
 * 03: left foot        *servo
 * 04: trig input       *ultrasonic sensor
 * 05: echo input       *ultrasonic sensor
 * 06: neck             *servo
 * 07: right foot       *servo
 * 08: right thigh      *servo
 * 09: -
 * 10: -
 * 11: - *IR reviever
 * 12: -
 * 13: -
 * 
 * Analogue Pin connections
 * A01: 
 * A02: 
 * A03: 
 * A04: 
 * A05: 
 * A06: 
 * 
 * IR remote: ?!
 * 
 * 
 *To do: 
 * LCD: real time clock, date
 * 8x8 LCD dot matrix : binary clock
 * connect IR remote and code
 * look up lego mindstorm
 * make body armor to strengthen body, pekka-hulk lfg! :)
 */
 
#include <Servo.h> 

// LEGS/THIGH SERVO
Servo rightfoot;
Servo righthigh;
Servo leftfoot;
Servo leftthigh;
 int pos;
 
 // NECK SERVO
Servo neck;

//Ultrasonic Senor Monitor
int trig = 4; // attach pin 3 to Trig
int echo = 5; //attach pin 4 to Echo


void setup() {
 
Serial.begin(9600); 

//servo setup
rightfoot.attach(7);
righthigh.attach(8);
leftfoot.attach(2);
leftthigh.attach(3);
neck.attach(6);
}

void loop() {
  
/////////////Ultrasonic Senor Monitor////////////////////
// establish variables for duration of the ping,
// and the distance result in inches and centimeters:

long duration, inches, cm;

// The PING))) is triggered by a HIGH pulse of 2 or more microseconds.
// Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
pinMode(trig, OUTPUT);
digitalWrite(trig, LOW);
delayMicroseconds(2);
digitalWrite(trig, HIGH);
delayMicroseconds(5);
digitalWrite(trig, LOW);

// The same pin is used to read the signal from the PING))): a HIGH
// pulse whose duration is the time (in microseconds) from the sending
// of the ping to the reception of its echo off of an object.
pinMode(echo,INPUT);
duration = pulseIn(echo, HIGH);

// convert the time into a distance
inches = microsecondsToInches(duration);
cm = microsecondsToCentimeters(duration);

Serial.print(inches);
Serial.print("in, ");
Serial.print(cm);
Serial.print("cm");
Serial.println();
delay(100);
}

///////SERVO//////////////
//zero out servos to 90 degrees
rightfoot.write(90);
righthigh.write(90);
leftfoot.write(90);
leftthigh.write(90);
//neck.write(90);
delay(1000);

//tilt left foot
rightfoot.write(90);
righthigh.write(90);
leftfoot.write(140);
leftthigh.write(90);
delay(500);

//moving the right theigh 
rightfoot.write(90);
righthigh.write(150);
leftfoot.write(130);
leftthigh.write(90);
delay(1000);

//move left hip
rightfoot.write(90);
righthigh.write(150);
leftfoot.write(90);
leftthigh.write(40);
delay(1000);

//untilt foot
rightfoot.write(90);
righthigh.write(90);
leftfoot.write(140);
leftthigh.write(150);
delay(1000);

/////
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

/////////////Ultrasonic Senor Monitor////////////////////
//Outside of the loop

long microsecondsToInches(long microseconds)
{
// According to Parallax's datasheet for the PING))), there are
// 73.746 microseconds per inch (i.e. sound travels at 1130 feet per
// second). This gives the distance travelled by the ping, outbound
// and return, so we divide by 2 to get the distance of the obstacle.
// See: http://www.parallax.com/dl/docs/prod/acc/28015-PI...
return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds)
{
// The speed of sound is 340 m/s or 29 microseconds per centimeter.
// The ping travels out and back, so to find the distance of the
// object we take half of the distance travelled.
return microseconds / 29 / 2;
}