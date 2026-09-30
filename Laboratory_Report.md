# Laboratory Report: ESP32 Analog I/O, PWM, and DAC

**Name:** Miche Louie B. Acompañado  
**Date:** September 30, 2026  

---

## 1. Introduction & Methodology

This laboratory activity explores the Analog-to-Digital Converter (ADC), Pulse Width Modulation (PWM), and Digital-to-Analog Converter (DAC) peripherals of the ESP32.

*Note on Equipment (Example 5):* A digital multimeter was unavailable for this session. Therefore, the DAC measurements in Example 5 were captured using an **ADC Loopback Method**, where the true analog output from the DAC (GPIO 25) was routed directly to an ADC input pin (GPIO 34) using a jumper wire, and voltages were calculated internally. This ensures the measurements are of the true DAC voltage levels and not averaged PWM signals.

---

## 2. Example 3: Analog Input (Potentiometer)

### Objective
To read variable voltages from a 10kΩ potentiometer using the ESP32's 12-bit ADC configured with 11dB attenuation.

### Data Table

| Knob Position | Raw Reading (0–4095) | Measured Input Voltage (mV) |
| :--- | :--- | :--- |
| **Minimum (Pos 1)** | 0 | 142 mV |
| **Lower-Mid (Pos 2)** | 575 | 618 mV |
| **Midpoint (Pos 3)** | 2619 | 2315 mV |
| **Upper-Mid (Pos 4)** | 3389 | 2840 mV |
| **Maximum (Pos 5)** | 4095 | 3160 mV |

### Visual Evidence
> **<img width="1366" height="768" alt="example 3 1" src="https://github.com/user-attachments/assets/9c437cf6-6f79-456e-859c-44af401edb57" />**

> **<img width="1366" height="768" alt="example 3 2" src="https://github.com/user-attachments/assets/f621f269-55fd-46e0-ac38-f78939287aac" />**

> **<img width="1366" height="768" alt="example 3 3" src="https://github.com/user-attachments/assets/0f1eede4-6043-4432-b818-a5990ee38ac6" />**

> **<img width="1366" height="768" alt="image" src="https://github.com/user-attachments/assets/83d2ab05-a592-47d2-ab7b-6318b9600cb3" />**

> **<img width="1366" height="768" alt="example 3 5" src="https://github.com/user-attachments/assets/eb17da68-f8ca-4309-b081-9b0f639c2c25" />**


### Comparison of Predicted vs. Observed Results
* **Predicted:** A linear 12-bit ADC reading across a $0.00\text{ V to } 3.30\text{ V}$ range should theoretically yield $0\text{ mV}$ at code $0$, $1650\text{ mV}$ at code $2048$, and $3300\text{ mV}$ at code $4095$.
* **Observed:** The observed results deviated predictably due to known ESP32 hardware characteristics:
  1. **Ground Offset:** Code $0$ yielded $142\text{ mV}$ instead of $0\text{ mV}$ due to non-linear deadband characteristics of the ADC near $0\text{ V}$.
  2. **Upper Saturation:** Code $4095$ peaked at $3160\text{ mV}$ ($3.16\text{ V}$) rather than $3300\text{ mV}$ ($3.30\text{ V}$). Under $11\text{ dB}$ attenuation, the ADC pipeline saturates at $\approx 3.16\text{ V}$, mapping all higher physical voltages to $4095$.

---

## 3. Example 4: PWM Output (LED Brightness)

### Objective
To map 12-bit ADC potentiometer readings (0–4095) to an 8-bit PWM duty cycle (0–255) using the ESP32 Core v3.x `ledcAttach()` API, controlling the brightness of an LED on GPIO 19.

### Data Table

| Knob Position | Raw ADC Value | Mapped PWM Duty (0–255) | Duty Cycle (%) | LED State |
| :--- | :--- | :--- | :--- | :--- |
| **Minimum** | 0 | 0 | 0% | Completely OFF |
| **Low** | ~321 | ~20 | 7.8% | Barely Visible |
| **Mid-range** | ~1834 | 114 | 44.7% | Medium Brightness |
| **High** | ~3387 | ~210 | 82.4% | Bright |
| **Maximum** | 4095 | 255 | 100% | Full Brightness |

### Visual Evidence
> **<img width="2048" height="1114" alt="943b04c2-ffcb-4fa0-b627-454cda826afb" src="https://github.com/user-attachments/assets/bd9ce767-0fe9-4fd8-9548-c23d2885af93" />**
><img width="1366" height="768" alt="image" src="https://github.com/user-attachments/assets/6e1099c1-6c51-4716-84d3-f34c825a2d38" />

> **<img width="2048" height="1092" alt="image" src="https://github.com/user-attachments/assets/361239b0-bf2b-4dc6-8a0b-c7f26844d4b4" />**
><img width="1366" height="768" alt="image" src="https://github.com/user-attachments/assets/c96c7413-9014-43df-8981-371d7db47d92" />

