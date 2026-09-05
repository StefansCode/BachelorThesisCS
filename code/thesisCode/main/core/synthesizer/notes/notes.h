#ifndef NOTES_H
#define NOTES_H
#include "stdint.h"

#define A0 10   // 27Hz
#define A1 22   // 55Hz
#define A2 33   // 110Hz
#define A3 45   // 220Hz
#define A4 57   // 440Hz
#define A5 69   // 880Hz
#define A6 81   // 1760Hz
#define A7 93   // 3520Hz

extern uint8_t lydian[8];
extern uint8_t ionian[8];
extern uint8_t mixolydian[8];
extern uint8_t dorian[8];
extern uint8_t aolian[8];
extern uint8_t phrygian[8];
extern uint8_t locrian[8];

extern uint8_t doubleHarmonic[8];

extern const uint8_t NUMBER_OF_SCALES;
extern uint8_t * scales[8];

extern const char * scaleNames[8];
extern const char * noteNames[12];
extern const char * waveformNames[5];
extern const char * sampleRateNames[3];

extern const uint16_t NOTES[];

#endif//NOTES_H