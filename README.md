# ESP32 SmartWatch & Pentest Tool

A modular ESP32-based Smart Watch project that combines daily utility features with cybersecurity penetration testing capabilities.

## 🚀 Features

### ⌚ Smart Watch Mode
- **Time & Date Display**: Synchronizes automatically via NTP when connected to WiFi.
- **Connectivity Status**: Monitor WiFi connection state.
- **Modular Design**: Extensible architecture for easy addition of new apps.

### 🎣 Phishing Portal
- **Captive Portal**: Creates an open WiFi Access Point ("Free_WiFi").
- **Credential Harvesting**: Simulates a login page (e.g., Google) to capture credentials for educational/testing purposes.
- **Victim Management**: Displays captured credentials on the OLED screen.

### ⚔️ WiFi Attacks
- **Network Scanner**: Scans and lists available WiFi networks with RSSI signal strength.
- **Deauthentication Attack**: Sends deauth frames to disconnect clients from a target AP.
- **Beacon Spam**: Floods the airwaves with fake Access Points.

### 📡 NRF24L01 Support
- **Spectrum Analyzer**: Visualizes 2.4GHz spectrum activity (requires NRF24L01+ module).
- **Sniffer**: (Future) Packet sniffing capabilities.

## 🖨️ 3D Case
The project includes a 3D printable case design.
- Check the [3d_models](./3d_models) directory for STL files.
- Recommended material: PLA/PETG.

## 🛠 Hardware Architecture

| Component | ESP32 Pin | Description |
|-----------|-----------|-------------|
| **OLED (I2C)** | SDA: 21, SCL: 22 | SSD1306 128x64 Display |
| **Button UP** | GPIO 13 | Navigate Menu Up |
| **Button DOWN** | GPIO 14 | Navigate Menu Down |
| **Button SELECT** | GPIO 12 | Select / Enter |
| **Potentiometer** | GPIO 34 | Optional Scroll/Back |
| **NRF24 CE** | GPIO 4 | Chip Enable |
| **NRF24 CSN** | GPIO 5 | SPI Chip Select |
| **NRF24 SPI** | 18, 19, 23 | SCK, MISO, MOSI |

## 📦 Installation

1.  **Clone the repository**:
    ```bash
    git clone <repository_url>
    ```
2.  **Open in PlatformIO**:
    - Open Visual Studio Code.
    - Install the **PlatformIO** extension.
    - Open the project folder.
3.  **Build & Upload**:
    - Connect your ESP32 via USB.
    - Click the **PlatformIO Upload** button (Arrow icon).

## 🎮 Usage

- **Boot**: The device starts in **Watch Mode**.
- **Navigation**:
    - Press **SELECT** to open the **Main Menu**.
    - Use **UP/DOWN** to scroll through modes.
    - Press **SELECT** to enter a mode.
- **Exiting Modes**:
    - Most modes return to the menu with a specific button combo (usually Long Press SELECT or Potentiometer < 5%).

## ⚠️ Disclaimer

This project is for **EDUCATIONAL PURPOSES ONLY**. Using the attack features (Deauth, Phishing) on networks you do not own or have permission to test is illegal and punishable by law. The authors assume no liability for misuse of this software.