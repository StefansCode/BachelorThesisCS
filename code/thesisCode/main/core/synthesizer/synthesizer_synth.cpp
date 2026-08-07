#include "synthesizer.h"


void sendData(sample *data, void *param) {
  dac.sendBuffer(data, BUFFER_SIZE * sizeof(sample));
}


void Synthesizer::synthTask(void *param) {
  while (1) {

    // taskAnalyser.startTimerWithId(1);

    if(bassWaveform.get() == WAVEFORM_SAW) {
      bass.fromSaw(NOTES[A4 + bassNote.get() - 12]);
    } else if(bassWaveform.get() == WAVEFORM_SQUARE) {
      bass.fromSquare(NOTES[A4 + bassNote.get() - 12]);
    } else if(bassWaveform.get() == WAVEFORM_TRIANGLE) {
      bass.fromTriangle(NOTES[A4 + bassNote.get() - 12]);
    } else if(bassWaveform.get() == WAVEFORM_SINE) {
      bass.fromSine(NOTES[A4 + bassNote.get() - 12]);
    } else {
      bass.fromSaw(NOTES[A4 + bassNote.get() - 12]);
    }

    // taskAnalyser.stopTimerWithId(1);

    // taskAnalyser.startTimerWithId(2);

    scale = scales[leadScale.get()];

    if (bassPlay.get() == 0) {
      /** @todo add fromSilence */
      bass.amplify(0);
    } else {
      bass.amplify(0.1);
    }

    // taskAnalyser.stopTimerWithId(2);

    // taskAnalyser.startTimerWithId(3);
    generateSound(lead1, ((float)envelope1.getValue()) / 255.0f, NOTES[A4 + bassNote.get() + scale[0]], leadWaveform.get());
    generateSound(lead2, ((float)envelope2.getValue()) / 255.0f, NOTES[A4 + bassNote.get() + scale[1]], leadWaveform.get());
    generateSound(lead3, ((float)envelope3.getValue()) / 255.0f, NOTES[A4 + bassNote.get() + scale[2]], leadWaveform.get());
    generateSound(lead4, ((float)envelope4.getValue()) / 255.0f, NOTES[A4 + bassNote.get() + scale[3]], leadWaveform.get());
    generateSound(lead5, ((float)envelope5.getValue()) / 255.0f, NOTES[A4 + bassNote.get() + scale[4]], leadWaveform.get());
    generateSound(lead6, ((float)envelope6.getValue()) / 255.0f, NOTES[A4 + bassNote.get() + scale[5]], leadWaveform.get());
    generateSound(lead7, ((float)envelope7.getValue()) / 255.0f, NOTES[A4 + bassNote.get() + scale[6]], leadWaveform.get());
    generateSound(lead8, ((float)envelope8.getValue()) / 255.0f, NOTES[A4 + bassNote.get() + scale[7]], leadWaveform.get());

    // taskAnalyser.stopTimerWithId(3);

    // taskAnalyser.startTimerWithId(4);

    bass.amplify(0.3).toFunction(sendData, NULL);

    // taskAnalyser.stopTimerWithId(4);
  }
}

void Synthesizer::generateSound(Sound &sound, float amplification, int frequency, int waveform) {
  if ( amplification == 0.0f) {
    sound.fromSilence();
    return;
  }
  if (waveform == WAVEFORM_SAW) {
    sound.fromSaw(frequency);
  } else if (waveform == WAVEFORM_SQUARE) {
    sound.fromSquare(frequency);
  } else if (waveform == WAVEFORM_TRIANGLE) {
    sound.fromTriangle(frequency);
  } else if (waveform == WAVEFORM_SINE) {
    sound.fromSine(frequency);
  } else {
    sound.fromSaw(frequency);
  }
  sound.amplify(0.1);
  sound.amplify(amplification);
  bass.add(sound);
}