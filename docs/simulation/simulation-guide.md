# Simulation Guide — Wokwi Online Simulator

Wokwi is a free, browser-based Arduino simulator. You can test this project virtually without any hardware — ideal for learning on a MacBook or any computer.

## What Wokwi Can Simulate

| Feature | Supported in Wokwi |
|---|---|
| Arduino UNO | ✅ Yes |
| DS18B20 temperature sensor | ✅ Yes (interactive slider) |
| 16x2 I2C LCD | ✅ Yes |
| 433 MHz RF modules | ❌ No (not supported) |

Because Wokwi does not support 433 MHz RF modules, the standard workaround is to simulate the DS18B20 + LCD together in one project (the core logic), and test the RF communication only on real hardware.

---

## Step-by-Step: Simulate DS18B20 + LCD on Wokwi

### Step 1 — Open Wokwi

Go to [https://wokwi.com](https://wokwi.com) and click **New Project → Arduino UNO**.

### Step 2 — Add Components

Click the **+** button (bottom left) and add:
- `DS18B20 Temperature Sensor`
- `LCD 1602 I2C`

### Step 3 — Wire the Components

Use the wiring table below inside Wokwi's visual editor (click a pin and drag):

| Component Pin | Arduino UNO Pin |
|---|---|
| DS18B20 GND | GND |
| DS18B20 VCC | 5V |
| DS18B20 DQ (DATA) | D2 |
| LCD GND | GND |
| LCD VCC | 5V |
| LCD SDA | A4 |
| LCD SCL | A5 |

> Wokwi automatically handles the 4.7 kΩ pull-up for DS18B20 — no need to add it manually.

### Step 4 — Paste the Simulation Code

In the code editor, paste the following simplified sketch:

```cpp
#include <OneWire.h>
#include <DallasTemperature.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define ONE_WIRE_BUS 2

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  sensors.begin();
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Temp Monitor");
}

void loop() {
  sensors.requestTemperatures();
  float tempC = sensors.getTempCByIndex(0);

  lcd.setCursor(0, 1);
  lcd.print("Temp: ");
  lcd.print(tempC, 2);
  lcd.print(" C  ");

  delay(1000);
}
```

### Step 5 — Run the Simulation

Click the **▶ Start Simulation** button. The LCD will display the temperature.

Click on the **DS18B20 chip** in the diagram and drag the **temperature slider** — the LCD updates in real time.

---

## Wokwi Libraries

Wokwi includes `OneWire` and `DallasTemperature` by default. If prompted, add them in the `libraries.txt` file:

```
OneWire
DallasTemperature
LiquidCrystal I2C
```

---

## What to Observe

- LCD row 1 shows the label `Temp Monitor`
- LCD row 2 shows the live temperature reading like `Temp: 27.50 C`
- Change the slider and watch the value update every second
- This confirms your sensor + LCD logic works before touching real hardware
