int joyX = A0;
int joyY = A1; // analog pins for joystick
int baseX = 820;
int baseY = 840;

void setup() {
  Serial.begin(9600);
  while (!Serial);

  //  test manually
  for (int i = 0; i < 1024; i++) {
    for (int j = 0; j < 1024; j++) {
      if (!testInputAndServo(i, j)) {
        Serial.println("test failed");
      }
    }
  }
}

void loop() {
  //  test with joystick inputs
  //  int valX = analogRead(joyX);
  //  int valY = analogRead(joyY);
  //  if (!testInputAndServo(valX, valY)) {
  //    Serial.println("test failed");
  //  }
}

bool testInputAndServo(int valX, int valY) {
  if (valX < 0 || valX > 1023 || valY < 0 || valY > 1023) {
    return false;
  }
  int servoX;
  if (valX > baseX) {
    servoX = map(valX, baseX, 1023, 90, 105); // 15 degree restriction
  } else {
    servoX = map(valX, 0, baseX, 75, 90);
  }
  int servoY;
  if (valY > baseY) {
    servoY = map(valY, baseY, 1023, 90, 105);
  } else {
    servoY = map(valY, 0, baseY, 75, 90);
  }
  if (servoX < 75 || servoX > 105 || servoY < 75 || servoY > 105) {
    return false;
  }
  return true;
}
