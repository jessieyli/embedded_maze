int lightSensor = A0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int lightSensorReading = analogRead(lightSensor);
  Serial.println(lightSensorReading);
  delay(100);
  
  if(lightSensorReading < 50){            
    Serial.print("It is dark.");
  } else {
    Serial.print("It is light.");
  }
}
