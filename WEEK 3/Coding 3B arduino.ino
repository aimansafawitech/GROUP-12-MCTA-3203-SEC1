#include <Servo.h>

Servo myservo;
int potPin = A0;
int gledPin = 7;
int yledPin = 6;
int rledPin = 5;
int potValue = 0;
int angle = 0;
bool manualMode = false;  // start in potentiometer mode

void dark (){
digitalWrite(gledPin, LOW);
digitalWrite(yledPin, LOW);
digitalWrite(rledPin, LOW);

}


void setup() {
  myservo.attach(12);
  pinMode(gledPin, OUTPUT);
  pinMode(yledPin, OUTPUT);
  pinMode(rledPin, OUTPUT);
  Serial.begin(9600);
  Serial.println("Arduino ready.");
}

void loop() {
  if (Serial.available() > 0) {
    String data = Serial.readStringUntil('\n');
    data.trim();

    if (data.equalsIgnoreCase("pot")) {
      manualMode = false;
      Serial.println("Switched to POT mode");
    } 
    else if (data.equalsIgnoreCase("manual")) {
      manualMode = true;
      Serial.println("Switched to MANUAL mode");
    } 
    else if (manualMode && data.toInt() >= 0 && data.toInt() <= 180) {
      angle = data.toInt();
      myservo.write(angle);
      Serial.print("Manual angle set to: ");
      Serial.println(angle);
    }
  }

  //using potentiometer mode
  if (!manualMode) {
    potValue = analogRead(potPin);
    angle = map(potValue, 0, 1023, 0, 180);
    myservo.write(angle);

    if (angle < 60){ 
      dark ();
      digitalWrite(gledPin, HIGH);
      }
    else if (angle > 60 && angle < 120){
      dark ();
      digitalWrite(yledPin, HIGH);
      }
    else if (angle > 120){
      dark ();
      digitalWrite(rledPin, HIGH);
    }

    Serial.println(angle);
    delay(100);
  }
}