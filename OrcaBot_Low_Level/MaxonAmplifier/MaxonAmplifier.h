// MaxonAmplifier.h

#ifndef MaxonAmplifier_h
#define MaxonAmplifier_h

#include "Arduino.h"
#include <SPI.h>

class MaxonAmplifier {
public:
    MaxonAmplifier(int readyPin, int digIn1Pin, int digIn2Pin, int enablePin, int directionPin, int setValSpeedPin, int potentiometerPin);

    void begin();  // Initialize the library

    // Motor control functions
    void setSpeed(float speed);  // Set the motor speed
    void enable();  // Enable the power stage
    void disable(); // Disable the power stage
    void setDirection(bool clockwise);  // Set the motor direction

    // Fault handling
    bool checkFault();  // Check for faults
    void resetFault();  // Reset faults (implement if needed)

private:
    // Internal methods
    void setDigitalInput(int pin, bool value);
    void sendToDigitalPotentiometer(byte value);

    // Member variables
    int _readyPin;
    int _digIn1Pin;
    int _digIn2Pin;
    int _enablePin;
    int _directionPin;
    int _setValSpeedPin;
    int _potentiometerPin;
};

#endif