# Hardware

**Status: board decision pending.** Nothing here has been ordered or built, and nothing in this folder has been tested on real hardware.

## Candidates being considered

| Option | Idea | Open questions |
|---|---|---|
| UKMARSBOT main board + a Nano-format ESP32-S3 | Drop-in processor swap (the UKMARS project says an ESP32-S3 Nano fits the socket) | Price and stock in India; voltage levels (ESP32 pins are 3.3 V only) |
| UKMARSBOT main board + adapter for a plain ESP32 DevKit | Cheapest, but needs a small adapter, a 5 V supply and level dividers | Exact socket pinout, which signals are 5 V (needs the schematic) |
| Perfboard build with a plain ESP32 | Flexible, no PCB needed to start | More wiring work |

## Draft pin maps

[`pin-maps/`](pin-maps/) holds two **unverified drafts** (one for a Nano-format ESP32-S3, one for a plain ESP32 DevKit).
They are derived from the UKMARSBOT wiki pin page (2019) and must be checked against the schematic of the exact board version before use.

## Parts plan (to be confirmed)

2x N20 gearmotor with encoder, TB6612FNG or DRV8833 driver, IR emitters and phototransistors, a gyro (IMU) module, 2S LiPo with protection and a balance charger, wheels and tyres.
