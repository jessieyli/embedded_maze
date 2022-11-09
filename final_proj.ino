#include <Servo.h>

// servo objects
Servo myServo1; 
Servo myServo2;

int servo1 = 3; // digital PWM pin servo1
int servo2 = 5; // digital PWM pin servo2
int joyX = 0;
int joyY = 1; // analog pins for joystick

void setup() {
  // attach servos to servo objects
  myServo1.attach(servo1);
  myServo2.attach(servo2);
}

void loop() {
  // put your main code here, to run repeatedly:
  int valX = analogRead(joyX);
  int valY = analogRead(joyY);

  // scale the values to use with the servo
  valX = map(valX, 0, 1023, 10, 170);
  valY = map(valY, 0, 1023, 10, 170);

  // set servo position
  myServo1.write(valX);
  myServo2.write(valY);
  delay(15);
}
