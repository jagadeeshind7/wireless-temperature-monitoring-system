#include <OneWire.h> 
#include <DallasTemperature.h> 
#include <VirtualWire.h> 
#define ONE_WIRE_BUS 2 
#define RF_TX_PIN 12 
#define STATUS_LED 13 
#define SAMPLE_INTERVAL_MS 1000 OneWire oneWire(ONE_WIRE_BUS); 
DallasTemperature sensors(&oneWire); 
unsigned long lastSampleTime = 0; char txMessage[16]; 

void setup() 
{ 
pinMode(STATUS_LED, OUTPUT); 
digitalWrite(STATUS_LED, LOW); 
sensors.begin(); 
vw_set_tx_pin(RF_TX_PIN); vw_setup(2000); 
} 
void loop() 
{ 
unsigned long currentTime = millis(); 
if (currentTime - lastSampleTime >= SAMPLE_INTERVAL_MS) 
{ 
lastSampleTime = currentTime; 
sensors.requestTemperatures(); 
float temperatureC = sensors.getTempCByIndex(0); 
if (temperatureC == DEVICE_DISCONNECTED_C) 
{ 
strcpy(txMessage, "ERR"); 
} 
else { 
dtostrf(temperatureC, 5, 2, txMessage); 
} 
vw_send((uint8_t *)txMessage, strlen(txMessage)); 
vw_wait_tx(); 
digitalWrite(STATUS_LED, !digitalRead(STATUS_LED)); 
} 
}