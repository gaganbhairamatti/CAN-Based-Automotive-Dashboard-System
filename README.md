# CAN-Based Automotive Dashboard System

A multi-ECU embedded automotive project developed using the **PIC18F4580 microcontroller** and **CAN (Controller Area Network) communication protocol** to simulate real-time vehicle dashboard monitoring and control.

This project demonstrates **inter-ECU communication**, **sensor data processing**, **dashboard visualization**, and **indicator control**, closely reflecting real automotive Electronic Control Unit (ECU) architecture.

---

## Project Overview

The system is divided into **three independent ECUs**, each responsible for specific vehicle functions.

* **ECU1 – Speed and Gear Control Node**
* **ECU2 – RPM and Indicator Control Node**
* **ECU3 – Central Dashboard Display Node**

All ECUs communicate through the **CAN bus** using unique message identifiers.

---

## System Architecture

ECU1 and ECU2 act as data source nodes, while ECU3 acts as the central dashboard receiver and display node.

```text id="xt4m2n"
ECU1 --------\
              \
               --> CAN BUS --> ECU3 Dashboard
              /
ECU2 --------/
```

---

## ECU1 – Speed and Gear Sensor Node

ECU1 is responsible for reading vehicle speed and gear position and transmitting the data over CAN.

### Features

* ADC-based speed sensing
* Matrix keypad-based gear selection
* Local CLCD display
* CAN transmission of:

  * Speed
  * Gear position

### Message IDs

* `0x10` → Speed
* `0x20` → Gear

### Functional Modules

* ADC Driver
* Matrix Keypad Driver
* CLCD Driver
* CAN Driver

---

## ECU2 – RPM and Indicator Control Node

ECU2 handles engine RPM monitoring and left/right indicator control.

### Features

* ADC-based RPM sensing
* SSD (7-segment display) RPM visualization
* Digital keypad switch input
* Indicator LED control
* CAN transmission of:

  * RPM
  * Indicator status

### Message IDs

* `0x30` → RPM
* `0x50` → Indicator

### Functional Modules

* ADC Driver
* SSD Display Driver
* Digital Keypad Driver
* CAN Driver

---

## ECU3 – Central Dashboard Display Node

ECU3 acts as the **central instrument cluster controller**.

It receives data from ECU1 and ECU2 through the CAN bus and updates the dashboard display in real time.

### Features

* Receives CAN frames from all ECUs
* Displays:

  * Speed
  * Gear
  * RPM
  * Indicator status
* Timer interrupt-based blinking indicator LEDs
* CLCD dashboard visualization

### Dashboard Output

```text id="lg2m7v"
SP  GR   RPM   IND
45  G3   2500  <-
```

### Functional Modules

* CAN Driver
* CLCD Driver
* Timer0 Driver
* Interrupt Service Routine (ISR)
* Message Handler

---

## Technologies Used

* **Microcontroller:** PIC18F4580
* **Programming Language:** Embedded C
* **IDE:** MPLAB X IDE
* **Compiler:** XC8
* **Communication Protocol:** CAN
* **Clock Frequency:** 20 MHz

---

## CAN Communication Details

### Standard Message IDs

| Parameter          | Message ID |
| ------------------ | ---------- |
| Speed              | `0x10`     |
| Gear               | `0x20`     |
| RPM                | `0x30`     |
| Engine Temperature | `0x40`     |
| Indicator          | `0x50`     |

---

## Key Embedded Concepts Used

* ADC
* CAN Protocol
* Interrupt Handling
* Timer0
* CLCD Interfacing
* SSD Multiplexing
* Matrix Keypad Scanning
* Digital Input Processing
* Real-Time Embedded Design

---

## Learning Outcomes

This project helped in understanding:

* Multi-node CAN communication
* ECU-based modular firmware design
* Real-time interrupt-driven control
* automotive dashboard system architecture
* driver abstraction in embedded systems

---

## Future Improvements

* Engine temperature display
* interrupt-based CAN receive
* fault diagnostics and error frames
* warning indicators
* buzzer alerts
* CAN bus monitoring and debugging support

---

## Author

**Gagan Bhairamatti**  
