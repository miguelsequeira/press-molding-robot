#include "HandController.h"

/**
 * Button Detection Logic:
 * - A9 pin reads:
 *   * Button 0 (Rotation): 12V DC when pressed
 *   * Button 6 (Z Down): 24V DC when pressed
 * - A10 pin reads:
 *   * Button 1 (Y Forward): 12V DC when pressed
 *   * Button 5 (Y Back): 24V DC when pressed
 * - A11 pin reads:
 *   * Button 2 (Z Up): 12V DC when pressed
 *   * Button 4 (Pick Mold): 24V DC when pressed
 * - A12 pin reads:
 *   * Button 3 (Start/Stop): 24V DC when pressed
 */

#define BTN0_NOT_PRESSED    100
#define BTN1_EMERGENCY      101
#define BTN2_BLOCK_TRACK    102
#define BTN3_GRAB_MOLD      103
#define BTN4_ROTATE         104
#define BTN5_FORWARD        105
#define BTN6_BACKWARD       106
#define BTN7_UP             107
#define BTN8_DOWN           108

// LED Pins
#define LED_ROTATION CONTROLLINO_D15
#define LED_Y_FWD CONTROLLINO_D16
#define LED_Z_UP CONTROLLINO_D17
#define LED_START_R CONTROLLINO_D21
#define LED_START_G CONTROLLINO_D22
#define LED_START_B CONTROLLINO_D23
#define LED_PICK CONTROLLINO_D18
#define LED_Y_BACK CONTROLLINO_D19
#define LED_Z_DOWN CONTROLLINO_D20


// Pin Definitions
#define PIN_A9 CONTROLLINO_A9     // Rotation (B1) and Down (B7)
#define PIN_A10 CONTROLLINO_A10   // Y Forward (B2) and Back (B6)
#define PIN_A11 CONTROLLINO_A11   // Z Up (B3) and Pick Mold (B5)
#define PIN_A12 CONTROLLINO_A12   // Start/Stop (B4)


// Constants
#define SIGNAL_CHECK_TIME 100     // 100ms to check signal
#define LED_CYCLE_TIME 200        // 200ms per RGB LED
#define SAMPLE_INTERVAL 1         // 1ms between samples
#define ADC_THRESHOLD_24V 800     // Threshold for 24V detection (>20V)
#define ADC_THRESHOLD_12V_MIN 300 // Threshold for 12V detection (>10V)
#define ADC_THRESHOLD_12V_MAX 600 // Maximum threshold for 12V detection (<15V)
#define ADC_THRESHOLD_LOW 200     // Threshold for LOW state (<5V)
#define SAMPLES_FOR_PRESS 100     // Number of samples to confirm button press

unsigned long rgbCycleStart = 0;
uint8_t currentRgbLed = 0;


int buttonsCodes[] = {BTN1_EMERGENCY, BTN2_BLOCK_TRACK, BTN3_GRAB_MOLD, BTN4_ROTATE, BTN5_FORWARD, BTN6_BACKWARD, BTN7_UP, BTN8_DOWN};

HandController::HandController(byte pinIn[], byte pinLed[]) {
    this->pinIn = pinIn;
    this->pinLed = pinLed;

    // Initialize analog input pins
    pinMode(PIN_A9, INPUT);
    pinMode(PIN_A10, INPUT);
    pinMode(PIN_A11, INPUT);
    pinMode(PIN_A12, INPUT);

    // Initialize LED pins
    pinMode(LED_ROTATION, OUTPUT);
    pinMode(LED_Y_FWD, OUTPUT);
    pinMode(LED_Z_UP, OUTPUT);
    pinMode(LED_START_R, OUTPUT);
    pinMode(LED_START_G, OUTPUT);
    pinMode(LED_START_B, OUTPUT);
    pinMode(LED_PICK, OUTPUT);
    pinMode(LED_Y_BACK, OUTPUT);
    pinMode(LED_Z_DOWN, OUTPUT);

    pinMode(CONTROLLINO_D14, OUTPUT);
    digitalWrite(CONTROLLINO_D14, HIGH);

    Button but[8];

    for(int i=0; i<3; i++) {
        but[i] = Button(i, pinIn[i], pinLed[i]);
        but[6-i] = Button((6-i), pinIn[i], pinLed[6-i]);
    }
    but[3] = Button(buttonsCodes[3], pinIn[3], pinLed[3]);

    // Initialize button states
    for (int i = 0; i < 7; i++) {

        but[i].isPressed = false;
        but[i].ledState = false;
        but[i].lastButtonState = false;
        but[i].signalCount = 0;
        but[i].sampleCount = 0;
        but[i].lastToggleTime = 0;
    }
    this->buttons = but;
}

Button* HandController::getClosedButtonObj() {
    int counter = 0;
//    int counterButtonsPressed = 0;
    //updateButtonStates();
    //updateLEDs();
    //Button *buttonSelected;
    for(int i=0; i<8; i++) {

            if(buttons[i].isPressed) {
                //Serial.println( buttons[i].position);
                return &buttons[i];
            } else {
                buttons[i].setLedOff();

            }
            //Serial.println( buttons[i]->isClosed());

        }
    return &buttons[0];


//    if(counterButtonsPressed > 1 || counterButtonsPressed == 0) {

  //  }

    return &buttons[0];
}




