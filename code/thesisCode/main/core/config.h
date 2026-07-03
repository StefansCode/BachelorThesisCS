#ifndef CONFIG_H
#define CONFIG_H
#include <stdint.h>

#define SAMPLE_RATE 44100
#define BUFFER_SIZE 256
typedef uint16_t sample;

const uint8_t BITS_PER_SAMPLE = sizeof(sample) * 8;
const sample MAX_SAMPLE_VALUE = (1 << BITS_PER_SAMPLE) - 1;

#endif// CONFIG_H