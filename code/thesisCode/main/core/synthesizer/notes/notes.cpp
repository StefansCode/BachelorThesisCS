#include "notes.h"

uint8_t lydian[8] =     {0, 2, 4, 6, 7, 9, 11, 12};
uint8_t ionian[8] =     {0, 2, 4, 5, 7, 9, 11, 12};    // major scale or Dur
uint8_t mixolydian[8] = {0, 2, 4, 5, 7, 9, 10, 12};
uint8_t dorian[8] =     {0, 2, 3, 5, 7, 9, 10, 12}; 
uint8_t aolian[8] =     {0, 2, 3, 5, 7, 8, 10, 12};    // minor scale or Moll
uint8_t phrygian[8] =   {0, 1, 3, 5, 7, 8, 10, 12};
uint8_t locrian[8] =    {0, 1, 3, 5, 6, 8, 10, 12};  

uint8_t doubleHarmonic[8] = {0, 1, 4, 5, 7, 8, 11, 12};

const uint8_t NUMBER_OF_SCALES = 8;
uint8_t *scales[8] = {
lydian,
ionian,
mixolydian,
dorian,
aolian,
phrygian,
locrian,
doubleHarmonic
};

const char *scaleNames[8] = {
"LYDIAN",   // lydian
"IONIAN",   // major scale
"MXOLYN",   // mixolydian
"DORIAN",   // dorian
"AOLIAN",   // minor scale
"PHRYG",    // phrygian
"LOCR",     // locrian
"2HARMO"    // double harmonic
};

const char * noteNames[12] = {
"A",
"A#",
"B",
"C",
"C#",
"D",
"D#",
"E",
"F",
"F#",
"G",
"G#"
};

const char * waveformNames[4] = {
"SAW",      // sawtooth
"SQUARE",   // square
"TRINGL",   // triangle
"SINE"      // sine
};

const char * sampleRateNames[3] = {
"11025",
"22050",
"44100"
};

const uint16_t NOTES[] = {
16,
17,
18,
19,
20,
21,
23,
24,
25,
27,
29,
30,
32,
34,
36,
38,
41,
43,
46,
49,
51,
55,
58,
61,
65,
69,
73,
77,
82,
87,
92,
98,
103,
110,
116,
123,
130,
138,
146,
155,
164,
174,
185,
196,
207,
220,
233,
246,
261,
277,
293,
311,
329,
349,
369,
392,
415,
440,
466,
493,
523,
554,
587,
622,
659,
698,
739,
783,
830,
880,
932,
987,
1046,
1108,
1174,
1244,
1318,
1396,
1479,
1567,
1661,
1760,
1864,
1975,
2093,
2217,
2349,
2489,
2637,
2793,
2959,
3135,
3322,
3520,
3729,
3951,
4186,
4434,
4698,
4978};