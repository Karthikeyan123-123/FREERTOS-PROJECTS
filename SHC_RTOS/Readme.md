
<img width="1600" height="1082" alt="WhatsApp Image 2026-08-07 at 10 40 21 AM" src="https://github.com/user-attachments/assets/7e6fdfe8-67df-4dc6-971e-1dfe092a8888" />


# 🏠 Smart Home Controller using FreeRTOS on STM32 Black Pill

A real-time Smart Home Controller developed using **STM32 Black Pill (STM32F401CCU6)** and **FreeRTOS**. This project demonstrates how multiple FreeRTOS features work together to build a complete embedded application similar to those used in industrial and IoT systems.

---

## 📖 Project Overview

The Smart Home Controller monitors different home sensors and controls appliances in real time using FreeRTOS tasks and synchronization mechanisms.

The project is designed to demonstrate practical usage of:

- FreeRTOS Tasks
- Queues
- Task Notifications
- Event Groups
- Mutexes
- Software Timers
- STM32 HAL Drivers

---

## 🎯 Objectives

- Learn real-time multitasking using FreeRTOS.
- Separate sensor acquisition, decision making, and output control.
- Demonstrate communication between multiple tasks.
- Protect shared resources using Mutex.
- Implement interrupt-driven event handling.
- Build a scalable embedded application architecture.

---

# 🛠 Hardware Used

| Component | Description |
|-----------|-------------|
| STM32 Black Pill | STM32F401CCU6 Development Board |
| Motion Sensor | PIR Motion Sensor |
| Door Sensor | Push Button / Magnetic Switch |
| Temperature Sensor | LM35 (or simulated ADC input) |
| LED | Light Indicator |
| LED | Alarm Indicator |
| UART | Serial Debug Output |

---

# 📂 Project Architecture

```
                    Motion Sensor (EXTI)
                           │
                           ▼
                  Task Notification
                           │
                           ▼
                     Motion Task
                           │
                           ▼
                  Reset Software Timer
                           │
                           ▼
                    Light Control

-------------------------------------------------------

Door Sensor
      │
      ▼
 Event Group
      │
      ▼
 Security Task
      │
      ▼
 Alarm LED

-------------------------------------------------------

Temperature Sensor
       │
       ▼
 Temperature Task
       │
       ▼
 Queue
       │
       ▼
 LCD / Display Task

-------------------------------------------------------

All Tasks
     │
     ▼
 UART Mutex
     │
     ▼
 UART Logger
```

---

# ⚙ FreeRTOS Features Used

| Feature | Purpose |
|----------|----------|
| Tasks | Concurrent execution of application modules |
| Queue | Transfer temperature data between tasks |
| Task Notification | Motion sensor interrupt to Motion Task |
| Event Group | Door security events |
| Mutex | Protect UART from simultaneous access |
| Software Timer | Automatic Light OFF timer |

---

# 📋 Tasks

## Motion Task

- Waits for notification from motion sensor interrupt.
- Turns ON room light.
- Resets Auto-OFF timer.

---

## Temperature Task

- Reads temperature periodically.
- Sends data to Queue.

---

## Display Task

- Receives temperature from Queue.
- Updates LCD / Display.

---

## Security Task

- Waits for Door Open Event.
- Turns ON alarm LED.

---

## Logger Task

- Prints system status using UART.
- Uses Mutex to protect UART.

---

# 🔄 Application Flow

### Motion Detection

```
Motion Sensor

↓

EXTI Interrupt

↓

Task Notification

↓

Motion Task

↓

Light ON

↓

Reset Software Timer
```

---

### Automatic Light OFF

```
No Motion

↓

Software Timer Expired

↓

Timer Callback

↓

Light OFF
```

---

### Temperature Monitoring

```
Temperature Sensor

↓

Temperature Task

↓

Queue

↓

Display Task

↓

LCD Update
```

---

### Door Security

```
Door Open

↓

Event Group

↓

Security Task

↓

Alarm ON
```

---

### UART Logging

```
Any Task

↓

UART Mutex

↓

UART Transmission
```

---

# 📁 Project Structure

```
Core
│
├── Inc
│
├── Src
│     ├── main.c
│     ├── freertos.c
│     ├── stm32f4xx_it.c
│
├── Drivers
│
├── Middlewares
│     └── FreeRTOS
│
└── README.md
```

---

# 🚀 Features

- Multi-tasking using FreeRTOS
- Event-driven architecture
- Interrupt-based motion detection
- Automatic light timeout
- Door security monitoring
- UART logging
- Modular software design
- STM32 HAL Driver based

---

# 🔧 Software Requirements

- STM32CubeIDE
- STM32CubeMX
- STM32 HAL Drivers
- FreeRTOS
- ST-Link Programmer

---

# 🎓 Concepts Demonstrated

- Task Creation
- Task Scheduling
- Blocking and Ready States
- Queue Communication
- Task Notifications
- Event Groups
- Mutex Synchronization
- Software Timers
- Interrupt Handling
- Resource Protection

---

# 📸 Project Demo

Add your project images here.

Example:

```
README.md
Images/
    SmartHomeController.jpg
```

Then include:

```md
![Smart Home Controller](Images/SmartHomeController.jpg)
```

---

# 📈 Future Improvements

- OLED/LCD User Interface
- Wi-Fi Connectivity (ESP8266 / ESP32)
- MQTT Communication
- Mobile App Control
- Cloud Monitoring
- SD Card Data Logging
- RTC Integration
- EEPROM Configuration Storage

---

# 👨‍💻 Developed By

**Karthikeyan M**

Embedded Systems Engineer

---

# 📜 License

This project is developed for educational and learning purposes.
