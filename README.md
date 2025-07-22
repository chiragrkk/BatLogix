# 🏏 BatLogix

A low-cost, IoT-enabled cricket shot simulator using **ESP8266** and **Force-Sensitive Resistor (FSR)** to detect shot intensity and simulate real match analytics like score, ball count, and strike rate. Ideal for cricket enthusiasts, and IoT learners.

---

## 📦 Features

- ⚡ **Real-Time Shot Detection**  
  Detects shot strength using FSR and maps it to cricket runs (0, 1, 2, 4, or 6).

- 📟 **Live Match Stats on OLED**  
  Displays live score, ball count, and dynamically calculated strike rate on a 0.96" OLED screen.

- 🌐 **Blynk IoT Integration**  
  Sends live game stats to Blynk IoT Cloud. View score (gauge), ball count (label), and strike rate (graph) on your phone.

- 🧠 **Smart Game Logic**  
  Debounce filtering, idle-state detection, and real-time strike rate updates ensure accurate scoring per ball.

---

## 🔧 Hardware Required

- 1 × **ESP8266 NodeMCU**
- 1 × **FSR Sensor**
- 1 × **OLED Display (SSD1306)**
- **Jumper Wires**
- **Breadboard** (optional)

---

## ⚙️ Setup Instructions

1. **Hardware Connections**
   - FSR connected to Analog pin A0 (via voltage divider)
   - OLED connected via I2C (SDA to D2, SCL to D1)
   - Power: 3.3V and GND from ESP8266

2. **Blynk Setup**
   - Create a project in Blynk IoT app
   - Add:
     - **Gauge** widget for Score (V0)
     - **Label** for Ball Count (V1)
     - **Line Chart** for Strike Rate (V2)
   - Link device using Blynk Auth Token

3. **Code & Libraries**
   - Upload code using Arduino IDE
   - Required Libraries:
     - `BlynkSimpleEsp8266.h`
     - `Adafruit_GFX.h`
     - `Adafruit_SSD1306.h`

---

## 🙌 Acknowledgements

- Powered by [Blynk IoT Platform](https://blynk.io)
- Developed using ESP8266, FSR sensor, and a love for cricket 🏏❤️
