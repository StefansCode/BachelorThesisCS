#ifndef SYNTHESIZER_H
#define SYNTHESIZER_H
#include "adapter/Encoder/Encoder.h"
#include "adapter/button/button.h"
#include "adapter/rgbLed/rgbLed.h"
#include "adapter/screen/screen.h"
#include "adapter/dac/i2sDac.h"
#include "adapter/threadSaveVariable/threadSaveVariable.h"
#include "config.h"
#include "notes/notes.h"
#include "core/sound/sound.h"

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

  uint16_t root = A4;
  uint8_t *scale = scales[0];

  ThreadSaveInt scaleCounter;
  ThreadSaveBool playBass;
};

extern Synthesizer synth;

#endif // SYNTHESIZER_H