#ifndef PIN_DEFINES_H
#define PIN_DEFINES_H
#include "driver/gpio.h"
// ======================================================
// GPIO Assignment
// https://docs.espressif.com/projects/esp-idf/en/v6.0.1/esp32s3/api-reference/peripherals/gpio.html
// ======================================================

// -------------------- Encoder -------------------------
#define PIN_ENCODER_CLK GPIO_NUM_1
#define PIN_ENCODER_DT GPIO_NUM_2
#define PIN_ENCODER_SW GPIO_NUM_8

// -------------------- Buttons -------------------------
#define PIN_BTN_11 GPIO_NUM_4
#define PIN_BTN_12 GPIO_NUM_5
#define PIN_BTN_13 GPIO_NUM_6
#define PIN_BTN_14 GPIO_NUM_7

#define PIN_BTN_21 GPIO_NUM_9
#define PIN_BTN_22 GPIO_NUM_10
#define PIN_BTN_23 GPIO_NUM_11
#define PIN_BTN_24 GPIO_NUM_12

#define PIN_BTN_B GPIO_NUM_13
#define PIN_BTN_A GPIO_NUM_14

// -------------------- I2C Display ---------------------
#define PIN_I2C_SCL GPIO_NUM_42
#define PIN_I2C_SDA GPIO_NUM_47

// -------------------- I2S DAC -------------------------
#define PIN_I2S_DOUT GPIO_NUM_16 // DIN of DAC
#define PIN_I2S_BCLK GPIO_NUM_17 // Bit Clock
#define PIN_I2S_WS GPIO_NUM_18   // LRC / Word Select

// -------------------- SD Card (SPI) -------------------
#define PIN_SD_CS GPIO_NUM_38
#define PIN_SD_MOSI GPIO_NUM_39
#define PIN_SD_CLK GPIO_NUM_40
#define PIN_SD_MISO GPIO_NUM_41

// -------------------- LEDs ----------------------------
#define PIN_ONBOARD_LED GPIO_NUM_44
#define PIN_ONBOARD_RGB_LED GPIO_NUM_48

// -------------------- Free ---------------------------
// #define PIN_FREE_1             GPIO_NUM_15
// #define PIN_FREE_2             GPIO_NUM_21
// #define PIN_FREE_3             GPIO_NUM_43

// // -------------------- Avoid if possible ---------------
// #define PIN_RESERVED_1         GPIO_NUM_35
// #define PIN_RESERVED_2         GPIO_NUM_36
// #define PIN_RESERVED_3         GPIO_NUM_37

// #define PIN_STRAP_BOOT         GPIO_NUM_0
// #define PIN_STRAP_45           GPIO_NUM_45
// #define PIN_STRAP_46           GPIO_NUM_46
// #define PIN_STRAP_JTAG         GPIO_NUM_3

// #define PIN_JTAG_DEBUG_1       GPIO_NUM_19
// #define PIN_JTAG_DEBUG_2       GPIO_NUM_20

#endif // PIN_DEFINES_H