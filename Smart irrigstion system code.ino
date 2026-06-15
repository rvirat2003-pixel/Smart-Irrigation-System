#define BLYNK_TEMPLATE_ID "TMPL3H9ooStI1"
#define BLYNK_TEMPLATE_NAME "smart irrigation system"

#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

// ===== WIFI =====
char auth[] = "YOUR_AUTH";
char ssid[] = "Vishal Mobile 5G";
char pass[] = "Vishalrajput";

// ===== LCD =====
LiquidCrystal_I2C lcd(0x27, 16, 2);

// ===== DHT =====
#define DHTPIN D4
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// ===== PINS =====
#define SOIL A0
#define PIR D5
#define RELAY D6
#define BUTTON D7
#define BUZZER D0

#define RELAY_ON LOW
#define RELAY_OFF HIGH

BlynkTimer timer;

// ===== VARIABLES =====
float temp = 0, hum = 0, soilVal = 0;

int relayState = RELAY_OFF;
int buttonState = HIGH;

bool autoMode = true;
int threshold = 30;

unsigned long lastReconnectAttempt = 0;

// ===== PIR BUZZER =====
unsigned long lastPirToggle = 0;
bool pirBeepState = false;

// ===== CALIBRATION =====
int dryValue = 850;
int wetValue = 400;

// ===== BUZZER =====
void beepOnce() {
  digitalWrite(BUZZER, HIGH);
  delay(150);
  digitalWrite(BUZZER, LOW);
}

void beepTwice() {
  beepOnce(); delay(150); beepOnce();
}

// ===== BLYNK CONTROLS =====
BLYNK_WRITE(V0) {
  if (!autoMode) {
    relayState = param.asInt();
    digitalWrite(RELAY, relayState);
  }
}
BLYNK_WRITE(V1) { autoMode = param.asInt(); }
BLYNK_WRITE(V2) { threshold = param.asInt(); }

// ===== DHT (1 MIN) =====
void readDHT() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (!isnan(h)) hum = h;
  if (!isnan(t)) temp = t;

  if (Blynk.connected()) {
    Blynk.virtualWrite(V3, temp);
    Blynk.virtualWrite(V4, hum);
  }
}

// ===== SOIL (15 SEC) =====
void readSoil() {
  int raw = analogRead(SOIL);

  soilVal = (float)(raw - dryValue) * 100.0 / (wetValue - dryValue);
  soilVal = constrain(soilVal, 0, 100);

  if (autoMode) {
    relayState = (soilVal < threshold) ? RELAY_ON : RELAY_OFF;
    digitalWrite(RELAY, relayState);
  }

  if (Blynk.connected()) {
    Blynk.virtualWrite(V5, soilVal);
  }
}

// ===== PIR REAL-TIME =====
void handlePIR() {

  if (digitalRead(PIR) == HIGH && relayState == RELAY_OFF) {

    if (millis() - lastPirToggle > 200) {
      pirBeepState = !pirBeepState;
      digitalWrite(BUZZER, pirBeepState);
      lastPirToggle = millis();
    }

    if (Blynk.connected()) {
      Blynk.virtualWrite(V6, 255);
    }

  } else {
    digitalWrite(BUZZER, LOW);

    if (Blynk.connected()) {
      Blynk.virtualWrite(V6, 0);
    }
  }
}

// ===== WIFI RECONNECT =====
void checkConnection() {

  if (WiFi.status() != WL_CONNECTED) {
    if (millis() - lastReconnectAttempt > 10000) {
      WiFi.begin(ssid, pass);
      lastReconnectAttempt = millis();
    }
  } 
  else {
    if (!Blynk.connected()) {
      Blynk.connect(1000);
    }
  }
}

// ===== SETUP =====
void setup() {
  Serial.begin(115200);

  lcd.begin();
  lcd.backlight();

  pinMode(PIR, INPUT);
  pinMode(RELAY, OUTPUT);
  pinMode(BUTTON, INPUT_PULLUP);
  pinMode(BUZZER, OUTPUT);

  digitalWrite(RELAY, RELAY_OFF);

  dht.begin();

  lcd.setCursor(0,0);
  lcd.print("Connecting WiFi");

  WiFi.begin(ssid, pass);

  unsigned long start = millis();
  while (WiFi.status() != WL_CONNECTED && millis() - start < 8000) {
    delay(500);
  }

  lcd.clear();

  Blynk.config(auth);
  if (WiFi.status() == WL_CONNECTED) {
    Blynk.connect(1000);
  }

  timer.setInterval(60000L, readDHT);
  timer.setInterval(15000L, readSoil);
  timer.setInterval(5000L, checkConnection);
}

// ===== LOOP =====
void loop() {

  if (WiFi.status() == WL_CONNECTED && Blynk.connected()) {
    Blynk.run();
  }

  timer.run();

  // ===== BUTTON =====
  if (digitalRead(BUTTON) == LOW) {
    delay(50);
    if (buttonState == HIGH) {
      relayState = !relayState;
      digitalWrite(RELAY, relayState);
      beepTwice();
    }
    buttonState = LOW;
  } else {
    buttonState = HIGH;
  }

  // ===== PIR =====
  handlePIR();

  // ===== LCD =====
  lcd.setCursor(0, 0);
  lcd.print("T:");
  lcd.print(temp,1);
  lcd.print(" H:");
  lcd.print(hum,1);
  lcd.print("   ");

  lcd.setCursor(0, 1);
  lcd.print("S:");
  lcd.print(soilVal,1);
  lcd.print(relayState == RELAY_ON ? " ON" : " OFF");

  lcd.print(WiFi.status() == WL_CONNECTED ? " W:O" : " W:X");
}