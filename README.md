# Smart-Irrigation-System

An IoT-based automated smart irrigation system utilizing ESP32 to monitor soil moisture levels. This project implements precision watering to optimize water usage and includes a mechanical-based regenerative braking concept for power management.

## Hardware Components
- ESP32 / ESP8266 (NodeMCU)
- Soil Moisture Sensor
- DHT22 Sensor
- PIR Sensor
- Battery & Mini 360 Buck Converter
- Relay Module & Water Pump
- Push Switch, Buzzer, and LCD Display

## Wiring Guide
- **Relay (Pump Control):** IN → D6, VCC → 3.3V, GND → GND
- **LCD I2C:** SDA → D2, SCL → D1
- **Sensors:**
  - DHT11/22 → D4
  - PIR Sensor → D5
  - Push Button → D7

## Libraries Required
To compile this project in Arduino IDE, you will need the following libraries:
- **Core:** `ESP8266WiFi`, `ESP8266WebServer`
- **Sensors:** `DHT sensor library` (by Adafruit), `Adafruit Unified Sensor`
- **Display:** `Adafruit SSD1306`, `Adafruit GFX`
- **IoT:** `Blynk` or `Adafruit MQTT` (depending on your chosen dashboard)

## Project Goals
- Automate irrigation based on real-time soil moisture data.
- Integrate mechanical regenerative braking for sustainable energy harvesting.
- Provide remote monitoring via IoT dashboard.
- 
