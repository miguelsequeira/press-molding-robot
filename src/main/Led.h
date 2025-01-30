#ifndef LED_H
#define LED_H
#include <Arduino.h>
class Led {
  
  private:
    byte pin;
    byte pinG;
    byte pinB;
    
  public:
    // Setup pin LED and call init()
    Led();
    Led(byte pin);
    Led(byte pinR, byte pinG, byte pinB);
    // Setup the pin led as OUTPUT
    // and power off the LED - default state
    void init();
    void initRGB();
    
    // Power on the LED
    void on();
    void onRGB(int val1, int val2, int val3);
    // Power off the LED
    void off();
    void offRGB();
};
#endif
