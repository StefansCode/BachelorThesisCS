#ifndef SYNTHESIZER_H
#define SYNTHESIZER_H
#include "adapter/Encoder/Encoder.h"
#include "adapter/button/button.h"
#include "adapter/rgbLed/rgbLed.h"
#include "adapter/screen/screen.h"
#include "adapter/dac/i2sDac.h"
#include "adapter/threadSaveVariable/threadSaveVariable.h"
#include "adapter/util/util.h"

#include "sound/sound.h"

#include "config.h"
#include "notes/notes.h"
#include "menu/menu.h"
#include "envelope/envelope.h"

class Synthesizer {
public:
  Synthesizer();

  // void init();
  void run();

  /**
   * @brief Handels the sound generation and output.
   */
  void synthTask(void *param);

  /**
   * @brief Handels the screen output.
   */
  void screenTask(void *param);

  /**
   * @brief Handels the buttons, encoder and led.
   */
  void IOTask(void *param);

private:
  Sound bass;
  Sound lead1;
  Sound lead2;
  Sound lead3;
  Sound lead4;
  Sound lead5;
  Sound lead6;
  Sound lead7;
  Sound lead8;

  Timer timer;

  Envelope envelope1;
  ThreadSaveInt envelopeValue1;
  Envelope envelope2;
  ThreadSaveInt envelopeValue2;
  Envelope envelope3;
  ThreadSaveInt envelopeValue3;
  Envelope envelope4;
  ThreadSaveInt envelopeValue4;
  Envelope envelope5;
  ThreadSaveInt envelopeValue5;
  Envelope envelope6;
  ThreadSaveInt envelopeValue6;
  Envelope envelope7;
  ThreadSaveInt envelopeValue7;
  Envelope envelope8;
  ThreadSaveInt envelopeValue8;

  Menu menu;

  uint16_t root = A4;
  uint8_t *scale = scales[0];

  ThreadSaveInt scaleCounter;
  ThreadSaveBool playBass;
};

extern Synthesizer synth;

#endif // SYNTHESIZER_H