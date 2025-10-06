#pragma once

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

void init(void);
void initVariant(void);
void yield(void);
unsigned long millis(void);
unsigned long micros(void);
void delay(unsigned long ms);
void delayMicroseconds(unsigned int us);
void randomSeed(unsigned long seed);
long random(long howbig);
long random(long howsmall, long howbig);

void pinMode(uint8_t pin, uint8_t mode);
void digitalWrite(uint8_t pin, uint8_t val);
int digitalRead(uint8_t pin);
int analogRead(uint8_t pin);
void analogWrite(uint8_t pin, int value);

#ifdef __cplusplus
}
#endif

#define HIGH 0x1
#define LOW  0x0

#define INPUT         0x0
#define OUTPUT        0x1
#define INPUT_PULLUP  0x2

#define LSBFIRST 0
#define MSBFIRST 1

#define CHANGE 1
#define FALLING 2
#define RISING 3

#define PI 3.14159265358979323846
#define HALF_PI 1.57079632679489661923
#define TWO_PI 6.28318530717958647692
#define DEG_TO_RAD 0.01745329251994329577
#define RAD_TO_DEG 57.2957795130823208768
#define EULER 2.71828182845904523536

#define SERIAL  0
#define DISPLAY 1

typedef uint8_t byte;
typedef uint16_t word;
typedef bool boolean;

#define bit(b) (1UL << (b))
#define bitRead(value, bit) (((value) >> (bit)) & 0x01)
#define bitSet(value, bit) ((value) |= (1UL << (bit)))
#define bitClear(value, bit) ((value) &= ~(1UL << (bit)))
#define bitWrite(value, bit, bitvalue) (bitvalue ? bitSet(value, bit) : bitClear(value, bit))

#define min(a,b) ((a)<(b)?(a):(b))
#define max(a,b) ((a)>(b)?(a):(b))
#define abs(x) ((x)>0?(x):-(x))
#define constrain(amt,low,high) ((amt)<(low)?(low):((amt)>(high)?(high):(amt)))
#define round(x)     ((x)>=0?(long)((x)+0.5):(long)((x)-0.5))
#define radians(deg) ((deg)*DEG_TO_RAD)
#define degrees(rad) ((rad)*RAD_TO_DEG)
#define sq(x)        ((x)*(x))

#define interrupts()
#define noInterrupts()

#define clockCyclesPerMicrosecond()  240
#define clockCyclesToMicroseconds(a) ((a) / clockCyclesPerMicrosecond())
#define microsecondsToClockCycles(a) ((a) * clockCyclesPerMicrosecond())

#define PROGMEM
#define PGM_P const char*
#define prog_char char
#define pgm_read_byte(addr) (*(const uint8_t *)(addr))
#define pgm_read_word(addr) (*(const uint16_t *)(addr))
#define pgm_read_dword(addr) (*(const uint32_t *)(addr))
#define pgm_read_float(addr) (*(const float *)(addr))
#define pgm_read_ptr(addr) (*(void const **)(addr))

#define F(str_literal) (str_literal)

#define IRAM_ATTR
#define DRAM_ATTR
#define RTC_DATA_ATTR
#define FLASHMEM
#define ICACHE_RAM_ATTR
#define ICACHE_FLASH_ATTR

#ifdef __cplusplus

#include <algorithm>
#include <string>

class String;
class __FlashStringHelper;
class Printable;
class Stream;

#include "WCharacter.h"
#include "WString.h"
#include "Printable.h"
#include "Print.h"
#include "Stream.h"
#include "HardwareSerial.h"

extern HardwareSerial Serial;

#endif

#include "variant.h"

#ifdef __cplusplus
void tone(uint8_t pin, unsigned int frequency, unsigned long duration = 0);
void noTone(uint8_t pin);
#endif

