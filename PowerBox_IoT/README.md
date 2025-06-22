# PowerBox IoT MVP Version

## Introduction

This MVP version of Technovate PowerBox focuses on basic yet effective energy monitoring using an ESP32 and the PZEM-004T energy meter. It enables real-time tracking of voltage, current, power, and energy consumption. Data is transmitted to an IoT platform (e.g., ThingSpeak or Firebase) for logging and visualization.

## Features

* Real-time voltage, current, power, and energy measurement
* Data transmission via Wi-Fi to IoT backend
* Relay control for switching loads
* Built with PlatformIO for modular and maintainable code

## Hardware Components

* **ESP32 Microcontroller**: Main controller for processing and communication
* **PZEM-004T 100A**: For single-phase energy monitoring
* **Relay Module**: For load control
* **RS485 to TTL Converter**: Interface between ESP32 and PZEM
* **AC to DC Converter**: Powers ESP32

## Software Requirements

* PlatformIO (on VSCode)
* Libraries:

  * `ArduinoJson`
  * `PZEM004T`
  * `PubSubClient`
  * `WiFi`

## File Structure

```
PowerBoxIoT/
├── src/
│   └── main.cpp            # Main firmware logic
├── include/                # Header files (if any)
├── lib/                    # Custom or third-party libraries
├── data/                   # Filesystem data (if needed)
├── .vscode/                # VSCode settings
├── platformio.ini          # PlatformIO build config
```

## Getting Started

### 1. Clone the Repository

```bash
git clone https://github.com/your-username/Technovate-PowerBox.git
cd Technovate-PowerBox/PowerBoxIoT
```

### 2. Install PlatformIO

Install [PlatformIO](https://platformio.org/) in Visual Studio Code.

### 3. Open the Project in PlatformIO

Open the folder in VSCode and let PlatformIO load the environment.

### 4. Configure `platformio.ini`

```ini
[env:esp32]
platform = espressif32
board = esp32dev
framework = arduino
upload_speed = 1500000
monitor_speed = 115200
lib_deps =
  ArduinoJson
  PubSubClient
  PZEM004T
```

### 5. Hardware Wiring

* **ESP32 <-> RS485 Module**

  * TX -> RX, RX -> TX
  * GND -> GND
* **RS485 Module <-> PZEM-004T**

  * A -> A
  * B -> B
* **CT**: Wrap around the live or neutral wire
* **Power**: Power PZEM from mains, ESP32 from DC supply

### 6. Upload Firmware

```bash
pio run --target upload
```

### 7. Monitor Data

```bash
pio device monitor
```

You should see live readings of voltage, current, power, and energy.

## Troubleshooting

* **No data?** Check RS485 wiring and PZEM power.
* **Wrong readings?** Ensure CT is placed correctly.
* **No Wi-Fi?** Confirm credentials in code.

## License

MIT License
