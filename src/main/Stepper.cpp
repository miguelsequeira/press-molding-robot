#include <Controllino.h>
#include "Stepper.h"

Stepper::Stepper(byte enablePin, byte directionPin, byte pulsePin) {
    this->enablePin = enablePin;
    this->directionPin = directionPin;
    this->pulsePin = pulsePin;
    this->appliedPower = 0;
    init();
    
    // Set default speeds
    if (pulsePin == CONTROLLINO_D2) {  // ZZ stepper
        this->speed = 60;   // 60 RPM
    } else {                // YY stepper
        this->speed = 30000; // 1000 RPM
    }
}

void Stepper::init() {
    pinMode(enablePin, OUTPUT);
    pinMode(directionPin, OUTPUT);
    pinMode(pulsePin, OUTPUT);
    digitalWrite(enablePin, LOW);  // Start disabled
}

void Stepper::setEnabled(int enabled) {
    digitalWrite(enablePin, enabled);
}

void Stepper::setDirection(int direction) {
    digitalWrite(directionPin, direction);
}

void Stepper::setAppliedPower(int appliedPower) {
    if (appliedPower > 0) {
        // Calculate pulse delay based on speed (RPM)
        // Steps per revolution = 400
        // RPM to steps per second = (RPM * 400) / 60
        // Microseconds per step = 1000000 / steps per second
        unsigned long stepsPerSecond = (speed * 400UL) / 60;
        unsigned long microsPerStep = 1000000UL / stepsPerSecond;
        
        // Generate a step pulse
        digitalWrite(pulsePin, HIGH);
        delayMicroseconds(microsPerStep / 2);
        digitalWrite(pulsePin, LOW);
        delayMicroseconds(microsPerStep / 2);
    }
}

void Stepper::setSpeed(int speed) {
    this->speed = speed;
}

int Stepper::getSpeed() {
    return speed;
}

int Stepper::getAppliedPower() {
    return digitalRead(pulsePin);
}
