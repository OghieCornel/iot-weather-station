# IoT-Based Weather Station

## Overview

An IoT-based weather monitoring system designed to collect, transmit, store, and display real-time environmental data. The system measures temperature, humidity, and rainfall using sensors connected to an ESP8266 (NodeMCU) microcontroller and makes the data accessible through a web interface and provides real-time alerts through Whatsapp using the callmebot library. The project focuses on providing a cost-effective and scalable alternative to traditional weather stations, suitable for both urban and rural environments.


![20250222_130809](https://github.com/user-attachments/assets/c53a132e-9469-4e12-bd71-99ae21965048)

## Features

* Real-time monitoring of temperature and humidity
* Rain detection and intensity monitoring
* Wireless data transmission using Wi‑Fi (ESP8266)
* Web-based interface for remote access and monitoring
* Alert notifications for predefined threshold conditions

## System Architecture

The system consists of sensor nodes connected to a NodeMCU ESP8266, which processes and transmits data over a Wi‑Fi network to a web interface for visualization and monitoring.
![weather station circuit diagram_page-0001](https://github.com/user-attachments/assets/c7086644-2be8-4fbb-aba5-55bbb4b395ac)

## Hardware Components

* ESP8266 (NodeMCU) Wi‑Fi Module
* DHT21 Temperature and Humidity Sensor
* YL‑83 Rain Sensor Module
* LM2596 DC‑DC Buck Converter Module
* Step-down Transformer (220V AC to low-voltage AC)
* Perf-board and connecting wires
![20250222_115946](https://github.com/user-attachments/assets/d8db74f4-8993-442d-baa6-0ea739f22c8b)



## Software Components

* Firmware programmed on ESP8266
* Web-based monitoring interface

## Setup and Configuration

1. Activate a hotspot on a PC or smartphone.
2. Configure the hotspot with the necessary credentials:


3. Power on the weather station device.
4. Allow the device to connect to the hotspot and obtain an IP address automatically.
5. Upon successful connection, a notification is sent via WhatsApp.
6. Scan the provided QR code or visit the web interface URL to monitor weather data.

## Usage

* Power on the device and ensure it is connected to the configured Wi‑Fi network.
* Access the web interface to view real-time temperature, humidity, and rainfall data.
* Monitor alerts generated when sensor values exceed defined thresholds.

## Alert Conditions

* High Temperature Alert: Above 45 °C
* Low Temperature Alert: Below 20 °C
* High Humidity Alert: Above 90%
* Rain Sensor Alert: Intensity between 30% and 55%
* Rain Intensity Limit Alert: Above 55%
* Rain Falling Alert: Above 60%

  <img width="677" height="933" alt="iot weather result" src="https://github.com/user-attachments/assets/012f209b-62b7-4ab0-b361-78b67ff7423e" />


## Firmware Upgrade

1. Connect the device to the configured hotspot.
2. Identify the assigned IP address.
3. Open a web browser and navigate to:



<img width="1295" height="141" alt="ip address for weather station" src="https://github.com/user-attachments/assets/8ee86a45-c5b4-4170-bb9d-9835b56b1c22" />

   ```
   http://192.168.137.166/update
   ```
4. Upload the new firmware file.
5. Wait until the progress bar reaches 100% to complete the update.

## Troubleshooting

* Verify all sensor connections and power supply.
* Ensure sensors are correctly placed and functional.
* Confirm Wi‑Fi credentials and network availability.
* Check that the ESP8266 is within Wi‑Fi range.

## Safety Precautions

* Keep the main device away from liquids; only the rain sensor should be exposed to water.
* Avoid extreme temperature and humidity conditions.
* Use a stable and compatible power supply (220–240V, 50/60Hz).
* Handle sensors carefully to prevent damage.


## Institution

Department of Computer Engineering
Faculty of Engineering
Edo University Iyamho

## Supervisor

Engr. Dr. Chukwuemeka .C. Obasi
