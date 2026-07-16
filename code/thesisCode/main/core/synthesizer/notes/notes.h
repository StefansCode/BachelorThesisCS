#ifndef NOTES_H
#define NOTES_H
#include "stdint.h"

#define A4 57

extern uint8_t majorScale[8];
extern uint8_t minorScale[8];
extern uint8_t desertScale[8];

extern uint8_t *scales[3];
extern uint8_t NUMBER_OF_SCALES;


extern const uint16_t NOTES[];

#endif//NOTES_H