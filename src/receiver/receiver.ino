#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <VirtualWire.h>

#define RF_RX_PIN 11
#define STATUS_LED 13
#define LCD_ADDRESS 0x27
#define LCD_COLUMNS 16
#define LCD_ROWS 2
#define PACKET_TIMEOUT_MS 3000

LiquidCrystal_I2C lcd(LCD_ADDRESS, LCD_COLUMNS, LCD_ROWS);

unsigned long lastPacketTime = 0;
char receivedText[16] = "Waiting...";

void showDisplay(const char *line2) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temp Monitor");
  lcd.setCursor(0, 1);
  lcd.print(line2);
}

void setup() {
  pinMode(STATUS_LED, OUTPUT);
  digitalWrite(STATUS_LED, LOW);

  lcd.init();
  lcd.backlight();
  showDisplay("Waiting...");

  vw_set_rx_pin(RF_RX_PIN);
  vw_setup(2000);
  vw_rx_start();
}

void loop() {
  uint8_t buffer[VW_MAX_MESSAGE_LEN];
  uint8_t bufferLength = VW_MAX_MESSAGE_LEN;

  if (vw_get_message(buffer, &bufferLength)) {
    buffer[bufferLength] = '\0';
    strncpy(receivedText, (char *)buffer, sizeof(receivedText) - 1);
    receivedText[sizeof(receivedText) - 1] = '\0';
    lastPacketTime = millis();

    digitalWrite(STATUS_LED, !digitalRead(STATUS_LED));

    if (strcmp(receivedText, "ERR") == 0) {
      showDisplay("Sensor Error");
    } else {
      char lcdLine[17];
      snprintf(lcdLine, sizeof(lcdLine), "%s C", receivedText);
      showDisplay(lcdLine);
    }
  }

  if (millis() - lastPacketTime > PACKET_TIMEOUT_MS) {
    showDisplay("No Signal");
  }
}
