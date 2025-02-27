int ledPin = 8; //select a digital I/O pin

void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  int remote = analogRead(A0);
  Serial.print("remote: "); Serial.println(remote);
  if (remote == 5) {
    digitalWrite(ledPin, HIGH); //set pin 8 output to HIGH, about 5v
    delay(1000);
  }//if
}//loop