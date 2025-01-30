#ifndef BRAKE_ACTUATOR_H
#define BRAKE_ACTUATOR_H
#include <Arduino.h>
class BrakeActuator {

  private:
    bool brake;
    byte pin;

  public:
    BrakeActuator(byte pin);

    void init();
    void setBrake(byte value);
    bool isBraked();
    void changeBrakeState();
};
#endif
