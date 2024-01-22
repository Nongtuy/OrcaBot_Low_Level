#include <MaxonAmplifier.h>

// Instantiate MaxonAmplifier object with pin numbers
MaxonAmplifier myAmplifier(30, 28, 26, 24, 22, 23, 23);  // D23 connected to MCP41010

void setup() {
    Serial.begin(9600);
  
    // Initialize the MaxonAmplifier library
    myAmplifier.begin();

    // Enable the power stage
    myAmplifier.enable();
}

void loop() {
    // Set the motor speed to 50% (adjust as needed)
    myAmplifier.setSpeed(50);

    // Check for faults
    if (myAmplifier.checkFault()) {
        Serial.println("Fault detected! Motor stopped.");
        // You might want to implement fault handling here
    }

    delay(1000);  // Adjust delay as needed
}