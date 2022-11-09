#include <Servo.h>

// servo objects
Servo myServo1; 
Servo myServo2;

int servo1 = 3; // digital PWM pin servo1
int servo2 = 5; // digital PWM pin servo2
int joyX = 0;
int joyY = 1; // analog pins for joystick
int baseX = 770;
int baseY = 790;
void setup() {
  // attach servos to servo objects
  myServo1.attach(servo1);
  myServo2.attach(servo2);
  while(!Serial);
}

void loop() {
  // put your main code here, to run repeatedly:
  int valX = analogRead(joyX);
  int valY = analogRead(joyY);
  Serial.print("x: ");
  Serial.println(valX);
  Serial.print("y: ");
  Serial.println(valY);

  // scale the values to use with the servo
  if (valX > baseX) {
    valX = map(valX, baseX, 1023, 90, 180);
  } else {
    valX = map(valX, 0, baseX, 0, 90);
  }
   if (valY > baseY) {
    valY = map(valY, baseY, 1023, 90, 180);
  } else {
    valY = map(valY, 0, baseY, 0, 90);
  }
//  Serial.println(valX);
//  Serial.println(valY);

  // set servo position
  myServo1.write(valX);
  myServo2.write(valY);
  delay(200);
}
