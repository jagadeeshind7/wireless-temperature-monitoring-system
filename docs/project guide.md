# Wireless Temperature Monitoring System Project Guide

This is a beginner-friendly embedded systems project that reads temperature using a DS18B20 sensor and sends it wirelessly from one Arduino UNO to another using low-cost 433 MHz RF modules.[cite:1][cite:6][cite:11]
The receiver Arduino displays the live temperature on a 16x2 LCD connected through I2C, which reduces the number of wiring connections compared with a parallel LCD interface.[cite:7][cite:10]

## Beginner explanation

Think of this project as two small Arduino stations:

- The **transmitter station** measures temperature.
- The **receiver station** listens to the transmitted data.
- The LCD acts like a tiny screen that shows the received temperature.

So, instead of connecting the temperature sensor directly to the display with a long wire, the system sends the reading through the air using RF communication.[cite:1][cite:11]

## Data flow

1. DS18B20 senses temperature.
2. Arduino UNO transmitter reads the sensor value.
3. Transmitter converts the number into text.
4. 433 MHz transmitter sends the text wirelessly.
5. 433 MHz receiver receives the text.
6. Receiver Arduino shows the value on the LCD.

## Why these parts are used

| Part | Why it is used |
|---|---|
| DS18B20 | Digital temperature sensor, easy to interface using OneWire.[cite:6][cite:9] |
| Arduino UNO | Simple and beginner-friendly controller board |
| 433 MHz RF modules | Cheap wireless communication option for small embedded projects.[cite:1][cite:11] |
| 16x2 I2C LCD | Displays output clearly while using only two I2C signal pins.[cite:7][cite:10] |

## Suggested testing order

- Test DS18B20 alone and print temperature on Serial Monitor.
- Test LCD alone with a simple hello message.
- Test RF modules by sending a short sample word.
- Combine everything only after each small block works.

That testing order reduces confusion because you will know exactly which section is failing.
