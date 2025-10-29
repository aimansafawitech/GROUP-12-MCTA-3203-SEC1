#include <Servo.h>



int potPin = A0;
int ledPin = 7;
int potValue = 0;
String command = "";

void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  // Read potentiometer and send value to Python
  potValue = analogRead(potPin);
  Serial.println(potValue);
  delay(1000);
  // Check if Python sent a command
  if (Serial.available() > 0) {
    command = Serial.readStringUntil('\n');
    command.trim();

    if (command == "ON") {
      digitalWrite(ledPin, HIGH);
    } else if (command == "OFF") {
      digitalWrite(ledPin, LOW);
    }
  }
}
