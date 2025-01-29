#ifndef HAND_CONTROLLER_H
#define HAND_CONTROLLER_H


#include <Controllino.h>
#include "Button.h"

class HandController {

  private:
    byte* pinIn;
    byte* pinLed;
    Button* buttons;

  public:
    HandController(byte pinIn[], byte pinLed[]);

    void init();

    int getClosedButton();
    Button* getClosedButtonObj();

    void checkPinA9Buttons();
    void checkPinA10Buttons();
    void checkPinA11Buttons();
    void checkPinA12Buttons();

    void updateButtonStates();
    void updateLEDs();
};
#endif
