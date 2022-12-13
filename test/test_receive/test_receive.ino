byte b = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial1.begin(9600);
}

void loop() {
  test_receive_msgs();
}

boolean test_receive_msgs() {
  if (Serial1.available() > 0) {
    b = Serial1.read();
    Serial.println(b);
    if (b != 42) {
      Serial.println("test failed");
      return false;
    }
  }
  delay(500);
  return true;
}
