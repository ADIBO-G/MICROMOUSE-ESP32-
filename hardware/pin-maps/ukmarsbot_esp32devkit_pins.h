// ukmarsbot_esp32devkit_pins.h
// UKMARSBOT roles mapped onto a classic ESP32 DevKit (30 or 38 pin) wired through an adapter.
// The DevKit does NOT fit the Nano socket, so each Nano socket pin is wired to the GPIO below.
//
// GPIO choices follow the usual ESP32 rules:
//   - GPIO 6..11 are used by the flash chip: never use them.
//   - GPIO 34, 35, 36, 39 are input only (good for analog sensors, no pull-up/pull-down).
//   - ADC2 pins stop working when Wi-Fi is on, so analog sensors and the battery use ADC1 pins
//     (32, 33, 34, 35, 36, 39).
//   - Strapping pins 0, 2, 5, 12, 15 affect boot: avoid them for anything important.
//   - GPIO 16 and 17 are used by PSRAM on WROVER modules; fine on the common WROOM DevKit.
//
// STATUS: NOT VERIFIED ON HARDWARE. The roles come from the UKMARSBOT wiki (2019, Arduino Nano).
// Check them against the schematic of your main board version, and check which signals are 5 V
// before connecting them: ESP32 pins are 3.3 V only and are not 5 V tolerant.

#pragma once

// ---- analog inputs (ADC1 only) -----------------------------------------------------------
constexpr int PIN_SENSE_LEFT_SIDE   = 36;  // Nano A0  (VP, input only)
constexpr int PIN_SENSE_RIGHT_FRONT = 39;  // Nano A1  (VN, input only)
constexpr int PIN_SENSE_LEFT_FRONT  = 34;  // Nano A2  (input only)
constexpr int PIN_SENSE_RIGHT_SIDE  = 35;  // Nano A3  (input only)
constexpr int PIN_BATTERY_SENSE     = 32;  // Nano A7  battery divider (keep the divider output below ~3 V)
constexpr int PIN_FUNCTION_SWITCH   = 33;  // Nano A6  function switch resistor ladder
// Nano A4 / A5 (spare sensors) are not used here; the gyro uses I2C below.

// ---- gyro on I2C (default ESP32 pins) ---------------------------------------------------
constexpr int PIN_I2C_SDA = 21;
constexpr int PIN_I2C_SCL = 22;

// ---- encoders (quadrature) ---------------------------------------------------------------
constexpr int PIN_ENC_M1_A = 16;           // Nano D2
constexpr int PIN_ENC_M1_B = 17;           // Nano D4
constexpr int PIN_ENC_M2_A = 18;           // Nano D3
constexpr int PIN_ENC_M2_B = 19;           // Nano D5

// ---- motor driver ------------------------------------------------------------------------
constexpr int PIN_MOTOR_L_DIR = 25;        // Nano D7
constexpr int PIN_MOTOR_R_DIR = 26;        // Nano D8
constexpr int PIN_MOTOR_L_PWM = 27;        // Nano D9
constexpr int PIN_MOTOR_R_PWM = 13;        // Nano D10

// ---- other outputs -----------------------------------------------------------------------
constexpr int PIN_SENSOR_TRIGGER = 23;     // Nano D12  sensor LED (emitter) trigger
constexpr int PIN_LED_SENSOR_1   = 4;      // Nano D6   diagnostic LED on the sensor board
constexpr int PIN_LED_BOARD      = 2;      // Nano D13  on-board LED (GPIO2 is a strapping pin: fine as an LED output)
constexpr int PIN_LED_SENSOR_2   = -1;     // Nano D11  not assigned (add a free pin if you need it)

// ---- control settings used with this board (from Part 4 and Part 5) ---------------------
constexpr int   PWM_FREQUENCY_HZ = 20000;  // above the audible range
constexpr int   ADC_BITS         = 12;     // ESP32 ADC: 0..4095 (noisy: average several samples)
constexpr float CONTROL_DT       = 0.001f; // 1 kHz control loop, run from a hardware timer
