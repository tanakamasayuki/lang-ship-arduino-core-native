#pragma once

#include <stdint.h>

// I2C
static const uint8_t SDA = 21;
static const uint8_t SCL = 22;

// SPI (display / SD)
static const uint8_t SS    = 5;
static const uint8_t MOSI  = 23;
static const uint8_t MISO  = 19;
static const uint8_t SCK   = 18;

static const uint8_t TFT_CS   = 14;
static const uint8_t TFT_DC   = 27;
static const uint8_t TFT_RST  = 33;
static const uint8_t TFT_LED  = 32;
static const uint8_t TFT_MOSI = MOSI;
static const uint8_t TFT_MISO = MISO;
static const uint8_t TFT_SCLK = SCK;

static const uint8_t SD_CS    = 4;

static const uint8_t SPEAKER_PIN = 25;

static const uint8_t BUTTON_A_PIN = 39;
static const uint8_t BUTTON_B_PIN = 38;
static const uint8_t BUTTON_C_PIN = 37;

static const uint8_t IMU_INT_PIN = 36;

static const uint8_t LED_BUILTIN = 10;

#define TFT_WIDTH  320
#define TFT_HEIGHT 240