> **<img width="2048" height="1052" alt="c1db0967-fa7c-4f43-ba0d-397d82b02287" src="https://github.com/user-attachments/assets/0432bfb2-3960-4eba-9ea9-105a6173c1f0" />**
><img width="1366" height="768" alt="image" src="https://github.com/user-attachments/assets/de7ae82e-676e-4502-af7a-68c12c3c9467" />


> **<img width="2048" height="1066" alt="df682698-71b6-4ff0-bda5-e1cd6d2bc7de" src="https://github.com/user-attachments/assets/f9964ca3-49af-43af-a501-4d3de0390685" />**
><img width="1366" height="768" alt="image" src="https://github.com/user-attachments/assets/dd90abdc-1a1a-440c-96ff-1038eedb4b8e" />


> **<img width="2048" height="1196" alt="3d93e1ce-9dad-4ef2-b810-cdb73760cafa" src="https://github.com/user-attachments/assets/1d277604-70bf-43b9-b773-5065604b1821" />**
> <img width="1366" height="768" alt="image" src="https://github.com/user-attachments/assets/b7339bf8-2334-4b22-84ba-0c28d1d38c8e" />


### Comparison of Predicted vs. Observed Results
* **Predicted:** The 8-bit PWM duty cycle was predicted using the bit-scaling equation:
  $$\text{Predicted Duty} = \left\lfloor \frac{\text{Raw ADC} \times 255}{4095} \right\rfloor$$
* **Observed:** The observed duty cycle output matched the mathematical prediction with $100\%$ accuracy (e.g., Raw $1834 \rightarrow \text{Duty } 114$). Physically, while duty cycle scaled strictly linearly, the human eye perceived LED brightness non-linearly (appearing brighter faster at lower duty values), which is a standard optical perception phenomenon.

### Prompt Question: Capping Duty at 128
*If the maximum duty is constrained to 128 while the frequency remains unchanged, which part of the waveform changes?*  
**Answer:** The frequency ($f = 5\text{ kHz}$) and total signal period ($T = 200\text{ }\mu\text{s}$) remain completely unchanged. The parameter that changes is the maximum **pulse width ($T_{\text{HIGH}}$)**. At full potentiometer rotation, the waveform stays HIGH for only half the period ($100\text{ }\mu\text{s}$, or 50% duty cycle). Consequently, the LED's maximum physical brightness is cut roughly in half.

---

## 4. Example 5: DAC Output Measurement

### Objective
To generate true analog voltage steps using the ESP32's internal 8-bit DAC on **GPIO 25**.

*Setup:* As noted in the introduction, this was measured via an ADC loopback (GPIO 25 connected to GPIO 34) due to the lack of a multimeter. **This data represents a true analog output, not an averaged digital PWM square wave.**

### Data Table

| `dacWrite()` Code | Ideal Theoretical Voltage ($V = \frac{\text{Code}}{255} \times 3.3\text{ V}$) | Measured ADC Loopback Voltage (V) | Absolute Offset Error (V) |
| :--- | :--- | :--- | :--- |
| **0** | 0.00 V | **0.14 V** | $+0.14\text{ V}$ |
| **64** | 0.83 V | **0.83 V** | $0.00\text{ V}$ |
| **128** | 1.66 V | **1.63 V** | $-0.03\text{ V}$ |
| **192** | 2.48 V | **2.40 V** | $-0.08\text{ V}$ |
| **255** | 3.30 V | **3.14 V** | $-0.16\text{ V}$ |

### Visual Evidence
> **<img width="2048" height="1536" alt="b7ae366d-b144-4a11-9c44-1956c0234aa4" src="https://github.com/user-attachments/assets/0b845c03-daa8-4cba-abfc-806ca7c028b6" />**  
> **<img width="1366" height="768" alt="image" src="https://github.com/user-attachments/assets/5d8400a3-37dc-400b-a649-f54e48a0f8c3" />**

### Comparison of Predicted vs. Observed Results
* **Predicted:** An ideal 8-bit DAC with a $3.30\text{ V}$ reference increases linearly at $12.94\text{ mV}$ per step, starting at $0.00\text{ V}$ and reaching $3.30\text{ V}$ at code $255$.
* **Observed:**
  1. **At Code 0:** The observed voltage was $0.14\text{ V}$ ($+140\text{ mV}$ error). The internal DAC output buffer driver cannot pull completely down to $0.00\text{ V}$.
  2. **Mid-Range (Codes 64–192):** Output tracked linear predictions closely with minimal deviation ($0.00\text{ V to } -0.08\text{ V}$ offset).
  3. **At Code 255:** The observed voltage saturated at $3.14\text{ V}$ (a $-0.16\text{ V}$ error), showing that the internal output amplifier saturates approximately $160\text{ mV}$ below the physical $3.3\text{ V}$ supply rail.
