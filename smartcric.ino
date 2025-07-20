#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

const int fsrPin = A0;
int fsrValue = 0;
int score = 0;
int runs = 0;
int ballsFaced = 0;

void setup() {
  Serial.begin(9600);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("OLED failed!");
    while (true);
  }
  
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("Cricket Bat Sim");
  display.display();
  delay(1000);
}

void loop() {
  fsrValue = analogRead(fsrPin);
  
  if (fsrValue > 100) { // lowest hit threshold
    runs = getRuns(fsrValue);
    score += runs;
    ballsFaced++;
    
    Serial.print("Run: ");
    Serial.print(runs);
    Serial.print(" | Score: ");
    Serial.print(score);
    Serial.print(" | Balls: ");
    Serial.println(ballsFaced);

    updateDisplay(score, ballsFaced, runs);
    
    delay(1000); // debounce
  }
}

int getRuns(int value) {
  if (value < 100) return 0;
  else if (value < 300) return 1;   // ↓ tweaked
  else if (value < 650) return 2;   // ↓ tweaked
  else if (value < 800) return 4;
  else return 6;
}

void updateDisplay(int score, int balls, int lastRun) {
  display.clearDisplay();
  display.setCursor(0, 0);
  display.print("Score: ");
  display.println(score);

  display.print("Balls: ");
  display.println(balls);

  display.print("Last Run: ");
  display.println(lastRun);

  display.display();
}
