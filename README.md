# Smart-Irrigation-System
An IoT-based automated smart irrigation system utilizing ESP32 to monitor soil moisture levels via sensors. This project implements precision watering to optimize water usage and includes a mechanical-based regenerative braking concept for power management. Built for sustainable agricultural efficiency.
Hardware Compononts: 
1.Esp32/esp82669 (any other compatible device)
2.soil moisture sensor
3.dht 22 sensor
4.Pir sensor
5.Battery
6.Buck converter
7.Relay module
8.Water Pump
9.Push Switch
10.Display
11.Jumper
12.Buzzer etc
                +-------------------+
                |   ESP8266 NodeMCU |
                +-------------------+
                       |   |   |   |
                       |   |   |   |
         A0 <----------+   |   |   +----------> D0 (Buzzer)
                       |   |   |
                       |   |   +----------> D4 (DHT11)
                       |   |
                       |   +----------> D5 (PIR Sensor)
                       |
                       +----------> D6 (Relay → Pump)
                       +----------> D7 (Push Button)

Soil Moisture Sensor
Notes:
Relay wiring: Relay IN → D6, VCC → 3.3V, GND → GND. Relay output connects to the pump’s power line.

LCD I2C: SDA → D2, SCL → D1 (standard I2C pins on NodeMCU).

Power: All sensors and modules share common GND with NodeMCU.

Blynk App: Communicates via WiFi, no physical wiring needed.

Arduino IDE Library Manager (Sketch > Include Library > Manage Libraries...).1. Essential Core LibrariesThese are necessary for basic ESP8266 connectivity and data handling:ESP8266WiFi: Built-in library (usually included with the ESP8266 board package) for handling Wi-Fi connections.ESP8266WebServer: Also built-in, used if you are hosting a local web server to monitor your system directly from a browser.ArduinoJson: Highly recommended if you are sending or receiving complex data packets (like status reports) to/from a dashboard or mobile app.2. Sensor-Specific LibrariesDepending on the specific sensors in your project, you will likely need:DHT sensor library (by Adafruit): Essential for your DHT11 or DHT22 temperature and humidity sensor. You will also need the Adafruit Unified Sensor library as a dependency.OneWire & DallasTemperature: If you decide to add waterproof temperature sensors (like the DS18B20).Adafruit SSD1306 & Adafruit GFX: Required if you add an OLED or LCD display to show moisture levels locally on the device.3. IoT & Connectivity LibrariesIf you are using a cloud platform for remote monitoring:Blynk: If you are using the Blynk IoT platform to control the pump and view sensor data via their app.Adafruit MQTT Library: Used if you are connecting your system to Adafruit IO to track data and create dashboards.
