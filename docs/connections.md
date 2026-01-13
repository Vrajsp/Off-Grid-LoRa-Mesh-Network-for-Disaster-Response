## 📡 Project 3: Off-Grid LoRa Mesh Node
**Controller:** ESP32-WROOM-32  
**Radio:** Ai-Thinker Ra-02 (SX1278)  
**GPS:** NEO-6M  
**Display:** 0.96" OLED (I2C)

### 1. LoRa Module (SPI Interface)
*Warning: SX1278 is strictly 3.3V. Do not connect VCC to 5V.*



| LoRa (Ra-02) Pin | ESP32 Pin | Function |
| :--- | :--- | :--- |
| **3.3V** | 3V3 | Power |
| **GND** | GND | Ground |
| **MISO** | GPIO 19 | SPI Master In Slave Out |
| **MOSI** | GPIO 23 | SPI Master Out Slave In |
| **SCK** | GPIO 18 | SPI Clock |
| **NSS (CS)** | GPIO 5 | Chip Select |
| **RST** | GPIO 14 | Reset |
| **DIO0** | GPIO 2 | IRQ (Interrupt Request) |

### 2. GPS Module (UART Serial)
*Note: UART connections are always "Crossed" (TX to RX).*

| NEO-6M Pin | ESP32 Pin | Function |
| :--- | :--- | :--- |
| **VCC** | 3V3 or 5V | Check module spec (usually 3.3V-5V OK) |
| **GND** | GND | Ground |
| **RX** | GPIO 17 (TX2) | ESP32 sends commands to GPS |
| **TX** | GPIO 16 (RX2) | GPS sends coordinates to ESP32 |

### 3. OLED Display (I2C)
| OLED Pin | ESP32 Pin | Function |
| :--- | :--- | :--- |
| **VCC** | 3V3 | Power |
| **GND** | GND | Ground |
| **SCL** | GPIO 22 | Shared I2C Clock |
| **SDA** | GPIO 21 | Shared I2C Data |

---
**Document Version:** 1.0  
**Generated for:** Viraj
