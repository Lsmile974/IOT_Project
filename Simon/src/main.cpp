#include <Arduino.h>

const int buttonG = 12;
const int ledG =  18;
const int buttonY = 14;
const int ledY =  05;
const int buttonB = 27;
const int ledB =  17;
const int buttonR = 26;
const int ledR =  16;
const int buzzer = 32;


int gButtonState = 0;
int yButtonState = 0;
int bButtonState = 0;
int rButtonState = 0;

// put function declarations here:
//int myFunction(int, int);

void setup() {
  Serial.begin(115200);
  pinMode(buttonG, INPUT_PULLUP);
  pinMode(ledG, OUTPUT);
  pinMode(buttonY, INPUT_PULLUP);
  pinMode(ledY, OUTPUT);
  pinMode(buttonB, INPUT_PULLUP);
  pinMode(ledB, OUTPUT);
  pinMode(buttonR, INPUT_PULLUP);
  pinMode(ledR, OUTPUT);
  pinMode(buzzer, OUTPUT);
}

void loop() {
  gButtonState = digitalRead(buttonG);
  Serial.println("green:" + gButtonState);
  if (gButtonState == LOW) {
      digitalWrite(ledG, HIGH);
      tone(buzzer, 262, 10);

  } else {
      digitalWrite(ledG, LOW);
  }
  yButtonState = digitalRead(buttonY);
  Serial.println("yellow:" + yButtonState);
  if (yButtonState == LOW) {
      digitalWrite(ledY, HIGH);
      tone(buzzer, 294, 10);
  } else {
      digitalWrite(ledY, LOW);
  }
  bButtonState = digitalRead(buttonB);
  Serial.println("green:" + bButtonState);
  if (bButtonState == LOW) {
      digitalWrite(ledB, HIGH);
      tone(buzzer, 330, 10);
  } else {
      digitalWrite(ledB, LOW);
  }
  rButtonState = digitalRead(buttonR);
  Serial.println("yellow:" + rButtonState);
  if (rButtonState == LOW) {
      digitalWrite(ledR, HIGH);
      tone(buzzer, 349, 10);
  } else {
      digitalWrite(ledR, LOW);
  }
}

// put function definitions here:
//int myFunction(int x, int y) {
//  return x + y;
//}