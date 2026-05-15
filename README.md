# Satellite Telemetry Transmitter - ESP32 Heltec V4

Real-time RF telemetry transmitter built on the Heltec WiFi LoRa 32 V4

## Overview
A PIO embedded systems project implementing a Finite State Machine 
architecture with the State Design Pattern to manage RF transmission, 
OLED display output, and hardware I/O on the ESP32-S3.

Built to transmit live signal data (RSSI) over LoRa to a CLI receiver, 
with a user-controlled start/stop interface via onboard hardware button.

## Hardware
- Heltec WiFi LoRa 32 V4 (ESP32-S3)
- Onboard SX1262 LoRa radio
- 128x64 OLED display
- Onboard RGB LED + USR button


## Architecture

### FSM State Model
   
<img width="420" height="300" alt="fsm" src="https://github.com/user-attachments/assets/ef913d4a-8844-45aa-be83-d1ac48c86453" />
  
### Class Design
| Class | Responsibility |
|---|---|
| `SystemController` | FSM orchestrator, owns all subsystems |
| `LEDController` | GPIO LED abstraction |
| `OLEDController` | Display rendering, wraps heltec_unofficial |
| `RFController` | LoRa radio abstraction, RSSI reads |

### Key Design Decisions
- `heltec_unofficial.h` included in exactly one translation unit (`main.cpp`) 
  to avoid multiple definition linker errors: solved with `extern` forward declaration
- `millis()` based update gate in RUNNING state prevents OLED heap fragmentation 
  from high-frequency `String` allocations
- Button input uses falling-edge detection with debounce rather than polling state, 
  keeping FSM event handling clean

### Planned
- [ ] GPS telemetry drivers (SFSM branch)
- [ ] LoRa packet transmission to CLI receiver
- [ ] WebSocket bridge for live dashboard
- [ ] Temperature + battery sensor integration
\```

## Related
- [C++ Satellite Telemetry Simulator](https://github.com/adamkimmins/satellite-telemetry-simulator) — the WSL2/desktop simulator
