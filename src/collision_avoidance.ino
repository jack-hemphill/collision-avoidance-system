#include <Servo.h>
#include <Stepper.h>
#include <HCSR04.h>

// ---------------- Pins ----------------
#define LED_RED   8
#define LED_GREEN 9
#define BUZZ      10
#define TRIG      11
#define ECHO      12
#define SERVO_PIN 7

// ---------------- Constants ----------------
const float THRESHOLD_CM = 5.0;
const int stepsPerRevolution = 2048;
const int STEPS_PER_LOOP = 10;

// Create ultrasonic object (trigger, echo)
UltraSonicDistanceSensor sr04(TRIG, ECHO);

// Stepper config (28BYJ-48 + ULN2003)
Stepper myStepper(stepsPerRevolution, 6, 5, 4, 3);

Servo myservo;

void setup() {
  Serial.begin(9600);

  pinMode(LED_RED, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(BUZZ, OUTPUT);

  myStepper.setSpeed(10);

  myservo.attach(SERVO_PIN);
  myservo.write(0);

  noTone(BUZZ);
}

void loop() {
  float distanceCm = sr04.measureDistanceCm();

  // Handle invalid readings (sometimes sensors return 0 or negative)
  if (distanceCm <= 0) {
    Serial.println("Invalid distance reading");
    delay(100);
    return;
  }

  Serial.print("Distance: ");
  Serial.print(distanceCm);
  Serial.println(" cm");

  if (distanceCm > THRESHOLD_CM) {
    // SAFE / FAR
    digitalWrite(LED_GREEN, HIGH);
    digitalWrite(LED_RED, LOW);

    noTone(BUZZ);
    myservo.write(0);

    myStepper.step(STEPS_PER_LOOP);
  } else {
    // WARNING / CLOSE
    digitalWrite(LED_RED, HIGH);
    digitalWrite(LED_GREEN, LOW);

    tone(BUZZ, 1000);
    myservo.write(180);

    myStepper.step(-STEPS_PER_LOOP);
  }

  delay(100); // stabilize behavior + prevents spamming actuators
}
