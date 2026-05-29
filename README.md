# EchoMapScout – Hazard Detection & Rescue Rover

## Overview

EchoMapScout is an IoT-based rescue and hazard detection robot designed for operation in hazardous and GPS-denied environments such as collapsed buildings, industrial accident zones, and smoke-filled areas.

The system enables remote monitoring and navigation using:

* ESP32 microcontroller
* ESP32-CAM live video streaming
* MQ2 gas sensor
* Web dashboard interface
* Blynk IoT control system

The robot helps reduce direct human exposure to dangerous environments during rescue and inspection operations.

---

# Problem Statement

Rescue teams operating in disaster environments often face:

* Poor visibility
* Toxic gas leakage
* Fire hazards
* Unstable terrain
* Limited environmental awareness

Manual exploration in such conditions is risky and time-consuming. EchoMapScout addresses this problem by providing a remotely operated robotic inspection system for hazardous areas.

---

# Features

* Remote robot movement control
* Real-time gas monitoring
* ESP32-CAM live video streaming
* Web dashboard for monitoring and control
* Blynk mobile app integration
* Wi-Fi based communication
* REST API based robot commands

---

# Hardware Components

| Component    | Purpose              |
| ------------ | -------------------- |
| ESP32        | Main controller      |
| ESP32-CAM    | Live video streaming |
| MQ2 Sensor   | Gas detection        |
| Motor Driver | Motor control        |
| DC Motors    | Robot movement       |
| Battery Pack | Power supply         |

---

# Technologies Used

* Embedded C++
* Arduino IDE
* HTML
* CSS
* JavaScript
* Blynk IoT

---

# Dashboard Features

* Live camera feed
* Gas sensor monitoring
* Robot movement controls
* System status display
* Responsive UI interface

---

# API Endpoints

| Endpoint  | Function            |
| --------- | ------------------- |
| /forward  | Move forward        |
| /backward | Move backward       |
| /left     | Turn left           |
| /right    | Turn right          |
| /stop     | Stop robot          |
| /gas      | Get gas sensor data |


---

# Future Improvements

* Obstacle avoidance
* Autonomous navigation
* IMU-based path mapping
* Smart Return-to-Home system
* Hazard map generation
* Thermal camera integration



