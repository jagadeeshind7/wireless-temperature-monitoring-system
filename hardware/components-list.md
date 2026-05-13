# Components List

## Full Bill of Materials (BOM)

| # | Component                          | Quantity | Purpose                                      | Approx. Cost (INR) |
|---|------------------------------------|:--------:|----------------------------------------------|--------------------|
| 1 | Arduino UNO R3                     | 2        | Microcontroller for TX and RX units          | ₹400 each          |
| 2 | DS18B20 Temperature Sensor         | 1        | Measures temperature using OneWire protocol  | ₹80                |
| 3 | 4.7 kΩ Resistor                    | 1        | Pull-up for DS18B20 OneWire data line        | ₹2                 |
| 4 | 433 MHz RF Transmitter Module      | 1        | Sends data wirelessly from TX Arduino        | ₹50                |
| 5 | 433 MHz RF Receiver Module         | 1        | Receives wireless data at RX Arduino         | ₹50                |
| 6 | 16x2 LCD with I2C backpack         | 1        | Displays received temperature                | ₹150               |
| 7 | Breadboard (full size)             | 2        | Prototyping without soldering                | ₹60 each           |
| 8 | Jumper wires (male-to-male)        | 30+      | Electrical connections                       | ₹60 (pack)         |
| 9 | USB Type-B cable (Arduino cable)   | 2        | Power and programming                        | ₹80 each           |

**Total estimated cost: ₹1,000 – ₹1,200**

## Component Details

### DS18B20 Temperature Sensor

| Parameter          | Value                   |
|--------------------|-------------------------|
| Protocol           | OneWire (1-Wire bus)    |
| Supply voltage     | 3.0 V – 5.5 V           |
| Temperature range  | −55 °C to +125 °C       |
| Accuracy           | ±0.5 °C (−10 to +85 °C) |
| Resolution         | 9 to 12 bit (configurable) |
| Package            | TO-92 (3 pin)           |

### 433 MHz RF Modules

| Parameter          | Transmitter     | Receiver        |
|--------------------|-----------------|-----------------|
| Frequency          | 433.92 MHz      | 433.92 MHz      |
| Modulation         | ASK / OOK       | ASK / OOK       |
| Supply voltage     | 3.5 V – 12 V    | 5 V             |
| Data rate          | Up to 10 kbps   | Up to 10 kbps   |
| Range (open air)   | ~30 m (typical) | ~30 m (typical) |

### 16x2 I2C LCD Module

| Parameter       | Value                     |
|-----------------|---------------------------|
| Columns × Rows  | 16 × 2 characters         |
| Interface       | I2C via PCF8574 backpack  |
| Default address | 0x27 (some boards: 0x3F)  |
| Supply voltage  | 5 V                       |
| Backlight       | Yes (controllable)        |
