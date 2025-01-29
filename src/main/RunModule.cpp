#define ENCODER_OPTIMIZE_INTERRUPTS
#include <Controllino.h>
#include <Encoder.h>
#include "RunModule.h"
#include "State.h"
#include "Led.h"
#include "InductiveSensor.h"
#include "Encoder.h"
#include "BrakeActuator.h"
#include "Stepper.h"
#include "LinearActuator.h"
#include "PushPullMotor.h"
#include "HandController.h"


#define BTN_ROTATION_LOCK     0
#define BTN_LEFT              1
#define BTN_UP                2
#define BTN_TRACK_LOCK        3
#define BTN_GRAB_MOLD         4
#define BTN_RIGHT             5
#define BTN_DOWN              6


Led leds[] = {Led(CONTROLLINO_D8), Led(CONTROLLINO_D9), Led(CONTROLLINO_D10)};
Led topLed = {Led(CONTROLLINO_D8, CONTROLLINO_D9, CONTROLLINO_D10)};
Led handRGBLed = {Led(CONTROLLINO_D15, CONTROLLINO_D16, CONTROLLINO_D17)};

Led handLeds[] = {Led(CONTROLLINO_D15, CONTROLLINO_D16, CONTROLLINO_D17), Led(CONTROLLINO_D18), Led(CONTROLLINO_D19), Led(CONTROLLINO_D20), Led(CONTROLLINO_D21), Led(CONTROLLINO_D22), Led(CONTROLLINO_D23)};

Stepper stepperYY = Stepper(CONTROLLINO_D3, CONTROLLINO_D4, CONTROLLINO_D5);
Stepper stepperZZ = Stepper(CONTROLLINO_D0, CONTROLLINO_D1, CONTROLLINO_D2);
LinearActuator linearActuator = LinearActuator(CONTROLLINO_D6, CONTROLLINO_D7);
PushPullMotor pushPullMotor = PushPullMotor(CONTROLLINO_R14, CONTROLLINO_R15);
InductiveSensor sensor = InductiveSensor(CONTROLLINO_A6);
BrakeActuator brakeActuator = BrakeActuator(CONTROLLINO_R13);
Encoder encoder = Encoder(CONTROLLINO_IN0, CONTROLLINO_IN1);

byte handControllerIns[] = {CONTROLLINO_A9, CONTROLLINO_A10, CONTROLLINO_A11, CONTROLLINO_A12};
byte handControllerLeds[] = {CONTROLLINO_D15, CONTROLLINO_D16, CONTROLLINO_D17, CONTROLLINO_D21, CONTROLLINO_D18, CONTROLLINO_D19, CONTROLLINO_D20};
HandController handController = HandController(handControllerIns, handControllerLeds);


RunModule::RunModule() {
}

void RunModule::run() {
   // disableAll();

    // read button direction
    // apply

    handController.updateButtonStates();
    Button *button = handController.getClosedButton();
    if(button != NULL && button->isPressed) {
        button->setLedOn();

        switch (button->getCode()) {
            case BTN_ROTATION_LOCK:
                stepperYY.setEnabled(LOW);
                brakeActuator.setBrake(HIGH);
                break;
            case BTN_LEFT:
                stepperYY.setEnabled(HIGH);
                stepperYY.setDirection(LOW);
                stepperYY.setAppliedPower(1);
                break;
            case BTN_UP:
                stepperYY.setEnabled(LOW);
                stepperZZ.setEnabled(HIGH);
                stepperZZ.setDirection(LOW);
                stepperZZ.setAppliedPower(1);
                break;
            case BTN_TRACK_LOCK:
                stepperYY.setEnabled(LOW);
                pushPullMotor.setEnabled(HIGH);
                pushPullMotor.changePosition();
                break;
            case BTN_GRAB_MOLD: // ???
                stepperYY.setEnabled(LOW);
                break;
            case BTN_RIGHT:
                stepperYY.setEnabled(HIGH);
                stepperYY.setDirection(HIGH);
                stepperYY.setAppliedPower(1);
                break;
            case BTN_DOWN:
                stepperYY.setEnabled(LOW);
                stepperZZ.setEnabled(HIGH);
                stepperZZ.setDirection(HIGH);
                stepperZZ.setAppliedPower(1);
                break;
        }
    } else {
        disableAll();
    }
}


void RunModule::disableAll() {
    brakeActuator.setBrake(LOW);
    stepperYY.setEnabled(LOW);
    stepperZZ.setEnabled(LOW);
    linearActuator.setEnabled(LOW);
    pushPullMotor.setEnabled(LOW);
}

//
//
//void TestsModule::testLinearActuator() {
//
//    delay(2000);
//    linearActuator.setEnabled(HIGH);
//    linearActuator.setDirection(LOW);
//    delay(2000);
//    linearActuator.setEnabled(HIGH);
//    linearActuator.setDirection(HIGH);
//    delay(2000);
//
//    linearActuator.setEnabled(LOW);
//}
//
//void TestsModule::testInductiveSensor() {
//    if(sensor.isClosed()) {
//        leds[2].on();
//        Serial.println("Object Detected");
//    } else {
//        leds[2].off();
//        Serial.println("Object Not Detected");
//    }
//}
//
//
//void TestsModule::testRGBLeds() {
//
//    topLed.onRGB(HIGH, LOW, LOW);
//    //handRGBLed.onRGB(HIGH, LOW, LOW);
//    delay(1000);
//    topLed.onRGB(LOW, HIGH, LOW);
//    //handRGBLed.onRGB(LOW, HIGH, LOW);
//    delay(1000);
//    topLed.onRGB(LOW, LOW, HIGH);
//    //handRGBLed.onRGB(LOW, LOW, HIGH);
//    delay(1000);
//    topLed.onRGB(HIGH, HIGH, LOW);
//    //handRGBLed.onRGB(HIGH, HIGH, LOW);
//    delay(1000);
//    topLed.onRGB(LOW, HIGH, HIGH);
//    //handRGBLed.onRGB(LOW, HIGH, HIGH);
//    delay(1000);
//    topLed.onRGB(HIGH, LOW, HIGH);
//    //handRGBLed.onRGB(HIGH, LOW, HIGH);
//    delay(1000);
//    topLed.onRGB(HIGH, HIGH, HIGH);
//    //handRGBLed.onRGB(HIGH, HIGH, HIGH);
//    delay(1000);
//    topLed.offRGB();
//    //handRGBLed.offRGB();
//    delay(1000);
//}
//
//
//void TestsModule::testHandLeds() {
//
//    handLeds[0].onRGB(HIGH, HIGH, HIGH);
//    delay(1000);
//    handLeds[0].offRGB();
//    for (int i = 1; i < 7; i++) {
//      handLeds[i].on();
//      delay(1000);
//      handLeds[i].off();
//    }
//}
