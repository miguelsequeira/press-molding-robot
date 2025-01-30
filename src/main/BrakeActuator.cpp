#include "BrakeActuator.h"

BrakeActuator::BrakeActuator(byte pin) {
  this->pin = pin;
  init();
}

void BrakeActuator::init() {
  pinMode(pin, OUTPUT);
  setBrake(HIGH);
}

void BrakeActuator::setBrake(byte value) {
    if(value == HIGH) {
        this->brake = true;
    } else {
        this->brake = false;
    }
    digitalWrite(pin, value);
}

void BrakeActuator::changeBrakeState() {
  if(isBraked()) {
    setBrake(LOW);
  } else {
   setBrake(HIGH);
  }
}

bool BrakeActuator::isBraked(){
  return this->brake;
}