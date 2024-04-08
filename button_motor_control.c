#include <Stepper.h>

#define STEPS_PER_REVOLUTION 4096

// Define motor control pins
#define motorPin1  8     // IN1 on the ULN2003 driver
#define motorPin2  10    // IN2 on the ULN2003 driver
#define motorPin3  9     // IN3 on the ULN2003 driver
#define motorPin4  7     // IN4 on the ULN2003 driver

// Define button pins
const int buttonPinClosed = 1;  // Fully Closed Button connected to PD1 (Arduino Digital Pin 1)(Yellow)
const int buttonPinHalf = 2;    // Half-Closed Button connected to PD2 (Arduino Digital Pin 2)(White)
const int buttonPinOpen = 3    // Fully Open Button connected to PD3 (Arduino Digital Pin 3)(Red)
const int buttonPinAuto = 4;    // Light Auto Button connected to PD4 (Arduino Digital Pin 4)(Blue)
//const int buttonPinAuto = 5;    // Heat Auto Button connected to PD5 (Arduino Digital Pin 5)(Black)  need to add this in somewhere, im not sure where right now

// Define photoresistor pin
const int pResistor = A0;       // Photoresistor connected to PC0 (Arduino Analog Pin A0)
int value;                      // Store value from photoresistor (0-1023)
int position = FULLY_CLOSED;    // Current position of the blinds, starts fully closed

// Initialize the stepper library on the specified pins
Stepper myStepper(STEPS_PER_REVOLUTION, motorPin1, motorPin2, motorPin3, motorPin4);

void setup() {
  // Set motor pins as outputs
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(motorPin3, OUTPUT);
  pinMode(motorPin4, OUTPUT);

  // Set button pins as inputs with internal pull-up resistors enabled
  pinMode(buttonPinClosed, INPUT_PULLUP);
  pinMode(buttonPinHalf, INPUT_PULLUP);
  pinMode(buttonPinOpen, INPUT_PULLUP);
  pinMode(buttonPinAuto, INPUT_PULLUP);

  // Set the photoresistor pin as an input
  pinMode(pResistor, INPUT);

  // Set up the stepper motor's speed and steps
  myStepper.setSpeed(10); // Set a low speed for the stepper motor
}



void loop() {
  // Button state checking with debouncing
  if (debounce(buttonPinClosed)) {
    closeBlinds();
  } else if (debounce(buttonPinHalf)) {
    halfOpenBlinds();
  } else if (debounce(buttonPinOpen)) {
    openBlinds();
  } else if (debounce(buttonPinAuto)) {
    autoControlBlinds();
  }

  // Add any additional repetitive code here, if necessary.
}

bool debounce(int pin) {
  if (digitalRead(pin) == LOW) {
    delay(50); // Short delay to debounce
    if (digitalRead(pin) == LOW) {
      while (digitalRead(pin) == LOW); // Wait for button release
      return true;
    }
  }
  return false;
}

void closeBlinds() {
  if (position != FULLY_CLOSED) {
    myStepper.step(FULLY_CLOSED - position); // Move to fully closed position
    position = FULLY_CLOSED;
  }
}

void halfOpenBlinds() {
  if (position != HALF_OPEN) {
    myStepper.step(HALF_OPEN - position); // Move to half-open position
    position = HALF_OPEN;
  }
}

void openBlinds() {
  if (position != FULLY_OPEN) {
    myStepper.step(FULLY_OPEN - position); // Move to fully open position
    position = FULLY_OPEN;
  }
}

void autoControlBlinds() {
  value = analogRead(pResistor);
  if (value > 400 && position != FULLY_CLOSED) {
    closeBlinds();
  } else if (value >= 300 && value <= 400 && position != HALF_OPEN) {
    halfOpenBlinds();
  } else if (value < 300 && position != FULLY_OPEN) {
    openBlinds();
  }
}
