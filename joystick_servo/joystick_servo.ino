#include <Servo.h>

// servo objects
Servo myServo1; 
Servo myServo2;

int servo1 = 3; // digital PWM pin servo1
int servo2 = 5; // digital PWM pin servo2
int joyX = A0;
int joyY = A1; // analog pins for joystick
int baseX = 820;
int baseY = 840;
float tolerance = 0.01;

int lightSensor = A2;

void setup() {

  // attach servos to servo objects
  myServo1.attach(servo1);
  myServo2.attach(servo2);
  Serial.begin(9600);
  while(!Serial);
   Serial1.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int valX = analogRead(joyX);
  int valY = analogRead(joyY);
  Serial.print("x: ");
  Serial.println(valX);
  Serial.print("y: ");
  Serial.println(valY);

  // light sensor reading
  int lightSensorReading = analogRead(lightSensor);
  Serial.println(lightSensorReading);

  // scale the values to use with the servo
  if (valX > baseX) {
    valX = map(valX, baseX, 1023, 90, 105); // 15 degree restriction
  } else {
    valX = map(valX, 0, baseX, 75, 90);
  }
   if (valY > baseY) {
    valY = map(valY, baseY, 1023, 90, 105);
  } else {
    valY = map(valY, 0, baseY, 75, 90);
  }
//  Serial.println(valX);
//  Serial.println(valY);

  // set servo position
  myServo1.write(valX);
  myServo2.write(valY);

  // use these lines to set servo positions at beginning
//  myServo1.write(90);
//  myServo2.write(90);

  // trigger light message
  if (lightSensorReading < 200) {
    Serial1.write("woohoo! congrats");
  }
  delay(200);
}
