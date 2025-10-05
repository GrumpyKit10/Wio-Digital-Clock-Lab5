# Wio Terminal Digital Clock (Lab 5)

CSCE 3612 - Embedded Systems Design  
Spring 2022 | Lab #5  

## Overview
This project implements a digital clock using the Wio Terminal development board.  
It leverages the onboard LCD display, push buttons, LED, buzzer, and 3-axis accelerometer.  
The lab demonstrates embedded systems design concepts such as interrupt-based inputs, event-driven timing, and sensor-based power saving.

## Features
- Digital clock displayed in **HH:MM:SS** format (24-hour military time).
- LCD initialized with:
  - Green background
  - Black text
  - Text size 6
- Blue LED blinks quickly on every second tick.
- Push button controls:
  - **WIO_KEY_B** → Increment hour (rolls over at 23 → 00).
  - **WIO_KEY_A** → Increment minute (rolls over at 59 → 00).
  - Both inputs use interrupts (no polling or delay loops).
- Beep tone generated when hours or minutes are adjusted.
- Power-saving mode:
  - LCD backlight turns off when device is stationary for 5 seconds.
  - Backlight turns back on when tilted to ~45°.

## Requirements
- Wio Terminal board
- Arduino IDE or PlatformIO
- Required libraries:
  - [Seeed_Arduino_LIS3DHTR](https://github.com/Seeed-Studio/Seeed_Arduino_LIS3DHTR) (accelerometer)
  - Seeed Wio Terminal board support package

## Usage
1. Clone this repository:
2. Open the project in Arduino IDE or PlatformIO.
3. Install required libraries.
4. Upload code to the Wio Terminal.
5. Demonstrate functionality per lab requirements.

---
**Author:** Matthew Wilson  
**Course:** CSCE 3612 - Embedded Systems Design  
**Lab:** #5 Digital Clock with Wio Terminal  

