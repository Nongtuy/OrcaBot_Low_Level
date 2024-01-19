#include "Maxon_Drive.h"

// Define the motor pins
const int motorPin1 = 3;     // Replace with your actual pin numbers
const int motorPin2 = 5;
const int directionPin = 7;
const int enablePin = 9;
const int digIN1Pin = 11;
const int digIN2Pin = 13;

// Create an instance of Maxon_Drive
Maxon_Drive myMotor(motorPin1, motorPin2, directionPin, enablePin, digIN1Pin, digIN2Pin);

void setup() {
    // Set up serial communication
    Serial.begin(9600);

    // Initialize motor settings
    myMotor.setSpeed(0);      // Set initial speed to 0
    myMotor.enableMotor();    // Enable the motor
}

void loop() {
    // Read user input from Serial Monitor
    if (Serial.available() > 0) {
        int speed = Serial.parseInt(); // Read the integer value from Serial Monitor

        // Set the speed and direction based on user input
        myMotor.setSpeed(speed);

        // Print the current speed and direction to Serial Monitor
        Serial.print("Speed: ");
        Serial.print(speed);
        Serial.print(" Direction: ");
        Serial.println((speed >= 0) ? "Clockwise" : "Counterclockwise");
    }

    // Your additional code here
}
