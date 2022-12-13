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

int lightSensor = A2;
int joySw = 1;

// variables
int valX, valY, lightReading;
state CURRENT_STATE;
int countdown;
int saved_clock;

// interrupt handler that resets the game
void changeState() {
  initialize_vars();
}

// resets the game, setting the state back to the initial state, 
// resetting state variables, and moving the servo back to its neutral position
void initialize_vars() {
  CURRENT_STATE = (state) 1;
  countdown = 3;
  saved_clock = millis();
  myServo1.write(90);
  myServo2.write(90);
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
//  test_all_tests();
}

void loop() {
  update_inputs();
  Serial.println(CURRENT_STATE);
  CURRENT_STATE = update_fsm(CURRENT_STATE, millis());
  delay(100);
}

// updates the state variables using joystick values and light sensor reading
// also prints these values to the Serial
void update_inputs() {
  valX = analogRead(joyX);
  valY = analogRead(joyY);
  lightReading = analogRead(lightSensor);
  Serial.print("x: ");
  Serial.println(valX);
  Serial.print("y: ");
  Serial.println(valY);

  // light sensor reading
  Serial.print("light: ");
  Serial.println(lightReading);
}


// this function takes in two joystick values (x and y positions) and 
// maps it to values that are then used to set the servo position 
// (here, we restrict the bounds to 75-105 degrees as opposed to 0-180) 
void update_servo(int valX, int valY) {
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
}

// update the fsm using the current state and the current timestamp
state update_fsm(state cur_state, long mils) {
  state next_state;
  switch (cur_state) {
    case sDISP_COUNTDOWN:
      if ((mils - saved_clock) >= 500 and countdown >= 0) { // transition 1-1
        Serial1.write(countdown);
        countdown -= 1;
        saved_clock = mils;
        next_state = sDISP_COUNTDOWN;
      } else if ((mils - saved_clock) >= 500 and countdown < 0) { // transition 1-2
        Serial1.write(4);
        saved_clock = mils;
        next_state = sIN_GAME;
      } else { // transition 1-1
        next_state = sDISP_COUNTDOWN;
      }
      break;
    case sIN_GAME:
      if (lightReading < 210) { // transition 2-3
        Serial1.write(5);
        next_state = sGAME_OVER;
      } else { // transition 2-2
        Serial1.write(4);
        update_servo(valX, valY);
        next_state = sIN_GAME;
      }
      break;
    case sGAME_OVER:
      Serial1.write(5);
      next_state = sGAME_OVER; // transition 3-3
      break;
    default:
      Serial1.write(5);
      next_state = sGAME_OVER;
      break;
  }
  return next_state;
}
