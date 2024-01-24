// MaxonAmplifierMarkIIDirect.cpp

#include "MaxonAmplifierMarkIIE.h"

MaxonAmplifierMarkIIE::MaxonAmplifierMarkIIE(int readyPin, int enablePin, int directionPin, int potentiometerPin) {
    _readyPin = readyPin;
    _enablePin = enablePin;
    _directionPin = directionPin;
    _potentiometerPin = potentiometerPin;
}

void MaxonAmplifierMarkIIE::begin() {
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

void MaxonAmplifierMarkIIE::setSpeed(float speed) {
    int speedValue = map(speed, 0, 255, 0, 255);
    //int speedValue = constrain(speed, 0, 255);
    sendToDigitalPotentiometer(speed);  // Set speed via MCP41010
}

void MaxonAmplifierMarkIIE::enable() {
    setDigitalInput(_enablePin, HIGH);
}

void MaxonAmplifierMarkIIE::disable() {
    setDigitalInput(_enablePin, LOW);
}

void MaxonAmplifierMarkIIE::setDirection(bool clockwise) {
    setDigitalInput(_directionPin, clockwise);
}

bool MaxonAmplifierMarkIIE::checkFault() {
    return digitalRead(_readyPin) == LOW;
}

void MaxonAmplifierMarkIIE::resetFault() {
    // Implement fault reset if needed
}

void MaxonAmplifierMarkIIE::setDigitalInput(int pin, bool value) {
    digitalWrite(pin, value);
}

/*void MaxonAmplifierMarkIIE::sendToDigitalPotentiometer(byte value) {
    // Send the value to the digital potentiometer (MCP41010)
    digitalWrite(_potentiometerPin, LOW);
    SPI.transfer(B00010001);  // Command byte, write to potentiometer
    SPI.transfer(value);       // Potentiometer value
    digitalWrite(_potentiometerPin, HIGH);  // Deselect MCP41010
}*/
void MaxonAmplifierMarkIIE::sendToDigitalPotentiometer(byte value) {
    // Send the value to the digital potentiometer (MCP41010)
    digitalWrite(_potentiometerPin, LOW);
    SPI.beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE0));  // 
    SPI.transfer(B00010001);  // Command byte, write to potentiometer
    if (SPI.transfer(value) != value) {
        // Handle SPI communication error
        Serial.println("Error communicating with MCP41010");
    }
    SPI.endTransaction();
    digitalWrite(_potentiometerPin, HIGH);  // Deselect MCP41010
}

