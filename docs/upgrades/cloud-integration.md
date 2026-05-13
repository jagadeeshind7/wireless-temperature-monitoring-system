# Upgrade Guide: Cloud Integration

This document explains how to send temperature data from the system to cloud IoT platforms for remote monitoring, data logging, and alerts.

## Cloud Platforms Compared

| Platform | Free Tier | Ease of Use | Real-time Charts | Alerts | Best For |
|---|---|---|---|---|---|
| ThingSpeak | ✅ Yes | ⭐⭐⭐⭐⭐ | ✅ Yes | ✅ Yes | Beginners, students |
| Blynk | ✅ Yes (limited) | ⭐⭐⭐⭐ | ✅ Yes | ✅ Yes | Mobile app dashboard |
| Firebase | ✅ Yes | ⭐⭐⭐ | Manual | ❌ No | Developers |
| MQTT Broker | ✅ Yes | ⭐⭐ | Manual | Manual | Advanced IoT |

## Option 1: ThingSpeak (Recommended for Beginners)

ThingSpeak is a free IoT analytics platform by MathWorks. It stores data, draws charts automatically, and is very easy to set up.

### Setup Steps

1. Create a free account at [thingspeak.com](https://thingspeak.com)
2. Create a **New Channel** → enable **Field 1** → name it `Temperature (C)`
3. Copy your **Write API Key** from the API Keys tab

### ESP32 Code for ThingSpeak

```cpp
#include <OneWire.h>
#include <DallasTemperature.h>
#include <WiFi.h>
#include <HTTPClient.h>

#define ONE_WIRE_BUS 4

const char* ssid       = "YOUR_WIFI_SSID";
const char* password   = "YOUR_WIFI_PASSWORD";
const char* apiKey     = "YOUR_THINGSPEAK_WRITE_API_KEY";
const char* server     = "http://api.thingspeak.com/update";

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
  Serial.println("\nConnected to Wi-Fi");
}

void loop() {
  sensors.requestTemperatures();
  float tempC = sensors.getTempCByIndex(0);

  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    String url = String(server) + "?api_key=" + apiKey + "&field1=" + String(tempC, 2);
    http.begin(url);
    int responseCode = http.GET();
    Serial.print("ThingSpeak response: ");
    Serial.println(responseCode);
    http.end();
  }

  delay(15000); // ThingSpeak free plan requires minimum 15 seconds between updates
}
```

### What You Will See on ThingSpeak

- Live temperature chart updating every 15 seconds
- Historical data stored in the cloud
- Public or private channel option
- Download data as CSV

---

## Option 2: Blynk (Mobile App Dashboard)

Blynk lets you build a mobile app dashboard to view temperature on your phone.

### Setup Steps

1. Download the **Blynk** app on your phone (iOS/Android)
2. Create a free account at [blynk.cloud](https://blynk.cloud)
3. Create a new **Template** → add a **Gauge** widget → assign to Virtual Pin `V0`
4. Copy your **Auth Token**

### ESP32 Code for Blynk

```cpp
#define BLYNK_TEMPLATE_ID "YOUR_TEMPLATE_ID"
#define BLYNK_AUTH_TOKEN  "YOUR_AUTH_TOKEN"

#include <BlynkSimpleEsp32.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS 4

char ssid[]     = "YOUR_WIFI_SSID";
char pass[]     = "YOUR_WIFI_PASSWORD";

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
BlynkTimer timer;

void sendTemperature() {
  sensors.requestTemperatures();
  float tempC = sensors.getTempCByIndex(0);
  Blynk.virtualWrite(V0, tempC);
}

void setup() {
  sensors.begin();
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  timer.setInterval(5000L, sendTemperature);
}

void loop() {
  Blynk.run();
  timer.run();
}
```

---

## System Architecture with Cloud

```
DS18B20
   │
   ▼
ESP32 (Wi-Fi enabled)
   │
   │  HTTP / MQTT over Wi-Fi
   ▼
Cloud Platform (ThingSpeak / Blynk)
   │
   ▼
Web Browser / Mobile App
(View live temperature from anywhere)
```

## Summary of What Each Upgrade Adds

| Step | What You Add | New Capability |
|---|---|---|
| Base project | Arduino + RF modules | Short-range wireless display |
| ESP32 upgrade | Replace Arduino UNOs | Wi-Fi connectivity |
| LoRa upgrade | Replace RF modules | Long-range (1 km+) wireless |
| Cloud upgrade | Add ThingSpeak/Blynk | Remote monitoring from anywhere |
