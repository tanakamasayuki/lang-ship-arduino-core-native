#pragma once

#include <stdint.h>

#define NUM_DIGITAL_PINS        48
#define NUM_ANALOG_INPUTS       0
#define NUM_ANALOG_OUTPUTS      0

extern const uint8_t digitalPinToChannel[];

void initVariant(void);

