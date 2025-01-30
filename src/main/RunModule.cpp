#define ENCODER_OPTIMIZE_INTERRUPTS
#include <Controllino.h>
#include <Encoder.h>
#include "RunModule.h"
#include "Led.h"
#include "State.h"
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

#define ZZ_SPEED    60
#define YY_SPEED    32000

Led leds[] = {Led(CONTROLLINO_D8), Led(CONTROLLINO_D9), Led(CONTROLLINO_D10)};
Led topLed = {Led(CONTROLLINO_D8, CONTROLLINO_D9, CONTROLLINO_D10)};
Led handRGBLed = {Led(CONTROLLINO_D21, CONTROLLINO_D22, CONTROLLINO_D23)};

Led handLeds[] = {Led(CONTROLLINO_D15, CONTROLLINO_D16, CONTROLLINO_D17), Led(CONTROLLINO_D18), Led(CONTROLLINO_D19), Led(CONTROLLINO_D20), Led(CONTROLLINO_D21), Led(CONTROLLINO_D22), Led(CONTROLLINO_D23)};

Stepper stepperYY = Stepper(CONTROLLINO_D3, CONTROLLINO_D4, CONTROLLINO_D5);
Stepper stepperZZ = Stepper(CONTROLLINO_D0, CONTROLLINO_D1, CONTROLLINO_D2);
LinearActuator linearActuator = LinearActuator(CONTROLLINO_D6, CONTROLLINO_D7);
PushPullMotor pushPullMotor = PushPullMotor(CONTROLLINO_R14, CONTROLLINO_R15);
InductiveSensor sensorLeft = InductiveSensor(CONTROLLINO_A1);
InductiveSensor sensorRight = InductiveSensor(CONTROLLINO_A2);
InductiveSensor sensorUp = InductiveSensor(CONTROLLINO_A4);
InductiveSensor sensorDown= InductiveSensor(CONTROLLINO_A3);
InductiveSensor sensorMold = InductiveSensor(CONTROLLINO_A6);
BrakeActuator brakeMoldActuator = BrakeActuator(CONTROLLINO_R13);
BrakeActuator brakeRotationActuator = BrakeActuator(CONTROLLINO_R11);
Encoder encoder = Encoder(CONTROLLINO_IN0, CONTROLLINO_IN1);

byte handControllerIns[] = {CONTROLLINO_A9, CONTROLLINO_A10, CONTROLLINO_A11, CONTROLLINO_A12};
byte handControllerLeds[] = {CONTROLLINO_D15, CONTROLLINO_D16, CONTROLLINO_D17, CONTROLLINO_D21, CONTROLLINO_D18, CONTROLLINO_D19, CONTROLLINO_D20};
HandController handController = HandController(handControllerIns, handControllerLeds);


RunModule::RunModule() {
}

byte currBtn = 0;
byte prevBtn = 0;
Button *button;

void RunModule::run() {

    // read button direction
    // apply

    handController.updateButtonStates();

    if(handController.getNumberOfClosedButtons() <= 1) {
        button = handController.getClosedButton();
    }

    if(button != NULL && button->isPressed) {
          button->setLedOn();

        currBtn = button->getCode();

        switch (currBtn) {
            case BTN_ROTATION_LOCK:
                brakeRotationActuator.setBrake(HIGH);
                break;
            case BTN_LEFT:
                if(!sensorLeft.isClosed()) {
                    stepperYY.setEnabled(HIGH);
                    stepperYY.setDirection(HIGH);
                    stepperYY.setSpeed(YY_SPEED);
                }
                break;
            case BTN_UP:
                if(!sensorUp.isClosed()) {
                    stepperZZ.setEnabled(HIGH);
                    stepperZZ.setDirection(HIGH);
                    stepperZZ.setSpeed(ZZ_SPEED);
                }
                break;
            case BTN_TRACK_LOCK:
                if(currBtn != prevBtn) {
                    topLed.onRGB(HIGH, LOW, HIGH);
                    handRGBLed.onRGB(HIGH, HIGH, LOW);
                    pushPullMotor.setEnabled(HIGH);
                    pushPullMotor.changePosition();
                }
                break;
            case BTN_GRAB_MOLD:
                if(currBtn != prevBtn) {
                    brakeMoldActuator.changeBrakeState();
                }
                break;
            case BTN_RIGHT:
                if(!sensorRight.isClosed()) {
                    stepperYY.setEnabled(HIGH);
                    stepperYY.setDirection(LOW);
                    stepperYY.setSpeed(YY_SPEED);
                }
                break;
            case BTN_DOWN:
                if(!sensorDown.isClosed()) {
                    stepperZZ.setEnabled(HIGH);
                    stepperZZ.setDirection(LOW);
                    stepperZZ.setSpeed(ZZ_SPEED);
                }
                break;
            default:
                disableAll();
        }
    }

    else {
        disableAll();
    }

    if(!brakeMoldActuator.isBraked()) {
        handController.setButtonLedOn(BTN_GRAB_MOLD);
    }

    if(pushPullMotor.getDirection() == HIGH) {
        topLed.onRGB(LOW, HIGH, LOW);
        handRGBLed.onRGB(LOW, HIGH,LOW);
    } else {
        topLed.onRGB(HIGH, LOW, LOW );
        handRGBLed.onRGB(HIGH, LOW, LOW);
    }

    prevBtn = currBtn;
}


void RunModule::disableAll() {
    brakeRotationActuator.setBrake(LOW);
    stepperYY.setSpeed(0);
    stepperZZ.setSpeed(0);
    linearActuator.setEnabled(LOW);
    pushPullMotor.setEnabled(LOW);
}

void RunModule::startup() {
    stepperYY.setEnabled(HIGH);
    stepperZZ.setEnabled(HIGH);
    pushPullMotor.setEnabled(HIGH);
    pushPullMotor.setDirection(LOW);
    delay(2000);
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
