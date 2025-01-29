#include "Button.h"

Button::Button() {
}

Button::Button(int position, byte pinIn, byte pinLed) {
  this->position = position;
  this->pinIn = pinIn;
  this->pinLed = pinLed;
  //init();
  setLedOff();
}

void Button::init() {
//  pinMode(pinIn, INPUT);
//  pinMode(pinLed, OUTPUT);
}

bool Button::isClosed() {
//
//    digitalWrite(pinOut1, out1Value);
//    digitalWrite(pinOut2, out2Value);
//    int value = analogRead(pinIn);
//    return (value > 358);
    return isPressed;
}

void Button::setLedOn() {
  digitalWrite(pinLed, HIGH);
}
void Button::setLedOff() {
  digitalWrite(pinLed, LOW);
}
int Button::getCode() {
    return position;
}