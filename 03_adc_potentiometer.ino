#include <Arduino.h>

const uint8_t POT_PIN = 34;

void setup() {
  Serial.begin(115200);
  
  // Configure ADC resolution (12-bit: 0 - 4095) and 11dB attenuation (~3.3V range)
  analogReadResolution(12);
  analogSetPinAttenuation(POT_PIN, ADC_11db);
}

void loop() {
  const int raw = analogRead(POT_PIN);
  const uint32_t mv = analogReadMilliVolts(POT_PIN);

  Serial.print("Raw ADC: ");
  Serial.print(raw);
  Serial.print("\tVoltage: ");
  Serial.print(mv);
  Serial.println(" mV");

  delay(200);
}
