/*
 * Project: LoRaWAN Disaster Mesh Node
 * Author: Viraj [Last Name]
 * Platform: ESP32 + SX1278
 * Description: Long-range, off-grid telemetry and text communication system.
 */

#include <SPI.h>
#include <LoRa.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <TinyGPS++.h>
#include <HardwareSerial.h>

// --- Pin Definitions ---
#define SCK 18
#define MISO 19
#define MOSI 23
#define SS 5
#define RST 14
#define DIO0 2

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1

#define GPS_RX 16
#define GPS_TX 17

// --- Constants ---
#define BAND 433E6 // 433MHz (Asia/Europe) - Change to 915E6 for Americas
#define NODE_ID "NODE_ALPHA" // Unique ID for this device

// --- Objects ---
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
TinyGPSPlus gps;
HardwareSerial GPS_Serial(2); // Use UART2

// --- Global Variables ---
String outgoing;
byte msgCount = 0;
long lastSendTime = 0;
int interval = 5000; // Send every 5 seconds

void setup() {
  Serial.begin(115200);
  GPS_Serial.begin(9600, SERIAL_8N1, GPS_RX, GPS_TX);

  // Initialize OLED
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(1);
  display.setCursor(0,0);
  display.println("System Booting...");
  display.display();

  // Initialize LoRa
  SPI.begin(SCK, MISO, MOSI, SS);
  LoRa.setPins(SS, RST, DIO0);
  
  if (!LoRa.begin(BAND)) {
    Serial.println("Starting LoRa failed!");
    display.println("LoRa Error!");
    display.display();
    while (1);
  }
  
  // LoRa Configuration for Long Range
  LoRa.setSpreadingFactor(12); // Max range, slower speed
  LoRa.setSignalBandwidth(125E3);
  LoRa.setCodingRate4(5);
  LoRa.setTxPower(20); // Max power (20dBm)
  
  display.println("LoRa Initialized.");
  display.println("Waiting for GPS...");
  display.display();
}

void loop() {
  // 1. Parse GPS Data
  while (GPS_Serial.available() > 0) {
    gps.encode(GPS_Serial.read());
  }

  // 2. Receive Incoming Packets
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    onReceive(packetSize);
  }

  // 3. Broadcast Status (Heartbeat)
  if (millis() - lastSendTime > interval) {
    String message = "ID:" + String(NODE_ID) + ",LOC:";
    
    if (gps.location.isValid()) {
      message += String(gps.location.lat(), 6) + "," + String(gps.location.lng(), 6);
    } else {
      message += "NO_FIX";
    }
    
    sendMessage(message);
    lastSendTime = millis();
    interval = random(4000) + 4000; // Randomize interval to avoid collision
  }
}

void sendMessage(String outgoing) {
  LoRa.beginPacket();
  LoRa.print(outgoing);
  LoRa.endPacket();
  
  Serial.print("Sent: "); Serial.println(outgoing);
  
  // UI Update
  display.clearDisplay();
  display.setCursor(0,0);
  display.println(">> TX SENT");
  display.println(outgoing);
  display.display();
  msgCount++;
}

void onReceive(int packetSize) {
  if (packetSize == 0) return;

  String incoming = "";
  while (LoRa.available()) {
    incoming += (char)LoRa.read();
  }
  
  int rssi = LoRa.packetRssi();
  
  Serial.print("Received: "); Serial.println(incoming);
  Serial.print("RSSI: "); Serial.println(rssi);

  // UI Update
  display.clearDisplay();
  display.setCursor(0,0);
  display.println("<< RX RECEIVED");
  display.println(incoming);
  display.print("Sig: "); display.println(rssi);
  display.display();
}
