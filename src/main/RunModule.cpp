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
#define LED_CYCLE_TIME 1000        // 200ms per RGB LED

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

Button onOffButton = Button(7, CONTROLLINO_I17);


RunModule::RunModule() {

}

int currBtn = 0;
int prevBtn = 0;
Button *button;
bool isMoldBraked = false;
bool isBlinking = false;
unsigned long previousTime = 0;
unsigned long currentTime = 0;
int ledBlinkState = LOW;


void RunModule::run() {
////
//  	onOffButton.updateState();
//
//    if(onOffButton.isClosed() ) {
//    	// In service
//    	digitalWrite(CONTROLLINO_R0, machineOn); // Security Contactor
//    	digitalWrite(CONTROLLINO_R1, machineOn); // L
////        turnAllOn();
//    }
//
//    if(!onOffButton.isClosed() ) {
//        machineOn = LOW;
//
//    	// In service
//    	digitalWrite(CONTROLLINO_R0, machineOn); // Security Contactor
//    	digitalWrite(CONTROLLINO_R1, machineOn); // L
////        turnAllOff();
//        return;
//    }
//
//    if(machineOn == LOW) {
////      turnAllOff();
//      return;
//    }

    // read button direction
    // apply

    handController.updateButtonStates();
    button = handController.getClosedButton();


    if(button != NULL && button->isPressed) {
        button->setLedOn();

        currBtn = button->getCode();
        if(currBtn != prevBtn) {
          disableAll();
        }

        switch (currBtn) {
            case BTN_ROTATION_LOCK:
                brakeRotationActuator.setBrake(HIGH);
                topLed.onRGB(HIGH, HIGH, HIGH);
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

    if(pushPullMotor.getDirection() == HIGH && !sensorMold.isClosed()) {
        topLed.onRGB(LOW, HIGH, LOW);
        handRGBLed.onRGB(LOW, HIGH,LOW);
    }

    if(pushPullMotor.getDirection() == LOW && !sensorMold.isClosed()) {
   		topLed.onRGB(HIGH, LOW, LOW );
        handRGBLed.onRGB(HIGH, LOW, LOW);
    }

    if(sensorMold.isClosed()) {
		currentTime = millis();
		if(currentTime - previousTime >= LED_CYCLE_TIME) {
			previousTime = currentTime;
			if (ledBlinkState == LOW) {
                ledBlinkState = HIGH;
      			topLed.onRGB(HIGH, HIGH, LOW);
				handRGBLed.onRGB(HIGH, HIGH, HIGH);
			} else {
                ledBlinkState = LOW;
      			topLed.offRGB();
      			handRGBLed.offRGB();
			}
        }

    } else {
      isBlinking = false;
    }

    prevBtn = currBtn;
}


void RunModule::disableAll() {
    brakeRotationActuator.setBrake(LOW);
    stepperYY.setEnabled(HIGH);
    stepperZZ.setEnabled(HIGH);
    stepperYY.setSpeed(0);
    stepperZZ.setSpeed(0);
    pushPullMotor.setEnabled(LOW);
}

void RunModule::startup() {
//  	onOffButton.init();
    topLed.onRGB(HIGH, LOW, HIGH);
    handRGBLed.onRGB(HIGH, HIGH, LOW);
    stepperYY.setEnabled(HIGH);
    stepperZZ.setEnabled(HIGH);
    pushPullMotor.setEnabled(HIGH);
    pushPullMotor.setDirection(LOW);
    brakeRotationActuator.setBrake(LOW);
    delay(2000);
}


void RunModule::turnAllOff() {
    stepperYY.setEnabled(LOW);
    stepperZZ.setEnabled(LOW);
//	isMoldBraked = brakeMoldActuator.isBraked();
//    brakeMoldActuator.setBrake(LOW);
	disableAll();
    for(int i=0;i<7;i++) {
      handController.setButtonLedOff(i);
    }
    topLed.offRGB();
    handRGBLed.offRGB();
}

void RunModule::turnAllOn() {
    stepperYY.setEnabled(HIGH);
    stepperZZ.setEnabled(HIGH);
//	if(isMoldBraked) {
//    	brakeMoldActuator.setBrake(HIGH);
//    }
}