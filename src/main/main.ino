  #include <Controllino.h>
#include "RunModule.h"

RunModule module = RunModule();

void setup() {
    Serial.begin(115200); // open the serial port at 9600 bps:

    int machineOn = HIGH;
    
    // In service
    digitalWrite(CONTROLLINO_R0, machineOn); // Security Contactor
    digitalWrite(CONTROLLINO_R1, machineOn); // Light/Fan Relay
    module.startup();
}

void loop() {
    module.run();
}
