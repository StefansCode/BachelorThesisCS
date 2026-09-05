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

const char * waveformNames[5] = {
"SAW",      // sawtooth
"SQUARE",   // square
"TRINGL",   // triangle
"SINE",      // sine
"NOISE"     // noise
};

const char * sampleRateNames[3] = {
"11025",
"22050",
"44100"
};

const uint16_t NOTES[] = {
16,     // 1    C0
17,     // 2    C#0
18,     // 3    D0
19,     // 4    D#0
20,     // 5    E0
21,     // 6    F0
23,     // 7    F#0
24,     // 8    G0
25,     // 9    G#0
27,     // 10   A0
29,     // 11   A#0
30,     // 12   B0
32,     // 13   C1
34,     // 14   C#1
36,     // 15   D1
38,     // 16   D#1
41,     // 17   E1
43,     // 18   F1
46,     // 19   F#1
49,     // 20   G1
51,     // 21   G#1
55,     // 22   A1
58,     // 23   A#1
61,     // 24   B1
65,     // 25   C2
69,     // 26   C#2
73,     // 27   D2
77,     // 28   D#2
82,     // 29   E2
87,     // 30   F2
92,     // 31   F#2
98,     // 32   G2
103,    // 33   G#2
110,    // 34   A2
116,    // 35   A#2
123,    // 36   B2
130,    // 37   C3
138,    // 38   C#3
146,    // 39   D3
155,    // 40   D#3
164,    // 41   E3
174,    // 42   F3
185,    // 43   F#3
196,    // 44   G3
207,    // 45   G#3
220,    // 46   A3
233,    // 47   A#3
246,    // 48   B3
261,    // 49   C4
277,    // 50   C#4
293,    // 51   D4
311,    // 52   D#4
329,    // 53   E4
349,    // 54   F4
369,    // 55   F#4
392,    // 56   G4
415,    // 57   G#4
440,    // 58   A4
466,    // 59   A#4
493,    // 60   B4
523,    // 61   C5
554,    // 62   C#5
587,    // 63   D5
622,    // 64   D#5
659,    // 65   E5
698,    // 66   F5
739,    // 67   F#5
783,    // 68   G5
830,    // 69   G#5
880,    // 70   A5
932,    // 71   A#5
987,    // 72   B5
1046,   // 73   C6
1108,   // 74   C#6
1174,   // 75   D6
1244,   // 76   D#6
1318,   // 77   E6
1396,   // 78   F6
1479,   // 79   F#6
1567,   // 80   G6
1661,   // 81   G#6
1760,   // 82   A6
1864,   // 83   A#6
1975,   // 84   B6
2093,   // 85   C7
2217,   // 86   C#7
2349,   // 87   D7
2489,   // 88   D#7
2637,   // 89   E7
2793,   // 90   F7
2959,   // 91   F#7
3135,   // 92   G7
3322,   // 93   G#7
3520,   // 94   A7
3729,   // 95   A#7
3951,   // 96   B7
4186,   // 97   C8
4434,   // 98   C#8
4698,   // 99   D8
4978    // 100  D#8
};