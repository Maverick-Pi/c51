# 🚀Puzhong 51-Development Board: STC89C52RC Microcontroller Programming

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT) [![Keil v5](https://img.shields.io/badge/Compiler-Keil_v5-blue)](https://www.keil.com/) [![VSCode](https://img.shields.io/badge/IDE-VSCode+-brightgreen)](https://code.visualstudio.com/) [![STC89C52RC](https://img.shields.io/badge/MCU-STC89C52RC-red)](https://www.stcmcudata.com/) [![Last Commit](https://img.shields.io/github/last-commit/Maverick-Pi/c51)](https://github.com/username/puzhong-51-projects)

> Comprehensive learning and development project for 51 microcontrollers with complete hardware drivers and functional modules



## 📋Project Overview

This project implements various hardware drivers and functional applications based on the STC89C52RC microcontroller development board:

+ **20+ hardware drivers** (sensors, displays, communication protocols)
+ **15+ functional applications** (temperature alarm, adjustable clock, breathing LED)
+ **Multiple communication protocols** (I2C, 1-Wire, IR NEC, UART)
+ **Peripheral control** (LCD1602, LED matrix, nixie tubes, buzzer)

<img src="https://github.com/Maverick-Pi/c51/blob/main/assets/Puzhong51.png?raw=true" style="zoom: 50%;" />



## 🛠️Development Environment

+ **IDE**: VSCode + Embedded IDE extension
+ **Compiler**: Keil μVision v5
+ **Target MCU**: STC89C52RC
+ **Programming Tool**: STC-ISP
+ **Development Board**: Puzhong 51-Development Board



## 📂Project Structure

```text
src/
├── main.c                                  # Main program entry
├── chapters/                               # Functional applications (by chapter)
│	├── ch1_1_light_up_led.c                # Basic LED control
│ 	├── ch1_2_led_flashing.c                # LED flashing
│	├── ch1_3_sequential_led_light.c        # Sequential LED Light
│	├── ch2_1_nixie.c                       # Nixie tube display
│	├── ch3_1_lcd1602.c                     # LCD1602 display
│ 	├── ch4_1_matrix_key_test.c             # Matrix Key
│ 	├── ch5_1_uart_to_pc.c                  # UART communicate to PC
│ 	├── ch5_2_uart_from_pc.c                # PC communicate to MCU by UART
│ 	├── ch6_1_lattice_screen.c              # Lattice Screen display
│ 	├── ch7_1_real_time_clock.c             # Real Time Clock
│ 	├── ch7_2_adjustable_clock.c            # Adjustable Real Time Clock
│	├── ch8_1_buzzer_alert_tone.c           # Buzzer Alert Tone
│	├── ch9_1_at24c02_test.c                # AT24C02 EEPROM Test
│	├── ch9_2_data_storage.c                # Data Storage by AT24C02 EEPROM
│	├── ch9_3_chronograph.c                 # An Inaccurate chronograph
│	├── ch10_1_measure_temperature.c        # Measure Temperature by DS18B20
│	├── ch10_2_temperature_alarm.c          # Temperature Alarm by DS18B20's EEPROM
│	├── ch11_1_led_breathing.c              # LED Breathing by PWM
│ 	├── ch11_2_dc_motor_control.c           # DC Motor control by PWM
│ 	├── ch12_1_analog_digital.c             # Analog convert to Digital
│	├── ch13_1_infrared_remote_control.c    # Infrared Remote Control
│	└── ch13_2_ir_motor.c                   # Infrared Remote Contorl DC Motor
└── modules/                                # Hardware drivers
	├── 74hc595.c                           # 74HC595 Serial to Parallel data conversion
	├── at24c02.c                           # AT24C02 EEPROM Driver
	├── buzzer.c                            # Buzzer Driver
	├── common_type.h                       # Common Type Aliases
	├── delay.c                             # Delay function
	├── ds18b20.c                           # DS18B20 temperature sensor
	├── ds1302.c                            # DS1302 Real-Time Clock
	├── independent_key.c                   # Independent Key Driver
	├── inter_integrated_circuit.c          # I2C Protocol
	├── interrupt.c                         # External Interrupt
	├── IR_NEC.c                            # IR NEC remote protocol
	├── lattice_screen.c                    # Lattice Screen Driver
	├── lcd1602.c                           # LCD1602 display driver
	├── matrix_key.c                        # Matrix Key Driver
	├── motor.c                             # DC Motor Driver
	├── nixie_tube.c                        # Nixie Tube Driver
	├── one_wire.c                          # 1-Wire Protocol
	├── timer.c                             # General Purpose Timer
	├── uart.c                              # UART Communication
	└── xpt2046.c                           # XPT2046 A/D Driver
```



## 🧩Functional Modules

### 🔌Hardware Drivers

| Module             | File                 | Description                                      | Size |
| ------------------ | -------------------- | ------------------------------------------------ | ---- |
| Temperature Sensor | `ds18b20.c/h`        | DS18B20 temperature reading (-55℃~+125℃)         | 5KB  |
| Real-Time Clock    | `ds1302.c/h`         | DS1302 RTC control (year/month/day/hour/min/sec) | 4KB  |
| EEPROM             | `at24c02.c/h`        | AT24C02 data storage (256 bytes)                 | 6KB  |
| Buzzer             | `buzzer.c/h`         | Passive buzzer control (alarms, tones)           | 1KB  |
| IR Remote          | `IR_NEC.c/h`         | NEC protocol decoding (38KHz carrier)            | 6KB  |
| Serial-Parallel    | `74hc595.c/h`        | 74HC595 IO expansion                             | 1KB  |
| LED Matrix         | `lattice_screen.c/h` | 8×8 LED matrix control                           | 1KB  |
| LCD Display        | `lcd1602.c/h`        | LCD1602 character display                        | 5KB  |
| ADC                | `xpt2046.c/h`        | XPT2046 analog-to-digital conversion             | 2KB  |

### 📚Application Chapters

| Chapter            | File                               | Description                                | Size |
| ------------------ | ---------------------------------- | ------------------------------------------ | ---- |
| Temperature Alarm  | `ch10_2_temperature_alarm.c`       | Threshold-based alarm system with LCD      | 12KB |
| Adjustable Clock   | `ch7_2_adjustable_clock.c`         | DS1302 clock interface with key adjustment | 8KB  |
| Breathing LED      | `ch11_1_led_breathing.c`           | PWM dimming effect (brightness gradient)   | 4KB  |
| Motor Control      | `ch11_2_dc_motor_control.c`        | DC motor speed control                     | 2KB  |
| Data Storage       | `ch9_2_data_storage.c`             | EEPROM read/write example                  | 2KB  |
| IR Remote          | `ch13_1_infrared_remote_control.c` | Infrared remote decoding application       | 3KB  |
| UART Communication | `ch5_1_uart_to_pc.c`               | PC-MCU serial communication                | 1KB  |



## ⚡Getting Started

### Hardware Requirements

1.  Puzhong 51-Development Board
2.  STC89C52RC microcontroller
3.  USB-to-Serial module
4.  Required peripherals (DS18B20, LCD1602, etc.)

### Software Setup

1.  Clone repository:

   ```bash
   git clone https://github.com/Maverick-Pi/c51.git
   ```

2.  Open project in VSCode

3.  Install `Embedded IDE` extension

4.  Configure Keil compiler path in VSCode settings

5.  Connect development board

### Compilation and Programming

<img src="https://github.com/Maverick-Pi/c51/blob/main/assets/Compilation.png?raw=true" alt="image-20250724162445702" style="zoom:80%;" />



## 🎥Demo

|        Feature         |              Description               |                            Image                             |
| :--------------------: | :------------------------------------: | :----------------------------------------------------------: |
| Temperature Monitoring | Real-Time display with threshold alarm | <img src="https://github.com/Maverick-Pi/c51/blob/main/assets/Temperature.gif?raw=true" alt="Temperature" style="zoom: 80%;" /> |
|    Adjustable Clock    |    DS1302 RTC with time adjustment     | <img src="https://github.com/Maverick-Pi/c51/blob/main/assets/RTC.gif?raw=true" alt="RTC" style="zoom: 80%;" /> |
|       LED Matrix       |    8×8 matrix pattern/text display     | <img src="https://github.com/Maverick-Pi/c51/blob/main/assets/MatrixLED.gif?raw=true" alt="MatrixLED" style="zoom: 33%;" /> |
|     Breathing LED      |   PWM-controlled brightness gradient   | <img src="https://github.com/Maverick-Pi/c51/blob/main/assets/BreathLight.gif?raw=true" alt="BreathLight" style="zoom: 33%;" /> |



## 🤝Contribution Guidelines

We welcome contributions! Please follow these steps:

1.  Fork the repository

2.  Create feature branch:

   ```bash
   git checkout -b feature/your-feature
   ```

3.  Commit changes:

   ```bash
   git commit -m "feat: add new functionality"
   ```

4.  Push to branch:

   ```bash
   git push origin feature/your-feature
   ```

5.  Open a Pull Request

### Contribution Standards

+ Include complete header documentation for drivers
+ Provide usage examples for new modules
+ Maintain consistent coding style
+ Test new functionality thoroughly



## 📜License

This project is licensed under the MIT License - see [LICENSE](https://github.com/Maverick-Pi/c51/blob/main/LICENSE) for details



> Developed by Maverick Pi · Updated July 2025 · [Project Home](https://github.com/Maverick-Pi/c51)