const int fsrPin = A0;
int fsrValue = 0;
int score = 0;
int runs = 0;

void setup() {
  Serial.begin(9600);
}

void loop() {
  fsrValue = analogRead(fsrPin);
  
  if (fsrValue > 150) { // base threshold for contact
    runs = getRuns(fsrValue);
    score += runs;
    Serial.print("Hit Detected! Runs: ");
    Serial.println(runs);
    Serial.print("Total Score: ");
    Serial.println(score);

    delay(1000); // debounce time (so same hit isn’t counted multiple times)
  }
}

int getRuns(int value) {
  if (value < 150) return 0;
  else if (value < 400) return 1;
  else if (value < 650) return 2;
  else if (value < 800) return 4;
  else return 6;
}
