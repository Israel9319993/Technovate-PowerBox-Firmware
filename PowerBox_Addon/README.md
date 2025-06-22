# PowerBox Add-on Module

## Introduction
This version of PowerBox is designed to act as an add-on to existing **Cyclenpo JDK inverters**. It integrates Technovate's PAYU and IoT monitoring system with the user's current inverter setup, enabling smart energy tracking, remote control, and prepaid energy management.

## Features
- **IoT Add-on for Existing Inverters**
- **Bluetooth and Wi-Fi Connectivity**
- **PAYU (Pay-As-You-Use) Integration**
- **Real-time Monitoring via ESP32**

## Hardware Components
- ESP32 Microcontroller
- RS485 to TTL Converter (if applicable)
- Relay Module
- LEDs for status indication
- Power supply module

## Software Requirements
- PlatformIO with Arduino framework
- BluetoothSerial, ArduinoJson, PubSubClient, Firebase libraries

## Project Structure
- `src/` - Source code for the ESP32 add-on
- `platformio.ini` - Configuration for PlatformIO build

## Setup Instructions
1. Clone the repo and navigate to the `PowerBox_Addon` folder.
2. Open with VSCode + PlatformIO.
3. Wire your ESP32 according to the schematics.
4. Upload the firmware.
5. Use the mobile app to connect via Bluetooth and configure your usage.

## License
MIT License