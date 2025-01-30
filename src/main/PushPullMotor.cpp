#include <Controllino.h>
#include "PushPullMotor.h"


PushPullMotor::PushPullMotor(byte forwardPin, byte backwardPin) {
  this->forwardPin = forwardPin;
  this->backwardPin = backwardPin;
  init();
}
void PushPullMotor::init() {
  pinMode(forwardPin, OUTPUT);
  pinMode(backwardPin, OUTPUT);
  this->direction = HIGH;
}

void PushPullMotor::setEnabled(int enable) {
    this->enable = enable;
    if(enable==LOW) {
        digitalWrite(forwardPin, LOW);
        digitalWrite(backwardPin, LOW);
    } else {
        setDirection(this->direction);
    }
}

void PushPullMotor::setDirection(int direction) {
    this->direction = direction;

    if(this->enable==LOW)
        return;

    if(direction==LOW) {
        digitalWrite(forwardPin, LOW);
        digitalWrite(backwardPin, HIGH);  
    } else {
        digitalWrite(forwardPin, HIGH);
        digitalWrite(backwardPin, LOW);  
    }
}

void PushPullMotor::changePosition() {
    if(this->direction==LOW) {
        setDirection(HIGH);
        delay(1500);
    } else {
        setDirection(LOW);
        delay(2000);
    }
}