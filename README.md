# Multi-Sensor Data Acquisition using Nordic Thingy:53

An embedded IoT project that uses the **Nordic Thingy:53** as a sensing platform to
capture live environmental data (temperature, humidity, pressure) and explores a
complete embedded development workflow — from firmware flashing to cloud-based
visualization and power profiling.

Submitted as a BTP project at the **Department of Electrical Engineering, IIT Ropar**,
under the supervision of Dr. Ashwini Sharma.

## Overview

The project uses the Thingy:53's onboard BME688 environmental sensor to continuously
read temperature, humidity, and pressure values. The firmware was built with the
**nRF Connect SDK** (Zephyr-based) and flashed onto the device via the **nRF5340 DK**
used as a programming/debug interface. Beyond firmware-level sensing, the project also
integrates:

- **nRF Connect for Desktop** — for loading firmware and monitoring serial output
- **Edge Impulse** — for cloud-based sensor data visualization and edge ML data collection
- **Power Profiler Kit II (PPK2)** — for measuring the device's current consumption during operation

## Hardware Used

| Component | Purpose |
|---|---|
| Nordic Thingy:53 | Primary sensing platform (nRF5340 SoC, onboard BME688 sensor) |
| nRF5340 DK | Programming and debug interface for flashing firmware to the Thingy:53 |
| Current Measurement Board | Interfaces with the PPK for per-rail current measurement |
| Power Profiler Kit II (PPK2) | Measures real-time current draw of the device |

## Software / Tools Used

- Visual Studio Code + nRF Connect SDK (Zephyr RTOS)
- nRF Connect for Desktop
- Edge Impulse (mobile app + web dashboard)
- SEGGER J-Link (flashing/debugging)

## Repository Structure

```
.
├── src/
│   └── main.c                          # Sensor read + LED status firmware
├── boards/
│   └── thingy53_nrf5340_cpuapp.conf    # Board-specific config overlay
├── CMakeLists.txt                      # Zephyr build configuration
├── prj.conf                            # Project-level Kconfig options
└── README.md
```

## What the Firmware Does

- Initializes the onboard RGB LED (used for status indication)
- Initializes the BME688 environmental sensor
- Continuously samples temperature, humidity, and pressure
- Prints readings to the serial console every 2 seconds
- Blinks green on a successful read, red on a failed sensor fetch

## Workflow

1. **Write & build** the firmware in VS Code using the nRF Connect SDK
2. **Flash** it onto the Thingy:53 through the nRF5340 DK
3. **Monitor output** via serial terminal (both through VS Code's built-in terminal and nRF Connect for Desktop)
4. **Visualize sensor data** on the Edge Impulse dashboard via the mobile app
5. **Profile power consumption** using the PPK2, connected through the current measurement board

## Results

- Verified sensor readings (temperature, humidity, pressure) via serial terminal, using both VS Code and nRF Connect for Desktop
- Visualized environmental, accelerometer, audio, and light sensor data on the Edge Impulse dashboard
- Captured a real-time current consumption graph of the device using the PPK2, reflecting different operational states (idle, sensing, communication)

## Challenges

- Firmware could not be flashed directly over USB — required the nRF5340 DK as a programming/debug interface
- SEGGER J-Link version compatibility issues with nRF Connect for Desktop
- Identifying correct VIN/VOUT/GND pins for PPK current measurement
- Zephyr/nRF Connect SDK project structure and board configuration setup
- Intermittent Bluetooth connectivity issues between the Thingy:53 and the Edge Impulse mobile app

## Conclusion

This project provided hands-on experience with a complete embedded IoT workflow —
firmware development, hardware interfacing, serial communication, cloud-based sensor
monitoring, and power profiling — using the Nordic Thingy:53 as the core sensing platform.
