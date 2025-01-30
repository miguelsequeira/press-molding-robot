# Press Molding Robot Control System Documentation

## Stepper Motor Control System

### Hardware Configuration
The system uses two stepper motors:
1. Y-Axis Stepper (stepperYY)
   - Enable Pin: CONTROLLINO_D3
   - Direction Pin: CONTROLLINO_D4
   - Step Pin: CONTROLLINO_D5
   - Speed: 1000 RPM
   - Steps per Revolution: 400

2. Z-Axis Stepper (stepperZZ)
   - Enable Pin: CONTROLLINO_D0
   - Direction Pin: CONTROLLINO_D1
   - Step Pin: CONTROLLINO_D2
   - Speed: 60 RPM
   - Steps per Revolution: 400

### Control Principles
Each stepper motor is controlled through three main mechanisms:

1. **Enable Control**
   - HIGH: Motor is enabled and can move
   - LOW: Motor is disabled (no power)
   - Used for power management and safety

2. **Direction Control**
   - HIGH: One direction (clockwise)
   - LOW: Opposite direction (counter-clockwise)
   - Changed through setDirection() method

3. **Power/Step Control**
   - Uses Arduino's Stepper library for precise stepping
   - Power level (0 or 1) determines if motor is stepping
   - Speeds are preset:
     * Y-axis: 1000 RPM for fast horizontal movement
     * Z-axis: 60 RPM for controlled vertical movement

## Button Control System

### Button Configuration
The system uses a hand controller with 7 buttons:
- BTN_ROTATION_LOCK (0): Controls rotation brake
- BTN_LEFT (1): Y-axis negative direction
- BTN_UP (2): Z-axis positive direction
- BTN_TRACK_LOCK (3): Controls track locking
- BTN_GRAB_MOLD (4): Controls mold brake
- BTN_RIGHT (5): Y-axis positive direction
- BTN_DOWN (6): Z-axis negative direction

### Operation Principles

1. **Button State Detection**
   - HandController continuously updates button states
   - Each button has an associated LED indicator
   - Button states are read through digital inputs

2. **Motor Control Logic**
   - When a directional button is pressed:
     * Corresponding stepper is enabled
     * Direction is set based on button
     * Power is applied (setAppliedPower(1))
   - When button is released:
     * All motors are disabled through disableAll()

3. **Safety Features**
   - Motors automatically disable when no buttons are pressed
   - Brake actuators provide additional safety
   - Error pins can monitor motor status

4. **LED Feedback**
   - Each button has LED feedback
   - Special LED indicators for brake states
   - RGB LED support for status indication

## Initialization and Startup

1. **Startup Sequence**
   - Both steppers are enabled
   - Push-pull motor is enabled
   - Direction is set to LOW
   - 2-second delay for system stabilization

2. **Default State**
   - All motors disabled
   - Brakes released
   - System ready for manual control

## Integration with Other Components

The stepper control system integrates with:
- Brake actuators for safety locks
- Push-pull motor for track control
- LED system for visual feedback
- Inductive sensors for position detection
- Encoder for position tracking
