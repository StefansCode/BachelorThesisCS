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

#define WAVEFORM_SAW 0
#define WAVEFORM_SQUARE 1
#define WAVEFORM_TRIANGLE 2
#define WAVEFORM_SINE 3

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

  void generateSound(Sound &lead, float amplification, int frequency, int waveform);

  Timer timer;

  Envelope envelope1;
  Envelope envelope2;
  Envelope envelope3;
  Envelope envelope4;
  Envelope envelope5;
  Envelope envelope6;
  Envelope envelope7;
  Envelope envelope8;

  ThreadSaveInt envelopeAttack;
  ThreadSaveInt envelopeDecay;
  ThreadSaveInt envelopeSustain;
  ThreadSaveInt envelopeRelease;

  Menu menu;
  int lastEncoderValue = 0;
  bool navigateMenuWithEncoder(int encoderValue);
  bool handelValueChange(uint8_t queue);
  bool handleVariableChange(uint8_t queue, ThreadSaveInt &variable);
  bool handleTODO(uint8_t queue);

  /** Bass variables and handler */
  ThreadSaveInt bassPlay;
  ThreadSaveInt bassNote;
  /** - 0 = saw
   *  - 1 = square
   *  - 2 = triangle
   *  - 3 = sine
   */
  ThreadSaveInt bassWaveform;

  uint8_t *scale = scales[0];

  ThreadSaveInt leadScale;
  ThreadSaveInt leadWaveform;
};

extern Synthesizer synth;

#endif // SYNTHESIZER_H