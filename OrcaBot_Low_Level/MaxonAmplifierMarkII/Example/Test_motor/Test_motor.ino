#include <MaxonAmplifierMarkII.h>

// Instantiate MaxonAmplifierMarkII object with pin numbers
MaxonAmplifierMarkII myAmplifier(30, 28, 26, 24, 22, 23);  // Replace with your actual pin numbers

void setup() {
    Serial.begin(115200);
  
    // Initialize the MaxonAmplifierMarkII library
    myAmplifier.begin();
}

void loop() {
    Serial.println("Starting loop...");

    // Gradually accelerate the motor speed to 100%
    for (int speed = 0; speed <= 100; speed += 10) {
        myAmplifier.setSpeed(speed);
        delay(1000);  // Adjust the delay as needed for acceleration steps
    }

    // Decelerate the motor speed back to 0%
    for (int speed = 100; speed >= 0; speed -= 10) {
        myAmplifier.setSpeed(speed);
        delay(1000);  // Adjust the delay as needed for deceleration steps
    }

    Serial.println("End of loop...");
    delay(2000);  // Delay before the next iteration
}
