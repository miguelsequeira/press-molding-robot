#define ENCODER_OPTIMIZE_INTERRUPTS
#include "TestsModule.h"
#include "Devices.h"


Led ledsTest[] = {Led(CONTROLLINO_D8), Led(CONTROLLINO_D9), Led(CONTROLLINO_D10)};
Led topLedTest = {Led(CONTROLLINO_D8, CONTROLLINO_D9, CONTROLLINO_D10)};
Led handRGBLedTest = {Led(CONTROLLINO_D15, CONTROLLINO_D16, CONTROLLINO_D17)};

Led handLedsTest[] = {Led(CONTROLLINO_D15, CONTROLLINO_D16, CONTROLLINO_D17), Led(CONTROLLINO_D18), Led(CONTROLLINO_D19), Led(CONTROLLINO_D20), Led(CONTROLLINO_D21), Led(CONTROLLINO_D22), Led(CONTROLLINO_D23)};

Stepper stepperYYTest = Stepper(CONTROLLINO_D3, CONTROLLINO_D4, CONTROLLINO_D5);
Stepper stepperZZTest = Stepper(CONTROLLINO_D0, CONTROLLINO_D1, CONTROLLINO_D2);
LinearActuator linearActuatorTest = LinearActuator(CONTROLLINO_D6, CONTROLLINO_D7);
PushPullMotor pushpullMotorTest = PushPullMotor(CONTROLLINO_R14, CONTROLLINO_R15);
InductiveSensor sensorTest = InductiveSensor(CONTROLLINO_A1);
BrakeActuator brakeActuatorTest = BrakeActuator(CONTROLLINO_R12);
Encoder encoderTest = Encoder(CONTROLLINO_IN0, CONTROLLINO_IN1);

byte hCInsTest[] = {CONTROLLINO_A10, CONTROLLINO_A11, CONTROLLINO_A12, CONTROLLINO_A13};
byte hCOutsTest[] = {CONTROLLINO_D13, CONTROLLINO_D14};
byte handControllerLedsTest[] = {CONTROLLINO_D18, CONTROLLINO_D19, CONTROLLINO_D20, CONTROLLINO_D21, CONTROLLINO_D22, CONTROLLINO_D23};
HandController handControllerTest = HandController(hCInsTest, hCOutsTest, handControllerLedsTest);

TestsModule::TestsModule() {
}

void TestsModule::run() {
//
    disableAll();

    //runActuators();
    //runSensors();
}


void TestsModule::runActuators() {
//    testStepperYY();
//    testStepperZZ();
//    testLinearActuator();
//    testPushPullMotor();
//    testBrakeActuator();

    testRGBLeds();
    testHandLeds();
}


void TestsModule::runSensors() {
//    testInductiveSensor();
//    testEncoder();
    testHandController();
    //testHandControllerObj();

}

void TestsModule::disableAll() {
    brakeActuatorTest.setBrake(HIGH);
    stepperYYTest.setEnabled(LOW);
    stepperZZTest.setEnabled(LOW);
    linearActuatorTest.setEnabled(LOW);
    pushpullMotorTest.setEnabled(LOW);
}


void TestsModule::testHandController() {
    byte button = handControllerTest.getClosedButton();
     Serial.print("Button Pressed = ");
     Serial.print(button);
     Serial.println();
}


void TestsModule::testHandControllerObj() {
    Button* button = handControllerTest.getClosedButtonObj();
    if(false) {
        Serial.print("Button Pressed = ");
        Serial.print(button->getCode());
        Serial.println();
    } else {
        Serial.print("Button NOT Pressed");
    }
}

void TestsModule::testEncoder() {
    long positionLeft  = -999;
    long positionRight = -999;

   long newLeft, newRight;
   newLeft = encoderTest.read();
   if (newLeft != positionLeft ) {
     Serial.print("Encoder position = ");
     Serial.print(newLeft);
     Serial.println();
     positionLeft = newLeft;
   }
   // if a character is sent from the serial monitor,
   // reset both back to zero.
   if (Serial.available()) {
     Serial.read();
     Serial.println("Reset encoder back to zero");
     encoderTest.write(0);
   }
}

