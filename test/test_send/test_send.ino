
void setup() {
  Serial1.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  test_bad_msgs();
}

void test_bad_msgs() {
  Serial1.write(42);
  delay(500);
}
