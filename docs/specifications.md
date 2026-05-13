# Technical Specifications

## System Specifications

| Parameter                     | Value                          |
|-------------------------------|--------------------------------|
| Microcontroller               | ATmega328P (Arduino UNO)       |
| Operating voltage             | 5 V                            |
| Clock speed                   | 16 MHz                         |
| Programming language          | Embedded C (Arduino framework) |
| Communication protocol (RF)   | VirtualWire ASK 433.92 MHz     |
| Communication protocol (sensor) | OneWire (DS18B20)            |
| Communication protocol (LCD)  | I2C (TWI)                      |
| RF bit rate                   | 2000 bps                       |
| Sensor update interval        | 1000 ms                        |
| Receiver timeout threshold    | 3000 ms                        |
| Temperature measurement range | −55 °C to +125 °C              |
| Temperature accuracy          | ±0.5 °C                        |
| Temperature resolution        | 12-bit (0.0625 °C steps)       |
| Wireless range (open air)     | ~30 m (typical)                |
| LCD display                   | 16 × 2 character, I2C          |
| Power supply (each unit)      | 5 V via USB                    |
| Flash memory (UNO)            | 32 KB                          |
| SRAM (UNO)                    | 2 KB                           |

## Memory Usage (Approximate)

| Sketch       | Flash Used | SRAM Used |
|--------------|-----------|-----------|
| Transmitter  | ~14 KB    | ~600 B    |
| Receiver     | ~16 KB    | ~800 B    |

## Library Versions Tested

| Library           | Version  |
|-------------------|----------|
| OneWire           | 2.3.7    |
| DallasTemperature | 3.9.0    |
| VirtualWire       | 1.27     |
| LiquidCrystal_I2C | 1.1.2    |
| Wire (built-in)   | Built-in |
