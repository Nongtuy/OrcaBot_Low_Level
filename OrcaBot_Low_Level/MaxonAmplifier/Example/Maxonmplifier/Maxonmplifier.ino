#include "MaxonAmplifier.h"

MaxonAmplifier myAmplifier(30, 28, 26, 24, 22, 23);  // Adjust pin numbers as needed

void setup() {
    myAmplifier.begin();
}

void loop() {
    // Your motor control logic here
}
