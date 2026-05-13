# Troubleshooting Guide

Work through problems in this order: **Power → Wiring → Code → Libraries**. Most issues are caused by a wrong wire, missing pull-up resistor, or wrong I2C address.

---

## Problem 1 — LCD shows nothing / blank screen

**Possible causes and fixes:**

| Cause | Fix |
|---|---|
| I2C address wrong | Change `0x27` to `0x3F` in receiver code and re-upload |
| SDA/SCL swapped | Verify SDA → A4, SCL → A5 on Arduino UNO |
| Backlight off | Call `lcd.backlight()` in `setup()` |
| Contrast too low | Turn the small blue potentiometer on the I2C backpack |
| Missing library | Install `LiquidCrystal_I2C` from Library Manager |
| Power issue | Check 5V and GND connected to LCD |

**How to find your LCD I2C address:**
Upload this I2C scanner sketch and open Serial Monitor at 9600 baud:

```cpp
#include <Wire.h>
void setup() {
  Wire.begin();
  Serial.begin(9600);
}
void loop() {
  for (byte addr = 1; addr < 127; addr++) {
    Wire.beginTransmission(addr);
    if (Wire.endTransmission() == 0) {
      Serial.print("Found device at 0x");
      Serial.println(addr, HEX);
    }
  }
  delay(5000);
}
```

---

## Problem 2 — Receiver shows `No Signal`

| Cause | Fix |
|---|---|
| RF modules too far apart | Move units closer; start within 1 metre |
| DATA pins swapped | Confirm TX DATA → D12, RX DATA → D11 |
| Bit rate mismatch | Both sketches must use `vw_setup(2000)` |
| TX unit not powered | Check USB power on transmitter Arduino |
| No antenna wire | Solder a 17 cm wire to the ANT pad on each module |
| Shared power rail issue | Power both boards from separate USB cables |

---

## Problem 3 — LCD shows `Sensor Error`

| Cause | Fix |
|---|---|
| Missing pull-up resistor | Add 4.7 kΩ between DS18B20 DATA and 5V |
| Wrong DATA pin | DS18B20 DATA must connect to D2 on transmitter |
| Sensor pin order wrong | Flat face towards you: GND — DATA — VCC |
| Sensor damaged | Test with a known working DS18B20 |
| Missing library | Install `OneWire` and `DallasTemperature` |

---

## Problem 4 — Compilation errors in Arduino IDE

| Error message | Fix |
|---|---|
| `'VirtualWire.h' not found` | Install VirtualWire library manually (ZIP install) |
| `'LiquidCrystal_I2C.h' not found` | Install LiquidCrystal_I2C from Library Manager |
| `'DallasTemperature.h' not found` | Install DallasTemperature from Library Manager |
| `'OneWire.h' not found` | Install OneWire from Library Manager |
| `vw_setup` undeclared | Wrong VirtualWire version; use the standard 1.x release |

---

## Problem 5 — Temperature value looks wrong

| Cause | Fix |
|---|---|
| Wrong resistor value used | Confirm 4.7 kΩ (yellow-violet-red) not 470 Ω |
| 12-bit conversion not complete | DallasTemperature handles this; no change needed |
| Multiple DS18B20 on same bus | Use index 0 for first sensor; add address search if needed |
| Floating pin | Ensure DATA pin is firmly connected with no loose contact |

---

## Debugging Tips

- Always test the DS18B20 alone first using Serial Monitor (print temperature before adding RF).
- Always test the LCD alone first with a simple "Hello World" sketch.
- Keep the two Arduino boards within 30 cm when first testing RF to rule out range issues.
- Use the onboard LEDs (D13) as heartbeat indicators — TX LED blinks on send, RX LED blinks on receive.
