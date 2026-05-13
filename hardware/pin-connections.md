# Pin Connections

## Transmitter Unit

### DS18B20 → Arduino UNO (Transmitter)

| DS18B20 Pin | Arduino UNO Pin | Notes                                     |
|-------------|-----------------|-------------------------------------------|
| VCC (pin 3) | 5V              | Power supply                              |
| GND (pin 1) | GND             | Common ground                             |
| DATA (pin 2)| D2              | OneWire data; 4.7 kΩ pull-up to 5V needed |

> **DS18B20 pin order (flat side facing you):** GND — DATA — VCC (left to right)

### 433 MHz RF Transmitter → Arduino UNO (Transmitter)

| RF TX Pin | Arduino UNO Pin | Notes              |
|-----------|-----------------|--------------------|
| VCC       | 5V              | Power supply       |
| GND       | GND             | Common ground      |
| DATA      | D12             | VirtualWire TX pin |

### Pull-up Resistor Wiring

```
Arduino 5V ──┬── DS18B20 VCC
             │
           4.7 kΩ
             │
             └── DS18B20 DATA ── Arduino D2
```

---

## Receiver Unit

### 433 MHz RF Receiver → Arduino UNO (Receiver)

| RF RX Pin | Arduino UNO Pin | Notes              |
|-----------|-----------------|--------------------|
| VCC       | 5V              | Power supply       |
| GND       | GND             | Common ground      |
| DATA      | D11             | VirtualWire RX pin |

### 16x2 I2C LCD → Arduino UNO (Receiver)

| LCD I2C Pin | Arduino UNO Pin | Notes                          |
|-------------|-----------------|--------------------------------|
| VCC         | 5V              | Power supply                   |
| GND         | GND             | Common ground                  |
| SDA         | A4              | I2C data line (UNO hardware)   |
| SCL         | A5              | I2C clock line (UNO hardware)  |

---

## Quick Reference Diagram

```
TRANSMITTER UNIT
─────────────────────────────────────────────────────
DS18B20                        Arduino UNO
 Pin 1 (GND)    ────────────►  GND
 Pin 2 (DATA)   ────────────►  D2   [+ 4.7kΩ to 5V]
 Pin 3 (VCC)    ────────────►  5V

RF TX Module                   Arduino UNO
 GND            ────────────►  GND
 DATA           ────────────►  D12
 VCC            ────────────►  5V
─────────────────────────────────────────────────────

RECEIVER UNIT
─────────────────────────────────────────────────────
RF RX Module                   Arduino UNO
 GND            ────────────►  GND
 DATA           ────────────►  D11
 VCC            ────────────►  5V

16x2 I2C LCD                   Arduino UNO
 GND            ────────────►  GND
 VCC            ────────────►  5V
 SDA            ────────────►  A4
 SCL            ────────────►  A5
─────────────────────────────────────────────────────
```

## Important Notes

- Always connect GND of all components to the Arduino GND first.
- The 4.7 kΩ pull-up resistor is **mandatory** for DS18B20 — without it the sensor will not respond.
- Do not swap DATA pins: transmitter uses D12, receiver uses D11.
- If the LCD does not display anything, try changing the I2C address from `0x27` to `0x3F` in the receiver code.
- Attach a short 17 cm wire antenna to the RF modules' ANT pin for better range.
