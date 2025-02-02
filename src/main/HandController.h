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

    Button* getClosedButton();

    void checkPinA9Buttons();
    void checkPinA10Buttons();
    void checkPinA11Buttons();
    void checkPinA12Buttons();

    void updateButtonStates();
    void setButtonLedOn(byte button);
    void setButtonLedOff(byte button);
    int getNumberOfClosedButtons();
};
#endif
