// ukmarsbot_esp32_pins.h
// UKMARSBOT (standard, Arduino Nano socket) pin roles mapped onto a Nano-format ESP32-S3 board
// (Arduino Nano ESP32 / Waveshare ESP32-S3-Nano). Values are GPIO numbers, so they work with the
// "GPIO number" pin scheme of the ESP32 Arduino core.
//
// Sources: the UKMARSBOT wiki "Pin Assignments" page (2019, roles for an Arduino Nano) and the
// Arduino Nano ESP32 pin map (Nano pin name -> ESP32-S3 GPIO).
//
// STATUS: NOT VERIFIED ON HARDWARE. The roles come from an older wiki page and your board version
// may differ. Check every line against the schematic of YOUR main board before powering anything.
// Also check signal voltages: the ESP32-S3 is 3.3 V and its pins are not 5 V tolerant.

#pragma once

// ---- analog inputs (Nano A0..A7) ---------------------------------------------------------
constexpr int PIN_SENSE_LEFT_SIDE  = 1;   // A0  left side wall sensor         (ADC1)
constexpr int PIN_SENSE_RIGHT_FRONT= 2;   // A1  right front sensor            (ADC1)
constexpr int PIN_SENSE_LEFT_FRONT = 3;   // A2  left front sensor             (ADC1) GPIO3 is a strapping pin: check at boot
constexpr int PIN_SENSE_RIGHT_SIDE = 4;   // A3  right side wall sensor        (ADC1)
constexpr int PIN_SENS_SPARE_1     = 11;  // A4  spare sensor input 1          (ADC2) also the I2C SDA pin on Nano boards (verify)
constexpr int PIN_SENS_SPARE_2     = 12;  // A5  spare sensor input 2          (ADC2) also the I2C SCL pin on Nano boards (verify)
constexpr int PIN_FUNCTION_SWITCH  = 13;  // A6  function switch (resistor ladder) (ADC2)
constexpr int PIN_BATTERY_SENSE    = 14;  // A7  battery voltage divider       (ADC2: not usable while Wi-Fi is on)

// ---- serial -------------------------------------------------------------------------------
constexpr int PIN_UART_RX = 44;           // D0
constexpr int PIN_UART_TX = 43;           // D1

// ---- encoders (quadrature, A and B per motor) --------------------------------------------
constexpr int PIN_ENC_M1_A = 5;           // D2  motor 1 encoder channel 1 (interrupt pin on the Nano)
constexpr int PIN_ENC_M1_B = 7;           // D4  motor 1 encoder channel 2
constexpr int PIN_ENC_M2_A = 6;           // D3  motor 2 encoder channel 1 (interrupt pin on the Nano)
constexpr int PIN_ENC_M2_B = 8;           // D5  motor 2 encoder channel 2

// ---- outputs ------------------------------------------------------------------------------
constexpr int PIN_LED_SENSOR_1  = 9;      // D6  diagnostic LED on the sensor board
constexpr int PIN_MOTOR_L_DIR   = 10;     // D7  left motor direction
constexpr int PIN_MOTOR_R_DIR   = 17;     // D8  right motor direction
constexpr int PIN_MOTOR_L_PWM   = 18;     // D9  left motor PWM
constexpr int PIN_MOTOR_R_PWM   = 21;     // D10 right motor PWM
constexpr int PIN_LED_SENSOR_2  = 38;     // D11 second diagnostic LED on the sensor board
constexpr int PIN_SENSOR_TRIGGER= 47;     // D12 trigger for the sensor LEDs (emitters)
constexpr int PIN_LED_BOARD     = 48;     // D13 external LED

// ---- control settings used with this board (from Part 4 and Part 5) -----------------------
constexpr int   PWM_FREQUENCY_HZ = 20000; // above the audible range
constexpr int   ADC_BITS         = 12;    // ESP32-S3 ADC: 0..4095 (the Nano's ADC was 10-bit, 0..1023)
constexpr float CONTROL_DT       = 0.001f;// 1 kHz control loop, run from a hardware timer
