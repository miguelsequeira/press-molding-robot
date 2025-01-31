#ifndef RUN_MODULE_H
#define RUN_MODULE_H
#include <Arduino.h>
class RunModule {

  public:
    RunModule();

    void run();
    void disableAll();
    void startup();
        void testRGBLeds();
        void turnAllOn();
        void turnAllOff();
};
#endif
