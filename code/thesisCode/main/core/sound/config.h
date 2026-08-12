#ifndef CONFIG_H
#define CONFIG_H
#include <stdint.h>

// possible sample rates: 16384, 32768
#define STANDART_SAMPLE_RATE 32768
#define SOUND_BUFFER_SIZE 256
typedef int16_t sample;

const unsigned int BITS_PER_SAMPLE = sizeof(sample) * 8;
#define SAMPLE_MAX INT16_MAX
#define SAMPLE_MIN INT16_MIN
#define SAMPLE_RANGE (SAMPLE_MAX - SAMPLE_MIN)

#endif// CONFIG_H