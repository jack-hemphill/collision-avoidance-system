# Collision Avoidance System (Arduino / Embedded C++)

An Arduino-based collision avoidance system using an HC-SR04 ultrasonic sensor to detect obstacles and trigger real-time responses using LEDs, a buzzer, a servo motor, and a stepper motor.

## Features
- Real-time distance measurement (cm)
- Threshold-based behavior (safe vs. close)
- LED indicators (green = safe, red = close)
- Buzzer warning alert
- Servo + stepper motor control
- Serial output for debugging

## Hardware
- Arduino (Uno/Nano)
- HC-SR04 Ultrasonic Sensor (TRIG/ECHO)
- Servo motor
- 28BYJ-48 Stepper + ULN2003 driver
- LEDs + resistors
- Buzzer

## How it works
- If distance > threshold: green LED ON, buzzer OFF, servo to 0°, stepper rotates forward
- If distance ≤ threshold: red LED ON, buzzer ON, servo to 180°, stepper rotates backward

## Demo
[Add your demo video here (upload or link).](https://youtu.be/U0klazo9PWw)

## Future Improvements
- Add 3 distance zones (safe / warning / danger)
- Smooth sensor noise with a moving average filter
- Make threshold adjustable (button or potentiometer)