void TestsModule::testBrakeActuator() {
    brakeActuatorTest.setBrake(HIGH);
    delay(2000);
    brakeActuatorTest.setBrake(LOW);
    delay(2000);
}

void TestsModule::testPushPullMotor() {
    pushpullMotorTest.setEnabled(HIGH);
    pushpullMotorTest.setDirection(LOW);
    delay(2000);
    pushpullMotorTest.setDirection(HIGH);
    delay(2000);
    pushpullMotorTest.setEnabled(LOW);
    delay(2000);
}

void TestsModule::testStepperYY() {

    stepperYYTest.setEnabled(HIGH);
    stepperYYTest.setDirection(LOW);
    stepperYYTest.setAppliedPower(1);
    delay(2000);
    stepperYYTest.setAppliedPower(5);
    stepperYYTest.setDirection(HIGH);
    delay(2000);
    stepperYYTest.setAppliedPower(0);
    stepperYYTest.setEnabled(LOW);
}


void TestsModule::testStepperZZ() {

    stepperZZTest.setEnabled(HIGH);
    stepperZZTest.setDirection(LOW);
    stepperZZTest.setAppliedPower(1);
    delay(2000);
    stepperZZTest.setAppliedPower(50);
    stepperZZTest.setDirection(HIGH);
    delay(2000);
    stepperZZTest.setAppliedPower(0);
    stepperZZTest.setEnabled(LOW);
}

void TestsModule::testLinearActuator() {

    delay(2000);
    linearActuatorTest.setEnabled(HIGH);
    linearActuatorTest.setDirection(LOW);
    delay(2000);
    linearActuatorTest.setEnabled(HIGH);
    linearActuatorTest.setDirection(HIGH);
    delay(2000);

    linearActuatorTest.setEnabled(LOW);
}
//
//void TestsModule::testEncoder() {
//    Encoder encoder = Encoder(CONTROLLINO_D0);
//
//    int a = encoder.getRelativePosition();
//    int b = encoder.getConstantSpeed();
//    int c = encoder.getDirection();
//    encoder.setDegreeFactor(1);
//    encoder.setMultiplyFactor(2);
//}

void TestsModule::testInductiveSensor() {
    if(sensorTest.isClosed()) {
        ledsTest[2].on();
        Serial.println("Object Detected");
    } else {
        ledsTest[2].off();
        Serial.println("Object Not Detected");
    }
}


void TestsModule::testRGBLeds() {

    topLedTest.onRGB(HIGH, LOW, LOW);
    handRGBLedTest.onRGB(HIGH, LOW, LOW);
    delay(1000);
    topLedTest.onRGB(LOW, HIGH, LOW);
    handRGBLedTest.onRGB(LOW, HIGH, LOW);
    delay(1000);
    topLedTest.onRGB(LOW, LOW, HIGH);
    handRGBLedTest.onRGB(LOW, LOW, HIGH);
    delay(1000);
    topLedTest.onRGB(HIGH, HIGH, LOW);
    handRGBLedTest.onRGB(HIGH, HIGH, LOW);
    delay(1000);
    topLedTest.onRGB(LOW, HIGH, HIGH);
    handRGBLedTest.onRGB(LOW, HIGH, HIGH);
    delay(1000);
    topLedTest.onRGB(HIGH, LOW, HIGH);
    handRGBLedTest.onRGB(HIGH, LOW, HIGH);
    delay(1000);
    topLedTest.onRGB(HIGH, HIGH, HIGH);
    handRGBLedTest.onRGB(HIGH, HIGH, HIGH);
    delay(1000);
    topLedTest.offRGB();
    handRGBLedTest.offRGB();
    delay(1000);
}


void TestsModule::testHandLeds() {

    handLedsTest[0].onRGB(HIGH, HIGH, HIGH);
    delay(1000);
    handLedsTest[0].offRGB();
    for (int i = 1; i < 7; i++) {
      handLedsTest[i].on();
      delay(1000);
      handLedsTest[i].off();
    }
}
