#include <Wire.h>
#include <MPU6050.h>
#include <Servo.h>

MPU6050 mpu;
Servo servo;

// --- Pin definitions ---0013070376
0013070376
0013070376

#define GREEN_LED 4
#define RED_LED 3

// --- Variables ---
int servoPosition = 90;  // default: locked

void setup() {
  Serial.begin(9600);
  Wire.begin();

  // Initialize MPU6050
  mpu.initialize();
  if (!mpu.testConnection()) {
    Serial.println("MPU6050 connection failed!");
    while (1);
  }

  // Setup servo & LEDs
  servo.attach(9);
  servo.write(servoPosition);

  pinMode(GREEN_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);

  digitalWrite(GREEN_LED, LOW);
  digitalWrite(RED_LED, HIGH);  // start locked

  Serial.println("Arduino ready.");
}

void loop() {
  // --- 1️⃣ Read motion data and send to Python ---
  int16_t ax, ay, az, gx, gy, gz;
  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

  Serial.print(ax);
  Serial.print(",");
  Serial.print(ay);
  Serial.print(",");
  Serial.println(az);
  delay(100);  // sampling rate ~10 Hz

  //
  if (Serial.available() > 0) {
    char cmd = Serial.read();

    if (cmd == 'A') {
      
      servo.write(180);
      digitalWrite(GREEN_LED, HIGH);
      digitalWrite(RED_LED, LOW);
      Serial.println("Unlocked (A)");
    }
    else if (cmd == 'D') {
      
      servo.write(90);
      digitalWrite(GREEN_LED, LOW);
      digitalWrite(RED_LED, HIGH);
      Serial.println("Locked (D)");
    }
  }
}
