#include "MaxonAmp.h"

MaxonMotor myMotor(/* Assign your pin numbers here */);

void setup() {
    myMotor.begin();
    // Perform other setup tasks
}

void loop() {
    myMotor.setSpeed(100); // Set speed to 100 (replace with wanted speed)
    // Perform other tasks
}
