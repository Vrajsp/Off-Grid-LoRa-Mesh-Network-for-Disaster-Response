# LoRaWAN Off-Grid Mesh Communicator

![License](https://img.shields.io/badge/license-MIT-blue.svg) ![Platform](https://img.shields.io/badge/platform-ESP32-green.svg) ![Tech](https://img.shields.io/badge/tech-LoRa_RF-orange.svg)

## Project Overview
This repository contains the firmware and hardware design for a **Decentralized Emergency Communication Node**. Designed for disaster scenarios where cellular infrastructure is compromised, this system utilizes **LoRa (Long Range)** modulation to establish a peer-to-peer mesh network. The device broadcasts encrypted telemetry and GPS coordinates, enabling search-and-rescue teams to triangulate positions and coordinate efforts without reliance on the internet or satellite uplinks.

## Technical Architecture
The system operates on the Sub-GHz ISM band (433MHz/915MHz), leveraging Chirp Spread Spectrum (CSS) modulation to achieve high interference immunity.

* **Micro-Controller:** ESP32 (Dual Core, 240MHz) handling stack logic.
* **Physical Layer (PHY):** Semtech SX1278 Transceiver.
* **Link Budget:** ~148dB, allowing for 5km+ range in Line-of-Sight (LoS) conditions.
* **Network Topology:** Asynchronous Mesh (Flood-Fill Algorithm).

## Hardware BoM (Bill of Materials)
| Component | Specification | Role |
| :--- | :--- | :--- |
| **ESP32 DevKit V1** | Xtensa LX6 | Central Processing Unit |
| **Ra-02 (SX1278)** | 433MHz, SPI | LoRa Transceiver |
| **NEO-6M GPS** | 9600 Baud, UART | Geolocation Provider |
| **SSD1306 OLED** | 128x64, I2C | User Interface |
| **Li-Ion 18650** | 2500mAh | Power Source |

## Circuit & Pinout
### SPI Interface (LoRa)
* **MISO:** GPIO 19
* **MOSI:** GPIO 23
* **SCK:** GPIO 18
* **NSS:** GPIO 5

### UART Interface (GPS)
* **TX (GPS)** -> **GPIO 16 (RX2)**
* **RX (GPS)** -> **GPIO 17 (TX2)**

## Installation & Build
1.  **Dependencies:**
    * `Sandeep Mistry LoRa Library`
    * `TinyGPS++`
    * `Adafruit GFX` & `SSD1306`
2.  **Configuration:**
    * Set `#define BAND` in `main.cpp` to match your local ISM regulation (433E6 for Asia/Europe, 915E6 for US).
3.  **Antenna Tuning:** Ensure a 17.3cm wire antenna (1/4 wavelength) is soldered to the Ra-02 module for 433MHz operation.

## Future Improvements
* Implementation of **AES-128 Encryption** for secure military/tactical use.
* Integration of **MQTT Gateway** node to bridge the mesh network to the cloud when internet is available.
* **Packet Hopping:** Advanced routing table storage to minimize network congestion.

## Disclaimer
Ensure compliance with local radio frequency regulations regarding duty cycle and transmission power when deploying this system.

---
**Author:** Viraj  
*Electronics Engineering Undergraduate*
