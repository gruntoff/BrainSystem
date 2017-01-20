#include <Arduino.h>

#include "PinChangeInt.h"

//PINS
#define RED_BTN 2
#define RED_LED 3
#define RED_LED_BOX A2

#define GREEN_BTN 5
#define GREEN_LED 6
#define GREEN_LED_BOX A4

#define GND1 4
#define GND2 7
#define GND3 A3
#define GND4 A5

#define RESET 12
#define START 11
#define FALSESTART 13
#define SPEAKER A0

#define SWITCH 8


//Variables

int btnCase = 0;
boolean started = false; //If Start button was pressed


//Functions
void resetPressed();
void checkReset();
void redBtnPressed();
void greenBtnPressed();
void startPressed();
void playStart();
void playFalseStart();
void playAnswer();
void falseStart();
boolean switchBrain();
void btnPressed();




boolean switchBrain() {
  if (digitalRead(SWITCH)) {
    return false;
  } else {
    return true;
  }
}



void resetPressed() {
    digitalWrite(RED_LED, LOW);
    digitalWrite(RED_LED_BOX, LOW);
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(GREEN_LED_BOX, LOW);
    digitalWrite(FALSESTART, LOW);
  btnCase = 0;
  if (switchBrain()) {
      started = false;
  }
}

void btnPressed() {
        if (switchBrain()) {
            if (!started) {
                falseStart();
            } else {
                playAnswer();
            }
        } else {
            playAnswer();
        }
        checkReset();
        resetPressed();
    }

void checkReset() {
  while (digitalRead(RESET)) {

  }
}

void redBtnPressed() {
  btnCase = 1;
};


void greenBtnPressed() {
  btnCase = 2;
}

void startPressed() {
  if (switchBrain()) {
    btnCase = 10;
  }
}

void playStart() {
  tone (SPEAKER, 1000, 500);
}

void playFalseStart() {
  tone (SPEAKER, 200, 700);
}

void playAnswer() {
  tone (SPEAKER, 500, 500);
}

void falseStart() {
  playFalseStart();
  digitalWrite(FALSESTART, HIGH);
}


void setup() {
  pinMode(RED_BTN, INPUT_PULLUP);
  pinMode(RED_LED, OUTPUT);
  pinMode(RED_LED_BOX, OUTPUT);

  pinMode(GREEN_BTN, INPUT_PULLUP);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(GREEN_LED_BOX, OUTPUT);

  //Box stuff
  pinMode(RESET, INPUT_PULLUP);
  pinMode(START, INPUT_PULLUP);
  pinMode(SPEAKER, OUTPUT);
  pinMode(FALSESTART, OUTPUT);
  pinMode(SWITCH, INPUT_PULLUP);

  //Ground
  pinMode(GND1, OUTPUT);
  pinMode(GND2, OUTPUT);
  pinMode(GND3, OUTPUT);
  pinMode(GND4, OUTPUT);

  digitalWrite(FALSESTART, LOW);

  digitalWrite(GND1, LOW);
  digitalWrite(GND2, LOW);
  digitalWrite(GND3, LOW);
  digitalWrite(GND4, LOW);
}

void loop() {
  attachPinChangeInterrupt(RED_BTN, redBtnPressed, FALLING);
  attachPinChangeInterrupt(GREEN_BTN, greenBtnPressed, FALLING);
  attachPinChangeInterrupt(START, startPressed, FALLING);



  switch (btnCase) {
    case 1:
      digitalWrite(RED_LED, HIGH);
      digitalWrite(RED_LED_BOX, HIGH);
      btnPressed();
      detachPinChangeInterrupt(RED_BTN);
      break;
    case 2:
      digitalWrite(GREEN_LED, HIGH);
      digitalWrite(GREEN_LED_BOX, HIGH);
      btnPressed();
      detachPinChangeInterrupt(GREEN_BTN);
      break;
    case 10:
    if (!started) {
      playStart();
      started = true;
      btnCase = 0;
    }
      break;
  }
  
}
