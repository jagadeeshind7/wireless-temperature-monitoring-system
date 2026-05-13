# Upgrade Guide: ESP32 Version

This document describes how to upgrade the Wireless Temperature Monitoring System from Arduino UNO to ESP32, which adds Wi-Fi connectivity, more processing power, and dual-core operation.

## Why Upgrade to ESP32?

| Feature | Arduino UNO | ESP32 |
|---|---|---|
| Wi-Fi | ❌ No | ✅ Built-in |
| Bluetooth | ❌ No | ✅ Built-in |
| CPU speed | 16 MHz | 240 MHz |
| RAM | 2 KB | 520 KB |
| Flash | 32 KB | 4 MB |
| Analog pins | 6 | 18 |
| Price | ~₹400 | ~₹350 |
| Cloud IoT support | ❌ No | ✅ Yes |

## What Changes in the Circuit

### ESP32 Transmitter Pin Mapping

| Component | Arduino UNO Pin | ESP32 Pin |
|---|---|---|
| DS18B20 DATA | D2 | GPIO4 |
| RF TX DATA | D12 | GPIO12 |

### ESP32 Receiver Pin Mapping

| Component | Arduino UNO Pin | ESP32 Pin |
|---|---|---|
| RF RX DATA | D11 | GPIO14 |
| LCD SDA | A4 | GPIO21 (hardware I2C) |
| LCD SCL | A5 | GPIO22 (hardware I2C) |

> **Important:** ESP32 GPIO pins run at 3.3 V logic. DS18B20 supports 3.3 V but 433 MHz modules prefer 5 V — use a level shifter or power TX module separately.

## ESP32 Transmitter Code (Wi-Fi enabled)

```cpp
#include <OneWire.h>
#include <DallasTemperature.h>
#include <WiFi.h>
#include <HTTPClient.h>

#define ONE_WIRE_BUS 4

const char* ssid     = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";
const char* serverURL = "http://YOUR_SERVER/temperature";

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

void setup() {
  Serial.begin(115200);
  sensors.begin();
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWi-Fi connected");
}

void loop() {
  sensors.requestTemperatures();
  float tempC = sensors.getTempCByIndex(0);

  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    String payload = "{\"temperature\":" + String(tempC, 2) + "}";
    http.begin(serverURL);
    http.addHeader("Content-Type", "application/json");
    http.POST(payload);
    http.end();
  }

  Serial.print("Temperature: ");
  Serial.println(tempC);
  delay(5000);
}
```

## Libraries for ESP32 Version

Install from Arduino IDE Library Manager:
- `OneWire`
- `DallasTemperature`
- `WiFi` (built-in with ESP32 board package)
- `HTTPClient` (built-in with ESP32 board package)

## Installing ESP32 Board in Arduino IDE

1. Open Arduino IDE → File → Preferences
2. Add this URL to "Additional boards manager URLs":
   `https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json`
3. Tools → Board → Boards Manager → search "ESP32" → Install
4. Select board: **ESP32 Dev Module**

## Advantages of the ESP32 Upgrade

- Temperature data can be sent to cloud platforms (ThingSpeak, Firebase, Blynk)
- No RF modules needed — uses Wi-Fi directly
- Multiple sensors can be connected and reported
- Supports deep sleep mode for battery-powered operation
