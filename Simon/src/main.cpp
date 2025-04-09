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

char input = 'N';
bool gState = false;
bool yState = false;
bool bState = false;
bool rState = false;

// put function declarations here:
//int myFunction(int, int);
void update();
void IRAM_ATTR gTrigger();
void IRAM_ATTR yTrigger();
void IRAM_ATTR bTrigger();
void IRAM_ATTR rTrigger();

void setup() {
  Serial.begin(115200);
  pinMode(buttonG, INPUT_PULLUP);
  attachInterrupt(buttonG, gTrigger, CHANGE);
  pinMode(ledG, OUTPUT);
  pinMode(buttonY, INPUT_PULLUP);
  attachInterrupt(buttonY, yTrigger, CHANGE);
  pinMode(ledY, OUTPUT);
  pinMode(buttonB, INPUT_PULLUP);
  attachInterrupt(buttonB, bTrigger, CHANGE);
  pinMode(ledB, OUTPUT);
  pinMode(buttonR, INPUT_PULLUP);
  attachInterrupt(buttonR, rTrigger, CHANGE);
  pinMode(ledR, OUTPUT);
  pinMode(buzzer, OUTPUT);
}

void loop() {
  update();
}

void update(){
  if (gState){
    digitalWrite(ledG, HIGH);
    tone(buzzer, 262, 10);
  }
  else{
    digitalWrite(ledG, LOW);
  }
  if (yState){
    digitalWrite(ledY, HIGH);
    tone(buzzer, 294, 10);
  }
  else{
    digitalWrite(ledY, LOW);
  }
  if (bState){
    digitalWrite(ledB, HIGH);
    tone(buzzer, 330, 10);
  }
  else{
    digitalWrite(ledB, LOW);
  }
  if (rState){
    digitalWrite(ledR, HIGH);
    tone(buzzer, 349, 10);
  }
  else{
    digitalWrite(ledR, LOW);
  }
}

void IRAM_ATTR gTrigger() {
  gState = !gState;
}

void IRAM_ATTR yTrigger() {
  yState = !yState;
}

void IRAM_ATTR bTrigger() {
  bState = !bState;
}

void IRAM_ATTR rTrigger() {
  rState = !rState;
}