#include <AccelStepper.h>

#define Stepper1StepPin 27
#define Stepper1DirPin 26

AccelStepper stepper(AccelStepper::DRIVER, Stepper1StepPin, Stepper1DirPin);

void setup() {
  pinMode(25, OUTPUT);
  Serial.begin(115200); // Initialize serial communication
  while (!Serial)
  {
    digitalWrite(25, HIGH);
    delay(200);
    digitalWrite(25, LOW);
    
  }
  stepper.setMaxSpeed(6000);
  stepper.setAcceleration(8000);
  Serial.println("Started");
}

void loop() {
  if (Serial.available() > 0) { // Check if data is available to read
    int distance = Serial.parseInt(); // Read the distance value from serial
    Serial.println(distance);
    Serial.flush();
    // Move the stepper by the specified distance in millimeters
    long steps = distance * 200; // Calculate steps based on the distance in millimeters
    stepper.move(steps);
  }
  stepper.run(); // Run the stepper motor
}