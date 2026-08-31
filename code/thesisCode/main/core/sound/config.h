#ifndef CONFIG_H
#define CONFIG_H
#include <stdint.h>

// possible sample rates: 16384, 32768, 44100, 22050, 11025
#define STANDART_SAMPLE_RATE 32768
// possible bit depths: 16, 32
#define BITS_PER_SAMPLE_ 16

#if BITS_PER_SAMPLE_ == 16
    typedef int16_t sample;
    const unsigned int BITS_PER_SAMPLE = sizeof(sample) * 8;
    #define SAMPLE_MAX INT16_MAX
    #define SAMPLE_MIN INT16_MIN
    #define SAMPLE_RANGE (SAMPLE_MAX - SAMPLE_MIN)
#elif BITS_PER_SAMPLE_ == 32
    typedef int32_t sample;
    const unsigned int BITS_PER_SAMPLE = sizeof(sample) * 8;
    #define SAMPLE_MAX INT32_MAX
    #define SAMPLE_MIN INT32_MIN
    #define SAMPLE_RANGE (SAMPLE_MAX - SAMPLE_MIN)
#endif

#define SOUND_BUFFER_SIZE 256

#endif// CONFIG_H