# How the System Works — Step by Step

This document explains what happens inside the project from the moment power is applied until the temperature appears on the LCD.

## Power ON Sequence

| Step | What Happens |
|------|-------------|
| 1    | Both Arduino UNO boards receive 5V power via USB |
| 2    | Transmitter initialises DS18B20 and sets up VirtualWire TX at 2000 bps |
| 3    | Receiver initialises the I2C LCD, turns on backlight, and starts VirtualWire RX |
| 4    | Receiver LCD shows `Waiting...` until first packet arrives |

## Normal Operation Loop

### Transmitter side (every 1 second)

1. `sensors.requestTemperatures()` — sends a conversion command to DS18B20 over OneWire.
2. DS18B20 measures temperature and stores the result internally (takes ~750 ms at 12-bit resolution).
3. `getTempCByIndex(0)` — reads the temperature as a floating-point number.
4. `dtostrf()` — converts the float (e.g., `27.50`) into an ASCII string `"27.50"`.
5. `vw_send()` — packages the ASCII string into VirtualWire packets and sends over the 433 MHz RF transmitter.
6. `vw_wait_tx()` — waits until all bytes have been transmitted before looping again.
7. Onboard LED (D13) toggles as a visual heartbeat indicator.

### Receiver side (continuous polling)

1. `vw_get_message()` — checks if a valid VirtualWire packet has arrived (non-blocking check).
2. If a packet arrives:
   - If the content is `"ERR"` → display `Sensor Error` on LCD row 2.
   - If it is a valid number string → display `27.50 C` on LCD row 2.
   - Record the current time as `lastPacketTime`.
3. If no packet has arrived for **3000 ms** → display `No Signal` on LCD row 2.
4. Onboard LED (D13) toggles on every successfully received packet.

## OneWire Protocol (DS18B20)

The DS18B20 communicates using a 1-Wire bus. This means only a single data wire is needed between sensor and Arduino, plus power and ground. The DallasTemperature library handles all the protocol details automatically.

```
Arduino D2 ── (DATA line) ── DS18B20 DATA pin
                │
            4.7 kΩ resistor
                │
              5V (pull-up)
```

The resistor is mandatory. Without it, the OneWire bus has no defined logic-HIGH level and the communication fails.

## VirtualWire Communication

VirtualWire uses a simple ASK (Amplitude Shift Keying) modulation. The library:
- Adds a preamble and start symbol so the receiver can lock on.
- Adds a 4-bit message length field.
- Adds a CRC (Cyclic Redundancy Check) for basic error detection.
- If the CRC fails, the packet is silently discarded (no corrupted data reaches the LCD).

## I2C LCD Communication

The I2C backpack on the 16x2 LCD converts the two-wire I2C bus into the 8-bit parallel interface the LCD chip expects. The LiquidCrystal_I2C library handles this automatically. SDA (A4) and SCL (A5) are the only signal pins needed on the Arduino UNO.

## Error Handling

| Fault Condition              | System Response                        |
|------------------------------|----------------------------------------|
| DS18B20 disconnected         | Transmitter sends `"ERR"` packet       |
| RF link broken / out of range | Receiver shows `No Signal` after 3 s  |
| LCD I2C address mismatch     | LCD stays blank (check `0x27`/`0x3F`)  |
| Missing pull-up resistor     | Sensor reads `DEVICE_DISCONNECTED_C`   |
