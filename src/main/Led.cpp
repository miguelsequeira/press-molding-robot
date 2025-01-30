#include "Led.h"

Led::Led() {
}

Led::Led(byte pin) {
  this->pin = pin;
  init();
}
Led::Led(byte pinR, byte pinG, byte pinB) {
  this->pin = pinR;
  this->pinG = pinG;
  this->pinB = pinB;
  initRGB();
}
void Led::init() {
  pinMode(pin, OUTPUT);
  off();
}
void Led::initRGB() {
  pinMode(pin, OUTPUT);
  pinMode(pinG, OUTPUT);
  pinMode(pinB, OUTPUT);
  offRGB();
}
void Led::on() {
  digitalWrite(pin, HIGH);
}
void Led::off() {
  digitalWrite(pin, LOW);
}
void Led::onRGB(int val1, int val2, int val3) {
  digitalWrite(pin, val1);
  digitalWrite(pinG, val2);
  digitalWrite(pinB, val3);
}

void Led::offRGB() {
  digitalWrite(pin, LOW);
  digitalWrite(pinG, LOW);
  digitalWrite(pinB, LOW);
}