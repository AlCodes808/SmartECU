# AUTOSAR Vehicle Safety Monitor

A real-time automotive safety monitoring system demonstrating AUTOSAR (AUTomotive Open System ARchitecture) Runtime Environment (RTE) principles for embedded systems.

## Project Overview

This project simulates a vehicle safety monitoring system that processes sensor data and triggers alerts based on predefined safety thresholds. It demonstrates proper AUTOSAR layering, component separation, and real-time data processing.

## Architecture

### AUTOSAR Layers
```
┌─────────────────────────────────────┐
│     Application Layer               │
│  (DataProcessor, Alert Logic)       │
├─────────────────────────────────────┤
│     Runtime Environment (RTE)       │
│  (Component Communication)          │
├─────────────────────────────────────┤
│     Basic Software (BSW)            │
│  (SensorReader, DataLogger)         │
└─────────────────────────────────────┘
```

### Component Diagram
```
SensorReader ──> RTE ──> DataProcessor ──> RTE ──> Display/Logger
     │                        │
     └── Generates ───────────┴── Processes & Alerts
         Random Data              Based on Rules
```

## Features

- **Multi-Condition Alert System**
  - High Speed Warning (>150 km/h)
  - Collision Risk Detection (<10m distance)
  - Overheating Alert (>35°C)
  - Critical Danger Combo (high speed + close distance)

- **Real-Time Monitoring**
  - Color-coded console output
  - Severity-based alert indicators
  - 1-second update interval

- **Data Logging**
  - CSV file logging with timestamps
  - Alert history tracking
  - Persistent storage across sessions

- **Statistics & Analytics**
  - Session summaries
  - Min/Max/Average calculations
  - Alert rate tracking

## Getting Started

### Prerequisites
- GCC compiler (MinGW for Windows)
- Make utility
- Terminal with ANSI color support

### Building the Project
```bash
# Clone or download the project
cd SmartECU

# Compile
mingw32-make clean
mingw32-make

# Run
./SmartECU.exe
```

### Project Structure
```
SmartECU/
├── include/
│   ├── Rte.h              # Runtime Environment interface
│   ├── SensorReader.h      # Sensor data types and interface
│   ├── DataProcessor.h     # Alert processing logic
│   └── DataLogger.h        # Logging functionality
├── src/
│   ├── main.c              # Main application and RTE implementation
│   ├── SensorReader.c      # Simulated sensor data generation
│   ├── DataProcessor.c     # Alert condition evaluation
│   └── DataLogger.c        # CSV logging implementation
├── Makefile
└── README.md
```

## Sample Output
```
========================================
   AUTOSAR Vehicle Safety Monitor
========================================
Logging to: vehicle_data_log.csv
Press Ctrl+C to stop...

Speed: 76 km/h  Dist: 60 m  Temp:20 C  -->  [OK] Status: NORMAL
Speed:169 km/h  Dist:  9 m  Temp:28 C  -->  [!!!] ALERTS: [HIGH SPEED] [COLLISION RISK] [*** CRITICAL DANGER ***]
Speed:143 km/h  Dist:  8 m  Temp:30 C  -->  [!!!] ALERTS: [COLLISION RISK] [*** CRITICAL DANGER ***]

========================================
           SESSION STATISTICS           
========================================
Total Readings:  12
Total Alerts:    6 (50.0%)

Speed:  Min=1  Max=169  Avg=92 km/h
Temp:   Min=20  Max=33  Avg=26 C
Closest Distance: 2 m
========================================
```

## Alert Thresholds

| Alert Type | Condition | Severity |
|------------|-----------|----------|
| High Speed | Speed > 150 km/h | Warning |
| Collision Risk | Distance < 10m | Warning |
| Overheating | Temperature > 35°C | Warning |
| Critical Danger | Speed > 100 km/h AND Distance < 20m | Critical |

## Data Logging

All sensor readings and alerts are logged to `vehicle_data_log.csv`:
```csv
Timestamp,Speed_kmh,Distance_m,Temperature_C,Alert_Code,Alert_Description
2025-10-31 17:43:23,76,60,20,0,OK
2025-10-31 17:43:26,169,9,28,11,HIGH_SPEED;COLLISION_RISK;CRITICAL_DANGER;
```

## Learning Outcomes

This project demonstrates:
- **AUTOSAR RTE principles** - Component isolation and communication
- **Embedded C programming** - Bit flags, structures, file I/O
- **Real-time systems** - Continuous monitoring and alerting
- **Modular design** - Separation of concerns, reusable components
- **Professional practices** - Logging, statistics, graceful shutdown

## Future Enhancements

- [ ] CAN bus simulation
- [ ] Multiple ECU communication
- [ ] Configurable alert thresholds (runtime config file)
- [ ] Graphical dashboard (web interface)
- [ ] Unit tests with mock sensors
- [ ] MISRA C compliance checking



**Note:** This is a simulation for demonstration purposes. Sensor data is randomly generated to showcase the monitoring and alert system capabilities.
