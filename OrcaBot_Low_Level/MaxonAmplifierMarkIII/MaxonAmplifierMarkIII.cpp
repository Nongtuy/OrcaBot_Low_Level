// Using as Interface between Arduino and Maxon Amplifier.
// 用作 Arduino 和 Maxon Amplifier 之間的介面。
//This Library must be used along with Potentiometer for adjusting speed. 
// 用作 Arduino 和 Maxon Amplifier 之間的介面。
//Suggestion: Potentio taps must be equal to steps of motor
//建議：電位器抽頭必須等於馬達步數
/*This Library is purposely used for OrcaBot SSL Low Level control. 
Contact: Tongthai  Thongsupan. Thai_23@outlook.co.th*/
/*該庫專門用於 OrcaBot SSL 低階控制。
聯絡人：林呂天禮. Thai_23@outlook.co.th*/
#include "MaxonAmplifierMarkIII.h"

MaxonAmplifierMarkIII::MaxonAmplifierMarkIII(int readyPin, int enablePin, int directionPin, int potentiometerPin) {
    _readyPin = readyPin;
    _enablePin = enablePin;
    _directionPin = directionPin;
    _potentiometerPin = potentiometerPin;
}

void MaxonAmplifierMarkIII::begin() {
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

void MaxonAmplifierMarkIII::setSpeed(float speed) {
    int speedValue = abs(speed);
    sendToDigitalPotentiometer(speedValue);  // Set speed via MCP41010

    // Set direction based on the sign of the speed
    if (speed > 0) {
        setDigitalInput(_directionPin, HIGH);  // Clockwise direction
    } else if (speed < 0) {
        setDigitalInput(_directionPin, LOW);   // Counter-clockwise direction
    }
    // If speed is 0, the direction remains unchanged
}

void MaxonAmplifierMarkIII::enable() {
    setDigitalInput(_enablePin, HIGH);
}

void MaxonAmplifierMarkIII::disable() {
    setDigitalInput(_enablePin, LOW);
}

bool MaxonAmplifierMarkIII::checkFault() {
    return digitalRead(_readyPin) == LOW;
}

void MaxonAmplifierMarkIII::resetFault() {
    // Additional Feather thooo
}

void MaxonAmplifierMarkIII::setDigitalInput(int pin, bool value) {
    digitalWrite(pin, value);
}

void MaxonAmplifierMarkIII::sendToDigitalPotentiometer(byte value) {
    // Send the value to the digital potentiometer (MCP41010)
    digitalWrite(_potentiometerPin, LOW);
    SPI.transfer(B00010001);  // Command byte, write to potentiometer
    SPI.transfer(value);       // Potentiometer value
    digitalWrite(_potentiometerPin, HIGH);  // Deselect MCP41010
}