int HandController::getClosedButton() {

    int threshold = 358;
    int counter = 0;
    int counterButtonsPressed = 0;
    int buttonSelected = 0;

    // emergency button (priority)
    Serial.print(analogRead(pinIn[0]));
    Serial.println();
    if(analogRead(pinIn[0]) > threshold) {
        return BTN1_EMERGENCY;
    }

    for(int i=0; i<4; i++) {
        for(int j=0; j<2; j++) {
            if(analogRead(pinIn[i]) > threshold) {
                buttonSelected = buttonsCodes[counter];
                counterButtonsPressed++;
            }
            counter++;
        }
    }

    if(counterButtonsPressed > 1 || counterButtonsPressed == 0) {
        return BTN0_NOT_PRESSED;
    }

    return buttonSelected;
}


void HandController::checkPinA9Buttons() {

    int pinValue = analogRead(PIN_A9);

    // Button 1 - Rotation (12V)
    if (pinValue >= ADC_THRESHOLD_12V_MIN && pinValue <= ADC_THRESHOLD_12V_MAX) {
        buttons[0].signalCount++;
    }

    // Button 7 - Z Down (24V)
    if (pinValue >= ADC_THRESHOLD_24V) {
        buttons[6].signalCount++;
    }

    buttons[0].sampleCount++;
    buttons[6].sampleCount++;

    if (buttons[0].sampleCount >= SAMPLES_FOR_PRESS) {
        buttons[0].isPressed = (buttons[0].signalCount >= 1);
        buttons[0].signalCount = 0;
        buttons[0].sampleCount = 0;
    }

    if (buttons[6].sampleCount >= SAMPLES_FOR_PRESS) {
        buttons[6].isPressed = (buttons[6].signalCount >= 1);
        buttons[6].signalCount = 0;
        buttons[6].sampleCount = 0;
    }
}

void HandController::checkPinA10Buttons() {

    int pinValue = analogRead(PIN_A10);

    // Button 2 - Y Forward (12V)
    if (pinValue >= ADC_THRESHOLD_12V_MIN && pinValue <= ADC_THRESHOLD_12V_MAX) {
        buttons[1].signalCount++;
    }

    // Button 6 - Y Back (24V)
    if (pinValue >= ADC_THRESHOLD_24V) {
        buttons[5].signalCount++;
    }

    buttons[1].sampleCount++;
    buttons[5].sampleCount++;

    if (buttons[1].sampleCount >= SAMPLES_FOR_PRESS) {
        buttons[1].isPressed = (buttons[1].signalCount >= 1);
        buttons[1].signalCount = 0;
        buttons[1].sampleCount = 0;
    }

    if (buttons[5].sampleCount >= SAMPLES_FOR_PRESS) {
        buttons[5].isPressed = (buttons[5].signalCount >= 1);
        buttons[5].signalCount = 0;
        buttons[5].sampleCount = 0;
    }
}

void HandController::checkPinA11Buttons() {

    int pinValue = analogRead(PIN_A11);

    // Button 3 - Z Up (12V)
    if (pinValue >= ADC_THRESHOLD_12V_MIN && pinValue <= ADC_THRESHOLD_12V_MAX) {
        buttons[2].signalCount++;
    }

    // Button 5 - Pick Mold (24V)
    if (pinValue >= ADC_THRESHOLD_24V) {
        buttons[4].signalCount++;
    }

    buttons[2].sampleCount++;
    buttons[4].sampleCount++;

    if (buttons[2].sampleCount >= SAMPLES_FOR_PRESS) {
        buttons[2].isPressed = (buttons[2].signalCount >= 1);
        buttons[2].signalCount = 0;
        buttons[2].sampleCount = 0;
    }

    if (buttons[4].sampleCount >= SAMPLES_FOR_PRESS) {
        buttons[4].isPressed = (buttons[4].signalCount >= 1);
        buttons[4].signalCount = 0;
        buttons[4].sampleCount = 0;
    }
}

void HandController::checkPinA12Buttons() {

    int pinValue = analogRead(PIN_A12);

    // Button 4 - Start/Stop (24V)
    if (pinValue >= ADC_THRESHOLD_24V) {
        buttons[3].signalCount++;
    }

    buttons[3].sampleCount++;

    if (buttons[3].sampleCount >= SAMPLES_FOR_PRESS) {
        buttons[3].isPressed = (buttons[3].signalCount >= 1);
        buttons[3].signalCount = 0;
        buttons[3].sampleCount = 0;
    }
}

void HandController::updateButtonStates() {

    checkPinA9Buttons();
    checkPinA10Buttons();
    checkPinA11Buttons();
    checkPinA12Buttons();
}

void HandController::updateLEDs() {

    // Update individual LEDs based on button states
    digitalWrite(LED_ROTATION, buttons[0].isPressed);
    digitalWrite(LED_Y_FWD, buttons[1].isPressed);
    digitalWrite(LED_Z_UP, buttons[2].isPressed);
    digitalWrite(LED_PICK, buttons[4].isPressed);
    digitalWrite(LED_Y_BACK, buttons[5].isPressed);
    digitalWrite(LED_Z_DOWN, buttons[6].isPressed);

    // Update RGB LED for Start/Stop button
    if (buttons[3].isPressed) {
        unsigned long currentTime = millis();
        if (currentTime - rgbCycleStart >= LED_CYCLE_TIME) {
            rgbCycleStart = currentTime;
            currentRgbLed = (currentRgbLed + 1) % 3;
        }

        digitalWrite(LED_START_R, currentRgbLed == 0);
        digitalWrite(LED_START_G, currentRgbLed == 1);
        digitalWrite(LED_START_B, currentRgbLed == 2);
    } else {
        digitalWrite(LED_START_R, LOW);
        digitalWrite(LED_START_G, LOW);
        digitalWrite(LED_START_B, LOW);
    }
}