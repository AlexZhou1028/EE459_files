// Include the stepper motor library
#include <Stepper.h>

// Define the number of steps per revolution
const int stepsPerRevolution = 200;  // for 1.8-degree stepper motor

// Initialize the stepper motor object
Stepper myStepper(stepsPerRevolution, 8, 9, 10, 11);  // IN1, IN2, IN3, IN4 connected to Arduino pins 8, 9, 10, 11

void setup() {
  // Set the speed of the motor (rpm)
  myStepper.setSpeed(60);  // Set speed to 60 RPM
}

void loop() {
  // Step one revolution in one direction
  myStepper.step(stepsPerRevolution);
  delay(1000);  // Delay before next movement
}
