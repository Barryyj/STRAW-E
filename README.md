# STRAW-E

STRAW-E is a simple ESP32-based remote-controlled system. It connects to your WiFi network and allows remote operation through a Python script.

## Installation

### Setup and Upload
1. **Install Arduino IDE** and set up the ESP32 board:
   - Add ESP32 support in Arduino IDE (refer to [ESP32 setup guide](https://docs.espressif.com/projects/arduino-esp32/en/latest/)).
   - Select **ESP32 Dev Module** as the board.
2. **Modify WiFi Credentials:**
   - Open `sketch_mar15b.ino`.
   - Replace `???` with your WiFi name and `???` with your WiFi password:
     ```cpp
     const char* ssid = "YourWiFiName";       // Replace with your WiFi network name
     const char* password = "YourWiFiPassword";   // Replace with your WiFi password
     ```
3. **Upload Code to ESP32:**
   - Compile and upload `sketch_mar15b.ino` to your ESP32.
4. **Find the Device's IP Address:**
   - Open the Serial Monitor in Arduino IDE.
   - Once connected to WiFi, the ESP32 will print its IP address.

## Running the Remote Control Script
1. **Install dependencies:**
   ```sh
   pip install keyboard requests
   ```
2. **Run the script in the same network as the ESP32:**
   ```sh
   python remote_control.py
   ```
   Make sure your computer and ESP32 are on the same network.
3. **Adjusting Controls:**
   - The current control implementation is janky, you may have to press the buttons multiple times, but you can easily modify `remote_control.py` to your liking.

