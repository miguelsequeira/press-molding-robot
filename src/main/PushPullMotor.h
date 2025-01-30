#ifndef PUSH_PULL_MOTOR_H
#define PUSH_PULL_MOTOR_H
#include <Arduino.h>
class PushPullMotor {

  private:
    int direction;
    int enable;
    byte forwardPin;
    byte backwardPin;

  public:
    PushPullMotor(byte forwardPin, byte backwardPin);

    void init();
    void setEnabled(int enabled);
    void setDirection(int direction);
    void changePosition();
    int getDirection();
};
#endif
