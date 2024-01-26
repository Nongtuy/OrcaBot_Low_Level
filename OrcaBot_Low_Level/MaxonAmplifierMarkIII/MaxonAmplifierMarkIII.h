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

#ifndef MaxonAmplifierMarkIII_h
#define MaxonAmplifierMarkIII_h

#include "Arduino.h"
#include <SPI.h> 
// Library SPI included for using with pottentiometer
// 包含與電位計一起使用的函式庫 SPI
class MaxonAmplifierMarkIII {
public:
    MaxonAmplifierMarkIII(int readyPin, int enablePin, int directionPin, int potentiometerPin);

    void begin();  // Initialize the library

    // Motor control functions
    void setSpeed(float speed);  // Set the motor speed
    void enable();  // Enable the power stage
    void disable(); // Disable the power stage
    void setDirection(const bool clockwise);

    // Fault handling
    bool checkFault();  // Check for faults
    void resetFault();  // Reset faults (implement if needed)

private:
    // Internal methods
    void setDigitalInput(const int pin, const bool value);
    void sendToDigitalPotentiometer(const byte value);

    // Member variables
    int _readyPin;
    int _enablePin;
    int _directionPin;
    int _potentiometerPin;
};

#endif

