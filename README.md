# Technovate-PowerBox
PowerBox is a modular, pay-as-you-use solar energy system designed to provide clean, affordable, and reliable power to off-grid and underserved communities. This project includes firmware for ESP32-based control units, IoT integration, energy monitoring, and mobile app connectivity.
---

## Project Structure

| Folder            | Description |
|-------------------|-------------|
| `PowerBox_Addon/` | Add-on firmware designed to integrate Technovate's IoT and PAYU system with existing **Cyclenpo JDK inverters**. Ideal for customers who already own an inverter. |
| `PowerBox_IoT/`   | The MVP version that includes basic IoT functionality, energy monitoring, and server communication using ESP32. |
| `PowerBox_Main/`  | The latest full-featured version of PowerBox with advanced energy management, ESP-NOW node communication, PAYU integration, and remote monitoring support. |

---

## Core Features

- Real-time energy monitoring (voltage, current, power, usage)
- Pay-As-You-Use (PAYU) integration for prepaid billing
- Remote control via Bluetooth, Wi-Fi, or ESP-NOW
- Integration with ThingSpeak, MQTT, or Firebase
- Modular design for standalone or add-on deployments

---

## 🔋 Hardware Specifications (Latest Deployment)

- **Inverter**: 5.5kW Hybrid Inverter  
- **Battery**: 7.5kWh LiFePO4  
- **Solar Panels**: 7 × 550W 48V  
- **Location**: Eleko, Lagos State, Nigeria  
- **Integration**: IoT + Cyclenpo JDK Inverter

---

## 🚀 Getting Started

### Clone the Repository

```bash
git clone https://github.com/Israel9319993/Technovate-PowerBox.git
cd Technovate-PowerBox
Choose a Version to Deploy
bash
Copy
Edit
cd PowerBox_Addon   # Add-on for existing inverters
cd PowerBox_IoT     # MVP version with basic IoT
cd PowerBox_Main    # Full-featured PowerBox version
Upload code to your ESP32 using Arduino IDE or PlatformIO.

🔐 License
This project is licensed under the MIT License.
Feel free to use, modify, and improve!

🤝 Contributing
We welcome contributions!
Feel free to fork the repo, open issues, or submit pull requests to help improve energy access for all.

🌍 About Technovate
Technovate is building smart energy solutions to power communities across Nigeria and beyond — one box at a time.