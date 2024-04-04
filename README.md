# Arduino Mega and ESP32 IoT Project

This project demonstrates how to use an Arduino Mega board with a DHT22 sensor, a soil moisture sensor, and a water flow sensor to monitor environmental conditions. The data is then sent to the Blynk app using an ESP32 board as a bridge.

## Table of Contents

- [Hardware Setup](#hardware-setup)
- [Software Setup](#software-setup)
- [Usage](#usage)
- [Contributing](#contributing)
- [License](#license)

## Hardware Setup

### Components Required

- Arduino Mega board
- DHT22 sensor
- Soil moisture sensor
- Water flow sensor
- ESP32 board
- Relay module (optional)

### Connections

1. **DHT22 Sensor**: Connect the DHT22 sensor's VCC to the Arduino Mega's 5V, GND to GND, and data pin to digital pin 2.
2. **Soil Moisture Sensor**: Connect the sensor's VCC to the Arduino Mega's 5V, GND to GND, and analog output to analog pin A0.
3. **Water Flow Sensor**: Connect the sensor's VCC to the Arduino Mega's 5V, GND to GND, and digital output to digital pin 3.
4. **Relay Module**: Connect the relay's VCC to the Arduino Mega's 5V, GND to GND, and IN pin to digital pin 4.
5. **ESP32 Board**: Connect the ESP32 board to the Arduino Mega via USB for serial communication.

## Software Setup

### Arduino IDE

1. Install the DHT sensor library for Arduino.
2. Upload the Arduino Mega code to the board.
3. Upload the ESP32 code to the ESP32 board.

### Blynk App

1. Create a new project in the Blynk app.
2. Add widgets for soil moisture, humidity, temperature, and water flow rate.
3. Note the Auth Token provided by Blynk for your project.

## Usage

1. Ensure the ESP32 board is connected to the internet.
2. Open the Blynk app and check the widgets for real-time data.
3. (Optional) Adjust the relay module based on soil moisture levels.

## Contributing

Contributions are welcome! Please read the [contributing guidelines](CONTRIBUTING.md) before getting started.

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.
