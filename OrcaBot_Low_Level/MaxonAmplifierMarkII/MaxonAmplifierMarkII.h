// MaxonAmplifierMarkIIDirect.h

#ifndef MaxonAmplifierMarkIIDirect_h
#define MaxonAmplifierMarkIIDirect_h

#include "Arduino.h"
#include <SPI.h>

class MaxonAmplifierMarkII {
public:
    MaxonAmplifierMarkII(int readyPin, int enablePin, int directionPin, int potentiometerPin);

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
    int _enablePin;
    int _directionPin;
    int _potentiometerPin;
};

#endif
