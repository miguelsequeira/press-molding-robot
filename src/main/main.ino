#include <Controllino.h>
#include "TestsModule.h"
#include "Led.h"
#include "InductiveSensor.h"

void setup() {
    Serial.begin(9600); // open the serial port at 9600 bps:

    int machineOn = HIGH;
    
    // In service
    digitalWrite(CONTROLLINO_R0, machineOn); // Security Contactor
    digitalWrite(CONTROLLINO_R1, machineOn); // Light/Fan Relay
}


void loop() {
    runTests();
}

void runTests() {
    TestsModule tests = TestsModule();
    tests.run();
}
