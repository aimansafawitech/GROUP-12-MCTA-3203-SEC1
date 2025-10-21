
//DEFINE SEGMENT PIN
const int segmentA = 3;  // D0
const int segmentB = 2;  // D1
const int segmentC = 8;  // D2
const int segmentD = 7;  // D3
const int segmentE = 6;  // D4
const int segmentF = 4;  // D5
const int segmentG = 5;  // D6
const int segmentDP = 9;  // DP
//DEFINE BUTTON
const int inc = 10; //INCBUTTON
const int reset = 11;  //REBUTTON

int num = 0;   // CURRENT NUMBER
int lastIncState = HIGH;
int lastResetState = HIGH;

int segments[] = {segmentA, segmentB, segmentC, segmentD, segmentE, segmentF, segmentG};

//SET ALL CLEAR SEGMENT FOR EACH NUMBER
void clear() {
  for (int i = 0; i < 7; i++) {
    digitalWrite(segments[i], HIGH); // HIGH = off 
  }
}
void displayDigit(int num) {
  clear(); 

  switch (num) {
    case 0: digitalWrite(segmentA, LOW); digitalWrite(segmentB, LOW); digitalWrite(segmentC, LOW);
            digitalWrite(segmentD, LOW); digitalWrite(segmentE, LOW); digitalWrite(segmentF, LOW); break;
    case 1: digitalWrite(segmentB, LOW); digitalWrite(segmentC, LOW); break;
    case 2: digitalWrite(segmentA, LOW); digitalWrite(segmentB, LOW); digitalWrite(segmentD, LOW);
            digitalWrite(segmentE, LOW); digitalWrite(segmentG, LOW); break;
    case 3: digitalWrite(segmentA, LOW); digitalWrite(segmentB, LOW); digitalWrite(segmentC, LOW);
            digitalWrite(segmentD, LOW); digitalWrite(segmentG, LOW); break;
    case 4: digitalWrite(segmentB, LOW); digitalWrite(segmentC, LOW);
            digitalWrite(segmentF, LOW); digitalWrite(segmentG, LOW); break;
    case 5: digitalWrite(segmentA, LOW); digitalWrite(segmentC, LOW); digitalWrite(segmentD, LOW);
            digitalWrite(segmentF, LOW); digitalWrite(segmentG, LOW); break;
    case 6: digitalWrite(segmentA, LOW); digitalWrite(segmentC, LOW); digitalWrite(segmentD, LOW);
            digitalWrite(segmentE, LOW); digitalWrite(segmentF, LOW); digitalWrite(segmentG, LOW); break;
    case 7: digitalWrite(segmentA, LOW); digitalWrite(segmentB, LOW); digitalWrite(segmentC, LOW); break;
    case 8: digitalWrite(segmentA, LOW); digitalWrite(segmentB, LOW); digitalWrite(segmentC, LOW);
            digitalWrite(segmentD, LOW); digitalWrite(segmentE, LOW); digitalWrite(segmentF, LOW);
            digitalWrite(segmentG, LOW);break;
    case 9: digitalWrite(segmentA, LOW); digitalWrite(segmentB, LOW); digitalWrite(segmentC, LOW);
            digitalWrite(segmentD, LOW); digitalWrite(segmentF, LOW); digitalWrite(segmentG, LOW); break;
  }
}


void setup() {
 
  pinMode(segmentA, OUTPUT);
  pinMode(segmentB, OUTPUT);
  pinMode(segmentC, OUTPUT);
  pinMode(segmentD, OUTPUT);
  pinMode(segmentE, OUTPUT);
  pinMode(segmentF, OUTPUT);
  pinMode(segmentG, OUTPUT);
  pinMode(segmentDP, OUTPUT);

  pinMode(inc, INPUT_PULLUP);
  pinMode(reset, INPUT_PULLUP);

  displayDigit(num);
}

void loop() {
int incStateNow = digitalRead(inc);
int resetStateNow = digitalRead(reset);

 if (incStateNow == LOW && lastIncState == HIGH) {
    num++;
    if (num > 9) num = 0; 
    displayDigit(num);
    delay(250); 
  }
 if (resetStateNow == LOW && lastResetState == HIGH) {
    num = 0;
    displayDigit(num);
    delay(250);
  }
lastIncState = incStateNow;
lastResetState = resetStateNow;
}