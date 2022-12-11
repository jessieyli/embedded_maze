#include <Servo.h>
#include "maze.h"

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
int joySw = 1;
// variables
int valX, valY, lightReading;
state CURRENT_STATE = (state) 1;
int countdown = 3;
int saved_clock;

void changeState() {
  CURRENT_STATE = (state) 1;
  countdown = 3;
}

void initialize_vars() {
  CURRENT_STATE = (state) 1;
  countdown = 3;
  saved_clock = millis();
}
void setup() {
  // attach servos to servo objects
  myServo1.attach(servo1);
  myServo2.attach(servo2);
  pinMode(joySw, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(joySw), changeState, FALLING);
  Serial.begin(9600);
  while (!Serial);
  Serial1.begin(9600);

  initialize_vars();

}

void loop() {
  // put your main code here, to run repeatedly:
  update_inputs();
  CURRENT_STATE = update_fsm(CURRENT_STATE, millis());
  delay(100);
}

void update_inputs() {
  valX = analogRead(joyX);
  valY = analogRead(joyY);
  lightReading = analogRead(lightSensor);
}

state update_fsm(state cur_state, long mils) {
  state next_state;
  switch (cur_state) {
    case sDISP_COUNTDOWN:
      if ((mils - saved_clock) >= 500 and countdown >= 0) {
        Serial1.write(countdown);
        countdown -= 1;
        saved_clock = mils;
        next_state = sDISP_COUNTDOWN;
      } else if ((mils - saved_clock) >= 500 and countdown < 0) {
        Serial1.write(4);
        saved_clock = mils;
        next_state = sIN_GAME;
      } else {
        next_state = sDISP_COUNTDOWN;
      }
      break;
    case sIN_GAME:
      if (lightReading < 200) {
        Serial1.write(5);
        next_state = sGAME_OVER;
      } else {
        Serial1.write(4);
//        valX = analogRead(joyX);
//        valY = analogRead(joyY);
        Serial.print("x: ");
        Serial.println(valX);
        Serial.print("y: ");
        Serial.println(valY);

        // light sensor reading
//        lightReading = analogRead(lightSensor);
        Serial.print("light: ");
        Serial.println(lightReading);

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

        // set servo position
        myServo1.write(valX);
        myServo2.write(valY);

        next_state = sIN_GAME;
      }
      break;
    case sGAME_OVER:
      Serial1.write(5);
      next_state = sGAME_OVER;
      break;
  }
  return next_state;
}
