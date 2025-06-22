# PowerBox Main Version (Full Implementation)

## Introduction
This is the latest and most complete version of Technovate PowerBox. It integrates all features from previous versions including PAYU, ESP-NOW node communication, multi-socket monitoring, and IoT backend support.

## Features
- Multi-socket energy monitoring (Socket 1 & 2)
- ESP-NOW based communication between nodes and central hub
- PAYU logic with top-up & credit validation
- Data logging to ThingSpeak and mobile app integration

## Hardware Components
- ESP32 Microcontrollers (for nodes and hub)
- PZEM-004T for each socket
- Relay Modules
- LEDs for status
- AC-DC Converter
- PC817, BC547 for signal control

## Software Requirements
- PlatformIO (Arduino)
- Libraries: ESPNow, ArduinoJson, PZEM004T, PubSubClient

## Project Structure
- `src/` - All core logic for hub and node firmware
- `platformio.ini` - PlatformIO config

## Setup Instructions
1. Clone and open the `PowerBox_Main` folder.
2. Connect and wire all hardware as designed.
3. Flash each ESP32 with the appropriate firmware (hub vs node).
4. Connect to Wi-Fi and ThingSpeak.

## License
MIT License