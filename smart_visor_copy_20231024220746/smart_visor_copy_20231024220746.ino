#include <Servo.h>
#include <NewPing.h>

const int TRIG_PIN = 6;
const int ECHO_PIN = 7;
const int SERVO_PIN1 = 9;
const int SERVO_PIN2 = 5;
const int DISTANCE_THRESHOLD = 55;
const int MAX_DISTANCE = 200; // Maximum distance to measure in centimeters

Servo servo1;  // First servo motor
Servo servo2;  // Second servo motor
NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE);

void setup() {
  Serial.begin(9600);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  servo1.attach(SERVO_PIN1);
  servo2.attach(SERVO_PIN2);
  servo1.write(0);
  servo2.write(0);
}

void loop() {
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  unsigned int duration_us = sonar.ping(); // Get the ping time in microseconds
  float distance_cm = sonar.convert_cm(duration_us); // Convert ping time to distance in centimeters

  if (distance_cm < DISTANCE_THRESHOLD) {
    servo1.write(90); // Open position for servo1 (clockwise)
    servo2.write(90); // Open position for servo2 (counterclockwise)
  } else {
    servo1.write(0);  // Closed position for servo1 (counterclockwise)
    servo2.write(180); // Closed position for servo2 (clockwise)
  }

  Serial.print("Distance: ");
  Serial.print(distance_cm);
  Serial.println(" cm");

 delay(500);
}
