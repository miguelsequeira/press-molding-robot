#ifndef STEPPER_H
#define STEPPER_H

#include <Arduino.h>

class Stepper {
private:
    
    
    byte enablePin;
    byte directionPin;
    byte pulsePin;
    int speed;
    int appliedPower;
    void init();
    //ini  direction;
    
public:
    Stepper(byte enablePin, byte directionPin, byte pulsePin);
    // void init();
    void setEnabled(int enabled);
    void setDirection(int direction);
    void setAppliedPower(int appliedPower);
    void setSpeed(int speed);
    int getSpeed();
    int getAppliedPower();
};

#endif
