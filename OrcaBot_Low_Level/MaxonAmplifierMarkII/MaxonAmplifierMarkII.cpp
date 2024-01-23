// MaxonAmplifierMarkIIDirect.cpp

#include "MaxonAmplifierMarkII.h"

MaxonAmplifierMarkII::MaxonAmplifierMarkII(int readyPin, int enablePin, int directionPin, int potentiometerPin) {
    _readyPin = readyPin;
    _enablePin = enablePin;
    _directionPin = directionPin;
    _potentiometerPin = potentiometerPin;
}

void MaxonAmplifierMarkII::begin() {
    SPI.begin();
    SPI.setBitOrder(MSBFIRST);
    SPI.setDataMode(SPI_MODE0);
    SPI.setClockDivider(SPI_CLOCK_DIV8);

    pinMode(_readyPin, INPUT);
    pinMode(_enablePin, OUTPUT);
    pinMode(_directionPin, OUTPUT);
    pinMode(_potentiometerPin, OUTPUT);

    digitalWrite(_potentiometerPin, HIGH);  // Deselect MCP41010
}

void MaxonAmplifierMarkII::setSpeed(float speed) {
    int speedValue = map(speed, 0, 100, 0, 255);
    sendToDigitalPotentiometer(speedValue);  // Set speed via MCP41010
}

void MaxonAmplifierMarkII::enable() {
    setDigitalInput(_enablePin, HIGH);
}

void MaxonAmplifierMarkII::disable() {
    setDigitalInput(_enablePin, LOW);
}

void MaxonAmplifierMarkII::setDirection(bool clockwise) {
    setDigitalInput(_directionPin, clockwise);
}

bool MaxonAmplifierMarkII::checkFault() {
    return digitalRead(_readyPin) == LOW;
}

void MaxonAmplifierMarkII::resetFault() {
    // Implement fault reset if needed
}

void MaxonAmplifierMarkII::setDigitalInput(int pin, bool value) {
    digitalWrite(pin, value);
}

void MaxonAmplifierMarkII::sendToDigitalPotentiometer(byte value) {
    // Send the value to the digital potentiometer (MCP41010)
    digitalWrite(_potentiometerPin, LOW);
    SPI.transfer(B00010001);  // Command byte, write to potentiometer
    SPI.transfer(value);       // Potentiometer value
    digitalWrite(_potentiometerPin, HIGH);  // Deselect MCP41010
}
