#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <BlynkSimpleEsp8266.h>
#include <ESP8266WiFi.h>

// OLED setup
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// FSR
const int fsrPin = A0;

// WiFi & Blynk credentials
char auth[] = "YourAuthToken";
char ssid[] = "YourWiFiSSID";
char pass[] = "YourWiFiPassword";

// Game variables
int fsrValue = 0;
int score = 0;
int runs = 0;
int ballsFaced = 0;
float strikeRate = 0.0;

void setup() {
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);

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
  Blynk.run();

  fsrValue = analogRead(fsrPin);

  if (fsrValue > 100) {
    runs = getRuns(fsrValue);
    score += runs;
    ballsFaced++;

    // Calculate strike rate
    strikeRate = (ballsFaced > 0) ? ((float)score / ballsFaced) * 100.0 : 0;

    Serial.print("Run: "); Serial.print(runs);
    Serial.print(" | Score: "); Serial.print(score);
    Serial.print(" | Balls: "); Serial.print(ballsFaced);
    Serial.print(" | SR: "); Serial.println(strikeRate, 2);

    updateOLED(score, ballsFaced, runs, strikeRate);
    updateBlynk(score, ballsFaced, strikeRate);

    delay(1000); // Debounce
  }
}

int getRuns(int value) {
  if (value < 100) return 0;
  else if (value < 300) return 1;
  else if (value < 650) return 2;
  else if (value < 800) return 4;
  else return 6;
}

void updateOLED(int score, int balls, int lastRun, float sr) {
  display.clearDisplay();
  display.setCursor(0, 0);
  display.print("Score: "); display.println(score);
  display.print("Balls: "); display.println(balls);
  display.print("Last Run: "); display.println(lastRun);
  display.print("SR: "); display.println(sr, 1);
  display.display();
}

void updateBlynk(int score, int balls, float sr) {
  Blynk.virtualWrite(V0, score);         // Gauge
  Blynk.virtualWrite(V1, String(balls)); // Label
  Blynk.virtualWrite(V2, sr);            // Graph (auto add point)
}
