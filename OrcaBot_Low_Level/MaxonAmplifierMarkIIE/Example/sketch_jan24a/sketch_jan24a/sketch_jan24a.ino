#include <MaxonAmplifierMarkIIE.h>

// Instantiate MaxonAmplifierMarkIIDirect  with pin numbers
MaxonAmplifierMarkIIE bobo(30, 24, 22, 23);  // 

void setup() {
    Serial.begin(115200);

    // Initialize the MaxonAmplifierMarkIIDirect library
    bobo.begin();
    bobo.enable();
}

void loop() {
    Serial.println("Starting loop...");

    // Gradually accelerate the motor speed to 100%
    for (int speed = 0; speed <= 100; speed += 1) {
        bobo.setDirection(false);  
        bobo.setSpeed(speed);
        delay(50);  // Adjust the delay as needed for acceleration steps
        Serial.println(speed);  // Send speed value to Serial
    }

    // Decelerate the motor speed back to 0%
    for (int speed = 100; speed >= -255; speed -= 1) {
        bobo.setSpeed(speed);
        delay(50);  // Adjust the delay as needed for deceleration steps
        Serial.println(speed);  // Send speed value to Serial
        if (speed >= 0) {
            bobo.setDirection(true);
            delay(50);
            }
        if (speed ==0 ) {
          bobo.disable();
          delay(50);
          }    
        
    }

    Serial.println("End of loop...");
    delay(4);  // Delay before the next iteration
}
