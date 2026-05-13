# System Architecture

## Overview

The Wireless Temperature Monitoring System is split into two independent embedded units that communicate wirelessly using 433 MHz ASK (Amplitude Shift Keying) RF modules.

```
┌────────────────────────────┐          RF 433 MHz          ┌─────────────────────────────┐
│      TRANSMITTER UNIT      │  ─────────────────────────►  │       RECEIVER UNIT         │
│                            │                               │                             │
│  DS18B20 Temperature       │                               │  433 MHz RF Receiver        │
│  Sensor (OneWire, D2)      │                               │  Module (VirtualWire, D11)  │
│          │                 │                               │          │                  │
│          ▼                 │                               │          ▼                  │
│  Arduino UNO               │                               │  Arduino UNO                │
│  (reads + formats data)    │                               │  (decodes + displays data)  │
│          │                 │                               │          │                  │
│          ▼                 │                               │          ▼                  │
│  433 MHz RF Transmitter    │                               │  16x2 I2C LCD Display       │
│  Module (VirtualWire, D12) │                               │  (SDA: A4, SCL: A5)         │
└────────────────────────────┘                               └─────────────────────────────┘
```

## Data Flow

```
DS18B20 Sensor
     │
     │  OneWire Protocol
     ▼
Arduino UNO (Transmitter)
     │  DallasTemperature Library reads float value
     │  dtostrf() converts float → ASCII string
     │  VirtualWire sends ASCII bytes at 2000 bps
     ▼
433 MHz RF Transmitter
     │
     │  Wireless RF Signal (up to ~30 m line-of-sight)
     ▼
433 MHz RF Receiver
     │
     │  VirtualWire decodes received bytes
     ▼
Arduino UNO (Receiver)
     │  Validates received string
     │  Handles: valid temp / ERR / no signal
     ▼
16x2 LCD via I2C
     │  Displays formatted temperature
     ▼
User reads live temperature
```

## Communication Protocol

| Parameter        | Value                |
|------------------|----------------------|
| Modulation       | ASK (OOK)            |
| Frequency        | 433.92 MHz           |
| Library          | VirtualWire          |
| Bit Rate         | 2000 bps             |
| Data Format      | ASCII text string    |
| Sample Interval  | 1000 ms              |
| Timeout          | 3000 ms              |
| Error Packet     | `"ERR"` string       |

## Software Architecture

### Transmitter Firmware

```
setup()
  ├── sensors.begin()         → Initialize DS18B20
  ├── vw_set_tx_pin(12)       → Set RF TX pin
  └── vw_setup(2000)          → Set bit rate

loop()
  └── every 1000 ms:
        ├── sensors.requestTemperatures()
        ├── sensors.getTempCByIndex(0)
        ├── dtostrf() → ASCII
        ├── vw_send() → transmit
        └── Toggle LED
```

### Receiver Firmware

```
setup()
  ├── lcd.init() + lcd.backlight()
  ├── vw_set_rx_pin(11)
  ├── vw_setup(2000)
  └── vw_rx_start()

loop()
  ├── vw_get_message()  → check for packet
  │     ├── "ERR"       → lcd "Sensor Error"
  │     └── numeric     → lcd temperature value
  └── timeout check     → lcd "No Signal"
```
