byte b = 0;
void setup() {
   Serial.begin(9600);  // Initialize serial monitor
  while (!Serial);     // Wait for serial monitor to start (need this for USB serial)
  Serial1.begin(9600); 
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial1.available() > 0) {
    b = Serial1.read();
    Serial.println((char) b);
  }
}
