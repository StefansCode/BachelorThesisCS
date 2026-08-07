#include "synthesizer.h"


Synthesizer synth;

Synthesizer::Synthesizer()
    : timer(),
      envelope1(timer),
      envelope2(timer),
      envelope3(timer),
      envelope4(timer),
      envelope5(timer),
      envelope6(timer),
      envelope7(timer),
      envelope8(timer),
      envelopeAttack(0),
      envelopeDecay(32),
      envelopeSustain(64),
      envelopeRelease(8),
      bassPlay(0),
      bassNote(0),
      bassWaveform(WAVEFORM_SAW),
      leadScale(1),
      leadWaveform(WAVEFORM_SAW) {}

/** @todo mit der static methode machen  */
void IOTaskWrapper(void *param) {
  synth.IOTask(param);
}

void screenTaskWrapper(void *param) {
  synth.screenTask(param);
}

void synthTaskWrapper(void *param) {
  synth.synthTask(param);
}

void Synthesizer::run() {
  xTaskCreate(IOTaskWrapper, "IOTask", 4096, NULL, 5, NULL);
  xTaskCreate(synthTaskWrapper, "SynthTask", 4096, NULL, 5, NULL);
  xTaskCreate(screenTaskWrapper, "ScreenTask", 4096, NULL, 5, NULL);
  unsigned int C = 0;
  while (1) {
    C++;
    printf("Synth main running since %d seconds.\r\n", C);
    // printf("leadScale: %d  bassPlay: %d   ", leadScale.get(), bassPlay.get());
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}