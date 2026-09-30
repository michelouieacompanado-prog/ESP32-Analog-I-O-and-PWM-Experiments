# ESP32 Analog I/O and PWM Experiments

This repository contains code and documentation for a series of experiments demonstrating Analog-to-Digital Conversion (ADC), Pulse Width Modulation (PWM), and Digital-to-Analog Conversion (DAC) using the ESP32 microcontroller.

## Hardware Requirements
* ESP32 Development Board
* Breadboard
* 10kΩ Potentiometer
* LED (Any color)
* 220Ω - 330Ω Resistor
* Jumper Wires

## Experiments Overview

### Example 3: ADC Potentiometer Reading
Reads a 12-bit analog value (0-4095) from a potentiometer connected to **GPIO 34**. The ESP32 maps this raw value to an estimated voltage (in millivolts) using its internal calibration lookup.

### Example 4: PWM LED Brightness Control
Reads the potentiometer value via ADC and maps the 12-bit range (0-4095) to an 8-bit PWM duty cycle (0-255). This PWM signal is output on **GPIO 16** to dynamically control the brightness of an LED.

### Example 5: DAC Output & ADC Loopback Measurement
Generates specific analog voltages using the ESP32's internal 8-bit DAC on **GPIO 25**. Since a digital multimeter was unavailable, this experiment uses an **ADC loopback** wire connecting GPIO 25 directly to GPIO 34 to measure and verify the generated output voltages in real-time.

## Wiring Guide
* **Potentiometer:** Outer pins to 3V3 and GND; Center wiper pin to GPIO 34.
* **LED:** Anode (long leg) to GPIO 16 via a 220Ω resistor; Cathode (short leg) to GND.
* **DAC Loopback (Ex 5):** Direct jumper wire from GPIO 25 to GPIO 34.
