#ifndef MINI_SYNTH_H
#define MINI_SYNTH_H
#include "adapter/button/button.h"
#include "adapter/dac/i2sDac.h"
#include "sound/sound.h"

Sound bass;

Sound sound1;
Sound sound2;
Sound sound3;
Sound sound4;
Sound sound5;
Sound sound6;
Sound sound7;
Sound sound8;

/** Arrays um auf die einzelnen Sounds mint eine Index zuzugreifen */
Sound leads[8] = {sound1, sound2, sound3, sound4, sound5, sound6, sound7, sound8};
unsigned int note[8] = {440, 493, 554, 587, 659, 739, 830, 880};
int buttonsPin[8] = {PIN_BTN_11, PIN_BTN_12, PIN_BTN_13, PIN_BTN_14, PIN_BTN_21, PIN_BTN_22, PIN_BTN_23, PIN_BTN_24};

void runMiniSynthTest() {

  float playBass = false;

  while (1) {
    if (buttons.readQueue() == PIN_BTN_B) {
      if (playBass == 0) {
        playBass = 1;
      } else {
        playBass = 0;
      }
    }
    for (int j = 0; j < SOUND_BUFFER_SIZE; j++) {
      bass.fromSaw(110)       // generiere den Bass
          .amplify(0.1f)      // mache den Bass leiser
          .amplify(playBass); // mache den Bass aus wenn playBass == 0
      for (int i = 0; i < 8; i++) {
        leads[i].fromSaw(note[i])  // Die Töne der einzelnen Tasten
                .amplify(0.1f)     // wie der Bass werden generiert.
                .amplify((float)buttons.getState(buttonsPin[i]));
        bass.add(leads[i]);   // addiere die Töne der einzelnen Tasten zum Bass
      }
      bass.amplify(0.3f);     // machhe nun alles leiser
    }
    // wenn der Buffer voll ist, sende ihn an den DAC
    dac.sendBuffer(bass.returnBuffer(), SOUND_BUFFER_SIZE * sizeof(sample));
  }
}

#endif // MINI_SYNTH_H