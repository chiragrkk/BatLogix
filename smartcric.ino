const int fsrPin = A0;
int threshold = 300; // calibrate this value after testing

void setup() {
  Serial.begin(9600);
}

void loop() {
  int fsrValue = analogRead(fsrPin);
  if (fsrValue > threshold) {
    Serial.println("Hit detected!");
    delay(300); // avoid multiple detections
  }
}
