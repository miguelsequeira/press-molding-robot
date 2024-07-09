#include <Controllino.h>
#include "MainModule.h"
#include "Devices.h"


Led leds[] = {Led(CONTROLLINO_D8), Led(CONTROLLINO_D9), Led(CONTROLLINO_D10)};
Led topLed = {Led(CONTROLLINO_D8, CONTROLLINO_D9, CONTROLLINO_D10)};
Led handRGBLed = {Led(CONTROLLINO_D15, CONTROLLINO_D16, CONTROLLINO_D17)};

Led handLeds[] = {Led(CONTROLLINO_D15, CONTROLLINO_D16, CONTROLLINO_D17), Led(CONTROLLINO_D18), Led(CONTROLLINO_D19), Led(CONTROLLINO_D20), Led(CONTROLLINO_D21), Led(CONTROLLINO_D22), Led(CONTROLLINO_D23)};

Stepper stepperYY = Stepper(CONTROLLINO_D3, CONTROLLINO_D4, CONTROLLINO_D5);
Stepper stepperZZ = Stepper(CONTROLLINO_D0, CONTROLLINO_D1, CONTROLLINO_D2);
LinearActuator linearActuator = LinearActuator(CONTROLLINO_D6, CONTROLLINO_D7);
PushPullMotor pushPullMotor = PushPullMotor(CONTROLLINO_R14, CONTROLLINO_R15);
InductiveSensor sensor = InductiveSensor(CONTROLLINO_A1);
BrakeActuator brakeActuator = BrakeActuator(CONTROLLINO_R12);


byte handControllerIns[] = {CONTROLLINO_A10, CONTROLLINO_A11, CONTROLLINO_A12, CONTROLLINO_A13};
byte handControllerOuts[] = {CONTROLLINO_D13, CONTROLLINO_D14};
byte handControllerLeds[] = {CONTROLLINO_D18, CONTROLLINO_D19, CONTROLLINO_D20, CONTROLLINO_D21, CONTROLLINO_D22, CONTROLLINO_D23};
HandController handController = HandController(handControllerIns, handControllerOuts, handControllerLeds);

MainModule::MainModule() {
}

void MainModule::run() {
//
    disableAll();

    //runActuators();
    //runSensors();
}

void MainModule::runManual() {
//
    disableAll();

    //runActuators();
    //runSensors();
}

void MainModule::disableAll() {
//    brakeActuator.setBrake(HIGH);
//    stepperYY.setEnabled(LOW);
//    stepperZZ.setEnabled(LOW);
//    linearActuator.setEnabled(LOW);
//    pushPullMotor.setEnabled(LOW);
int a = 2;
}
