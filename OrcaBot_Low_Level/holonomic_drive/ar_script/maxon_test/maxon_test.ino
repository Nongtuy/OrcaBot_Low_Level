#include "Maxon.h"

// Pin configuration for the Maxon motor
const int in1Pin = 2;
const int in2Pin = 3;
const int dirPin = 4;
const int enPin = 5;
const int spdPin = 6;
const int rdyPin = 7;
const int ledPin = 8;

// Create an instance of the Maxon class
Maxon maxonMotor;

void setup() {
  // Initialize the Maxon motor
  maxonMotor.begin(in1Pin, in2Pin, dirPin, enPin, spdPin, rdyPin, ledPin);

  // Enable the motor
  maxonMotor.enable();

  // Set the LED direction (1 for source, 0 for sink)
  maxonMotor.setLEDDir(LED_SOURCE);

  // Set the speed mode (SPEED_MODE_MED for 8-pole configuration)
  maxonMotor.setMode(SPEED_MODE_MED);
}

void loop() {
  // Drive the motor at a specific speed (adjust as needed)
  maxonMotor.setMotor(50); // Speed value between 0 and 100

  // Add any additional logic or tasks as needed
  // ...

  delay(1000); // Delay for 1 second for demonstration purposes

  // Disable the motor (stop it)
  maxonMotor.disable();

  delay(10);
}
