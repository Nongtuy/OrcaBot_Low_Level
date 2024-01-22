#include <MaxonAmplifier.h>

// Instantiate MaxonAmplifier object with pin numbers
MaxonAmplifier myAmplifier(30, 28, 26, 24, 22, 23, 23);  // D23 connected to MCP41010

void setup() {
    Serial.begin(115200);
  
    // Initialize the MaxonAmplifier library
    myAmplifier.begin();

    // Enable the power stage
    myAmplifier.enable();
}

void loop() {
    Serial.println("Starting loop...");

    // Rotate CW (clockwise) for 2 seconds
    Serial.println("Rotating CW");
    myAmplifier.setDirection(true);  // Set direction to clockwise
    myAmplifier.setSpeed(50);  // Set the motor speed to 50% (adjust as needed)
    delay(2000);

    // Stop the motor
    Serial.println("Stopping");
    myAmplifier.setSpeed(0);  // Set speed to 0 for stopping
    delay(2500);

    // Rotate CCW (counterclockwise) for 2 seconds
    Serial.println("Rotating CCW");
    myAmplifier.setDirection(false);  // Set direction to counterclockwise
    myAmplifier.setSpeed(50);  // Set the motor speed to 50% (adjust as needed)
    delay(2000);

    // Stop the motor
    Serial.println("Stopping");
    myAmplifier.setSpeed(0);  // Set speed to 0 for stopping
    delay(2500);

    Serial.println("End of loop...");
    delay(2000);  // Delay before the next iteration
}
