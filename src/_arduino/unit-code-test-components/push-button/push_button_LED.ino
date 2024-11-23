int LEDpin = 3;
int buttonPin = 2;
int readValue = 0;

void setup() {
  pinMode(buttonPin, INPUT); // button
  pinMode(LEDpin, OUTPUT); // LED
}

void loop() {
  readValue = digitalRead(buttonPin);
  if (readValue == 1){
    digitalWrite(LEDpin,HIGH);
  }
}