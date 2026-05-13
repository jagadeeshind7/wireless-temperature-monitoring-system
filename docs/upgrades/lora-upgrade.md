# Upgrade Guide: LoRa Long-Range Version

This document explains how to replace the 433 MHz ASK RF modules with LoRa modules for dramatically improved range and reliability.

## Why Upgrade to LoRa?

| Feature | 433 MHz ASK Modules | LoRa Modules (SX1276/SX1278) |
|---|---|---|
| Range (open air) | ~30 m | 1 km – 10 km |
| Modulation | ASK (simple) | Chirp Spread Spectrum (CSS) |
| Interference resistance | Low | Very high |
| Data rate | Up to 10 kbps | 0.3 – 50 kbps |
| Power consumption | Medium | Very low (sleep mode) |
| Library | VirtualWire | RadioHead / LoRa.h |
| Cost | ~₹100 for pair | ~₹500 for pair |
| Ideal use case | Indoor, short range | Outdoor, long range IoT |

## Recommended Module

**Ra-02 LoRa Module (SX1278)** — 433 MHz band, widely available in India, compatible with Arduino.

## Pin Connections (LoRa SX1278 → Arduino UNO)

| LoRa Module Pin | Arduino UNO Pin | Notes |
|---|---|---|
| VCC | 3.3V | Use 3.3V, NOT 5V |
| GND | GND | Common ground |
| SCK | D13 | SPI clock |
| MISO | D12 | SPI MISO |
| MOSI | D11 | SPI MOSI |
| NSS (CS) | D10 | Chip select |
| RST | D9 | Reset |
| DIO0 | D2 | Interrupt |

> Use both TX and RX units with identical wiring. Replace the 433 MHz modules and update the code only — DS18B20 and LCD wiring stays the same.

## Transmitter Code (LoRa version)

```cpp
#include <OneWire.h>
#include <DallasTemperature.h>
#include <SPI.h>
#include <LoRa.h>

#define ONE_WIRE_BUS 4
#define SS_PIN 10
#define RST_PIN 9
#define DIO0_PIN 2

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

void setup() {
  Serial.begin(9600);
  sensors.begin();
  LoRa.setPins(SS_PIN, RST_PIN, DIO0_PIN);
  if (!LoRa.begin(433E6)) {
    Serial.println("LoRa init failed");
    while (1);
  }
  Serial.println("LoRa Transmitter Ready");
}

void loop() {
  sensors.requestTemperatures();
  float tempC = sensors.getTempCByIndex(0);
  char msg[16];
  dtostrf(tempC, 5, 2, msg);

  LoRa.beginPacket();
  LoRa.print(msg);
  LoRa.endPacket();

  Serial.print("Sent: ");
  Serial.println(msg);
  delay(2000);
}
```

## Receiver Code (LoRa version)

```cpp
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SPI.h>
#include <LoRa.h>

#define SS_PIN 10
#define RST_PIN 9
#define DIO0_PIN 2

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("LoRa Receiver");
  LoRa.setPins(SS_PIN, RST_PIN, DIO0_PIN);
  if (!LoRa.begin(433E6)) {
    lcd.setCursor(0, 1);
    lcd.print("LoRa Failed");
    while (1);
  }
}

void loop() {
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    String received = "";
    while (LoRa.available()) {
      received += (char)LoRa.read();
    }
    lcd.setCursor(0, 0);
    lcd.print("Temp Monitor    ");
    lcd.setCursor(0, 1);
    lcd.print(received);
    lcd.print(" C      ");
  }
}
```

## Libraries Required

- `LoRa` by Sandeep Mistry — install from Arduino Library Manager

## Key Benefits of LoRa Upgrade

- Range increases from 30 m to over 1 km in open areas
- Signal penetrates walls and buildings much better than ASK
- Suitable for outdoor temperature monitoring (weather stations, agriculture)
- Very low power draw — ideal for battery or solar-powered nodes
- Supports multiple transmitter nodes sending to one receiver (network of sensors)
