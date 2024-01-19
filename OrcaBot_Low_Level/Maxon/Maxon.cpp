// MaxonMotor.cpp
#include "Maxon_Drive.h"

Maxon_Drive::Maxon_Drive(int motorPin1, int motorPin2, int directionPin, int enablePin, int digIN1Pin, int digIN2Pin){
    _motorPin1 = motorPin1;
    _motorPin2 = motorPin2;
    _directionPin = directionPin;
    _enablePin = enablePin;
    _digIN1Pin = digIN1Pin;
    _digIN2Pin = digIN2Pin;

    pinMode(_motorPinSpeed, OUTPUT);
    pinMode(_directionPin, OUTPUT);
    pinMode(_enablePin, OUTPUT);
    pinMode(_digIN1Pin, INPUT);
    pinMode(_digIN2Pin, INPUT);

    setSpeed(DEFAULT_SPEED); // Set default speed
    setDirection(DEFAULT_DIRECTION); // Set default direction
    enableMotor(); // Enable the motor during initialization
    setCurrentLimit(DEFAULT_CURRENT_LIMIT); // Set current limit

void Maxon_Drive::setSpeed(int speed) {
        // Implement the code to set the speed using PWM
    analogWrite(_motorPinSpeed, abs(speed)); // Set the speed using PWM

    // Set the direction based on the sign of the speed
    if (1024<= speed >= 0) {
        // Clockwise (CW) direction
        digitalWrite(_directionPin, HIGH);
    } 
    else if (-1024 <= speed <= 0){
        // Counterclockwise (CCW) direction
        digitalWrite(_directionPin, LOW);
    }
}
void Maxon_Drive::setCurrentLimit(int limit) {
    // Implement the code to set the current limit
    // You might need additional pins for this
}

/*void Maxon_Drive::setDirection(int direction) {
    // Implement the code to set the direction
    digitalWrite(_directionPin, direction);
}*/

void Maxon_Drive::enableMotor() {
    // Implement the code to enable the motor
    digitalWrite(_enablePin, HIGH);
}

void Maxon_Drive::disableMotor() {
    // Implement the code to disable the motor
    digitalWrite(_enablePin, LOW);
}

bool MaxonMotorControl5::isReady() {
    // Implement the code to check the ready status
    return digitalRead(_digIN1Pin);
}

bool MaxonMotorControl5::readDigIN1() {
    // Implement the code to read DigIN1
    return digitalRead(_digIN1Pin);
}

bool MaxonMotorControl5::readDigIN2() {
    // Implement the code to read DigIN2
    return digitalRead(_digIN2Pin);
}