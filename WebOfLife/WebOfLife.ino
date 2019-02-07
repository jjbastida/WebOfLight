/*********************************************************
  This is a modified version of the library for the MPR121 12-channel Capacitive touch sensor
  Written by Limor Fried/Ladyada for Adafruit Industries.
  Modified by JJ Bastida
**********************************************************/
#include <Wire.h>
#include "Adafruit_MPR121.h"
#ifndef _BV
#define _BV(bit) (1 << (bit))
#endif
Adafruit_MPR121 cap = Adafruit_MPR121();

// Keeps track of the last pins touched
// so we know when buttons are 'released'
uint16_t lasttouched = 0;
uint16_t currtouched = 0;
int ledPinOne[] = {0, 1, 2};
int ledPinTwo[] = {3, 4, 5};
int ledPinThree[] = {6, 7, 8};
int ledPinFour[] = {9, 10, 11};
int ledPinFive[] = {12, 24, 25};
int ledPinSix[] = {26, 27, 28};
void setup() {
  Wire.begin();
  Serial.begin(9600);
  pinMode(ledPinOne[0], OUTPUT);
  pinMode(ledPinOne[1], OUTPUT);
  pinMode(ledPinOne[2], OUTPUT);
  pinMode(ledPinTwo[0], OUTPUT);
  pinMode(ledPinTwo[1], OUTPUT);
  pinMode(ledPinTwo[2], OUTPUT);
  pinMode(ledPinThree[0], OUTPUT);
  pinMode(ledPinThree[1], OUTPUT);
  pinMode(ledPinThree[2], OUTPUT);
  pinMode(ledPinFour[0], OUTPUT);
  pinMode(ledPinFour[1], OUTPUT);
  pinMode(ledPinFour[2], OUTPUT);
  pinMode(ledPinFive[0], OUTPUT);
  pinMode(ledPinFive[1], OUTPUT);
  pinMode(ledPinFive[2], OUTPUT);
  pinMode(ledPinSix[0], OUTPUT);
  pinMode(ledPinSix[1], OUTPUT);
  pinMode(ledPinSix[2], OUTPUT);
  Serial.println("HI");
  while (!Serial) {
    delay(10);
  }
  if (!cap.begin(0x5A)) {
    Serial.println("MPR121 not found, check wiring?");
    while (1);
  }
}

void loop() {
  // Get the currently touched pads
  currtouched = cap.touched();
  for (uint8_t i = 0; i < 12; i++) {
    if ((currtouched & _BV(i)) && !(lasttouched & _BV(i)) ) {
      if (i == 0) {
        setColor(0, 255, 0, 0);
      }
      else if (i == 1) {
        setColor(255, 225, 0, 1);
      }
      else if (i == 2) {
        setColor(255, 225, 0, 2);
      }
      else if (i == 3) {
        setColor(255, 255, 0, 3);
      }
      else if (i == 4) {
        setColor(255, 0, 255, 4);
      }
      else if (i == 5) {
        setColor(0, 255, 255, 5);
      };
    }
    // if it *was* touched and now *isnt*, alert!
    if (!(currtouched & _BV(i)) && (lasttouched & _BV(i)) ) {
      if (i == 0) {
        setColor(0, 0, 0, 0);
      }
      else if (i == 1) {
        setColor(0, 0, 0, 1);
      }
      else if (i == 2) {
        setColor(0, 0, 0, 2);
      }
      else if (i == 3) {
        setColor(0, 0, 0, 3);
      }
      else if (i == 4) {
        setColor(0, 0, 0, 4);
      }
      else if (i == 5) {
        setColor(0, 0, 0, 5);
      };
    }
  }
  lasttouched = currtouched;
  // put a delay so it isn't overwhelming
  delay(100);
}
void setColor(int red, int green, int blue, int pinN) {
  if (pinN == 0) {
    analogWrite(ledPinOne[0], red);
    analogWrite(ledPinOne[1], green);
    analogWrite(ledPinOne[2], blue);
  }
  else if (pinN == 1) {
    analogWrite(ledPinTwo[0], red);
    analogWrite(ledPinTwo[1], green);
    analogWrite(ledPinTwo[2], blue);
  }
  else if (pinN == 2) {
    analogWrite(ledPinThree[0], red);
    analogWrite(ledPinThree[1], green);
    analogWrite(ledPinThree[2], blue);
  }
  else if (pinN == 3) {
    analogWrite(ledPinFour[0], red);
    analogWrite(ledPinFour[1], green);
    analogWrite(ledPinFour[2], blue);
  }
  else if (pinN == 4) {
    analogWrite(ledPinFive[0], red);
    analogWrite(ledPinFive[1], green);
    analogWrite(ledPinFive[2], blue);
  }
  else if (pinN == 5) {
    analogWrite(ledPinSix[0], red);
    analogWrite(ledPinSix[1], green);
    analogWrite(ledPinSix[2], blue);
  }
}
