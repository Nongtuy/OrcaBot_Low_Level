// 21:17:02 18/01/24 MaxonMotor.h
//Maxon Library Proto 1 OrcaBot_Specifically with DEC 24/2 1-Q-EC amplifier
/*maxon motor control 5maxon motor
Operating Instructions 1-Q-EC Amplifier DEC Module 24/2
April 2015 Edition / document number 1002422_PDF_E - 04 / subject to change
3 Pin assignment DEC Module 24/2
Top view
3.1 Pin assignment
Pin Signal Description Pin Signal Description
1 W1 Motor winding 1
2 W2 Motor winding 2 --------------17 Set value speed Set value speed input
3 W3 Motor winding 3 --------------16 Set current limit Set current limit input
4 +Vcc Supply voltage 8...24 VDC --15 Gnd Ground
5 Gnd Ground ----------------------14 Direction Direction input
6 Vcc Hall +5 VDC output voltage --13 Enable Enable input
7 H1 Hall sensor 1 ----------------12 DigIN2 Digital input 2
8 H2 Hall sensor 2 ----------------11 DigIN1 Digital input 1
9 H3 Hall sensor 3 ----------------10 Ready Status indication output*/ 
#ifndef MAXONDRIVER_H
#define MAXONDRIVER_H

#include <Arduino.h>

class Maxon_Drive {
public:
    Maxon_Drive(int motorPin1, int motorPin2, int directionPin, int enablePin, int digIN1Pin, int digIN2Pin);

    void setSpeed(int speed);
    void setCurrentLimit(int limit);
    void setDirection(int direction);
    void enableMotor();
    void disable();
    bool isReady();
    bool readDigIN1();
    bool readDigIN2();

private:
    int _motorPin1;
    int _motorPin2;
    int _directionPin;
    int _enablePin;
    int _digIN1Pin;
    int _digIN2Pin;
    

};

#endif
