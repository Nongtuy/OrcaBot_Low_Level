/*Library_For_Maxon_Amplifier Mark II [Usable]
23:47 22/01/24 OrcaBot_Low_Level*/

#include "MaxonAmplifier.h"

MaxonAmplifier::MaxonAmplifier(int readyPin, int digIn1Pin, int digIn2Pin, int enablePin, int directionPin, int setValSpeedPin, int potentiometerPin) {
    _readyPin = readyPin;
    _digIn1Pin = digIn1Pin;
    _digIn2Pin = digIn2Pin;
    _enablePin = enablePin;
    _directionPin = directionPin;
    _setValSpeedPin = setValSpeedPin;
    _potentiometerPin = potentiometerPin;
}

void MaxonAmplifier::begin() {
    SPI.begin();
    SPI.setBitOrder(MSBFIRST);
    SPI.setDataMode(SPI_MODE0);
    SPI.setClockDivider(SPI_CLOCK_DIV8);

    pinMode(_readyPin, INPUT);
    pinMode(_digIn1Pin, OUTPUT);
    pinMode(_digIn2Pin, OUTPUT);
    pinMode(_enablePin, OUTPUT);
    pinMode(_directionPin, OUTPUT);
    pinMode(_setValSpeedPin, OUTPUT);

    digitalWrite(_setValSpeedPin, HIGH);  // Deselect MCP41010
}

void MaxonAmplifier::setSpeed(float speed) {
    int speedValue = map(speed, 0, 100, 0, 255);
    sendToDigitalPotentiometer(speedValue);  // Set speed via MCP41010
}

void MaxonAmplifier::enable() {
    setDigitalInput(_enablePin, HIGH);
}

void MaxonAmplifier::disable() {
    setDigitalInput(_enablePin, LOW);
}

void MaxonAmplifier::setDirection(bool clockwise) {
    setDigitalInput(_directionPin, clockwise);
}

bool MaxonAmplifier::checkFault() {
    return digitalRead(_readyPin) == LOW;
}

void MaxonAmplifier::resetFault() {
    // Implement fault reset if needed
}

void MaxonAmplifier::setDigitalInput(int pin, bool value) {
    digitalWrite(pin, value);
}

void MaxonAmplifier::sendToDigitalPotentiometer(byte value) {
    // Send the value to the digital potentiometer (MCP41010)
    digitalWrite(_setValSpeedPin, LOW);
    SPI.transfer(B00010001);  // Command byte, write to potentiometer
    SPI.transfer(value);       // Potentiometer value
    digitalWrite(_setValSpeedPin, HIGH);  // Deselect MCP41010
}

