// Example sketch

#include "MaxonAmplifierMarkIII.h"

// Instantiate MaxonAmplifierMarkIIE with pin numbers
MaxonAmplifierMarkIII bobo(30, 24, 22, 23);

void setup() {
    Serial.begin(115200);
    bobo.begin();
    bobo.enable();
}

void loop() {
    // Gradually accelerate the motor speed to maximum
    for (int speed = -255; speed <= 255; speed += 1) {
        bobo.setSpeed(255);
        delay(10);  // Adjust the delay as needed for acceleration steps
        Serial.println(speed);  // Send speed value to Serial
        delay(10);
        
    }

    // Decelerate the motor speed back to 0
    for (int speed = 255; speed >= -255; speed -= 1) {
        bobo.setSpeed(speed);
        delay(10);  // Adjust the delay as needed for deceleration steps
        Serial.println(speed);  // Send speed value to Serial
    }

    Serial.println("End of loop...");
    delay(10);  // Delay before the next iteration
}
