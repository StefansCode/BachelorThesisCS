#ifndef NOTES_H
#define NOTES_H
#include "stdint.h"

#define A4 57

extern uint8_t lydian[8];
extern uint8_t ionian[8];
extern uint8_t mixolydian[8];
extern uint8_t dorian[8];
extern uint8_t aolian[8];
extern uint8_t phrygian[8];
extern uint8_t locrian[8];

extern uint8_t doubleHarmonic[8];

extern const uint8_t NUMBER_OF_SCALES;
extern uint8_t *scales[8];

extern const char *scaleNames[8];

extern const char * NoteNames[12];

extern const uint16_t NOTES[];

#endif//NOTES_H