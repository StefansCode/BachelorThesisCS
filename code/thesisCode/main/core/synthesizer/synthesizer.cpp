#include "synthesizer.h"
// #include "debug/taskAnalyser/taskAnalyser.h"

// TaskAnalyser taskAnalyser;

Synthesizer synth;

Synthesizer::Synthesizer()
    : timer(),
      envelope1(timer),
      envelopeValue1(0),
      envelope2(timer),
      envelopeValue2(0),
      envelope3(timer),
      envelopeValue3(0),
      envelope4(timer),
      envelopeValue4(0),
      envelope5(timer),
      envelopeValue5(0),
      envelope6(timer),
      envelopeValue6(0),
      envelope7(timer),
      envelopeValue7(0),
      envelope8(timer),
      envelopeValue8(0),
      scaleCounter(0),
      playBass(false),
      root(A4) {}

/** @todo mit der static methode machen  */
void IOTaskWrapper(void *param) {
  synth.IOTask(param);
}

void screenTaskWrapper(void* param) {
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
    // printf("scaleCounter: %d  playBass: %d   ", scaleCounter.get(), playBass.get());
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}

void Synthesizer::IOTask(void *param) {

  // int lightLvl = 1;
  envelope1.set(0, 25, 0, 2);
  envelope2.set(0, 25, 0, 2);
  envelope3.set(0, 25, 0, 2);
  envelope4.set(0, 25, 0, 2);

  envelope5.set(0, 25, 0, 2);
  envelope6.set(0, 25, 0, 2);
  envelope7.set(0, 25, 0, 2);
  envelope8.set(0, 25, 0, 2);

  while (1) {
    // uint8_t queue = buttons.readQueue();
    // uint32_t allButton = buttons.getStateAll();

    // if (queue == PIN_BTN_A) {
    //   scaleCounter.set((scaleCounter.get() + 1) % 3);
    // }
    // if (queue == PIN_BTN_B) {
    //   playBass.set(!playBass.get());
    // }

    // encoder.changeExternalValue(lightLvl, 0, 15, 1);

    envelopeValue1.set(envelope1.apply(buttons.getState(PIN_BTN_11)));
    envelopeValue2.set(envelope2.apply(buttons.getState(PIN_BTN_12)));
    envelopeValue3.set(envelope3.apply(buttons.getState(PIN_BTN_13)));
    envelopeValue4.set(envelope4.apply(buttons.getState(PIN_BTN_14)));

    envelopeValue5.set(envelope5.apply(buttons.getState(PIN_BTN_21)));
    envelopeValue6.set(envelope6.apply(buttons.getState(PIN_BTN_22)));
    envelopeValue7.set(envelope7.apply(buttons.getState(PIN_BTN_23)));
    envelopeValue8.set(envelope8.apply(buttons.getState(PIN_BTN_24)));

    // printf("Encoder value: %d  lightLvl: %d  buttonState: ", encoder.getvalue(), lightLvl);
    // for (int i = 0; i < 32; i++) {
    //   printf("%d", int((allButton >> i) & (1U)));
    // }
    // printf("\r\n");

    // if (scaleCounter.get() == 0) {
    //   rgbLed.set(0, lightLvl * 16, 0);
    // } else if (scaleCounter.get() == 1) {
    //   rgbLed.set(lightLvl * 16, 0, 0);
    // } else {
    //   rgbLed.set(0, 0, lightLvl * 16);
    // }
    // rgbLed.on();

    util.delay(100);
  }
}

void sendData(sample *data, void *param) {
  dac.sendBuffer(data, BUFFER_SIZE * sizeof(sample));
}
uint8_t time = 0;
void Synthesizer::synthTask(void *param) {
  while (1) {
    int local_root = root.get();
    int local_waveform = waveform.get();

    // taskAnalyser.startTimerWithId(1);

    
    bass.fromSaw(NOTES[local_root - 12]);

    // taskAnalyser.stopTimerWithId(1);

    // taskAnalyser.startTimerWithId(2);

    scale = scales[scaleCounter.get()];

    if (!playBass.get()) {
      bass.amplify(0);
    } else {
      bass.amplify(0.1);
    }

    // taskAnalyser.stopTimerWithId(2);

    // taskAnalyser.startTimerWithId(3);

    if (envelopeValue1.get() != 0) {
      lead1.fromSaw(NOTES[local_root + scale[0]])
           .amplify(0.1)
           .amplify(((float)envelopeValue1.get())/255.0f);
      bass.add(lead1);
    }
    if (envelopeValue2.get() != 0) {
      lead2.fromSaw(NOTES[local_root + scale[1]])
           .amplify(0.1)
           .amplify(((float)envelopeValue2.get())/255.0f);
      bass.add(lead2);
    }
    if (envelopeValue3.get() != 0) {
      lead3.fromSaw(NOTES[local_root + scale[2]])
           .amplify(0.1)
           .amplify(((float)envelopeValue3.get())/255.0f);
      bass.add(lead3);
    }
    if (envelopeValue4.get() != 0) {
      lead4.fromSaw(NOTES[local_root + scale[3]])
           .amplify(0.1)
           .amplify(((float)envelopeValue4.get())/255.0f);
      bass.add(lead4);
    }
    if (envelopeValue5.get() != 0) {
      lead5.fromSaw(NOTES[local_root + scale[4]])
           .amplify(0.1)
           .amplify(((float)envelopeValue5.get())/255.0f);
      bass.add(lead5);
    }
    if (envelopeValue6.get() != 0) {
      lead6.fromSaw(NOTES[local_root + scale[5]])
           .amplify(0.1)
           .amplify(((float)envelopeValue6.get())/255.0f);
      bass.add(lead6);
    }
    if (envelopeValue7.get() != 0) {
      lead7.fromSaw(NOTES[local_root + scale[6]])
           .amplify(0.1)
           .amplify(((float)envelopeValue7.get())/255.0f);
      bass.add(lead7);
    }
    if (envelopeValue8.get() != 0) {
      lead8.fromSaw(NOTES[local_root + scale[7]])
           .amplify(0.1)
           .amplify(((float)envelopeValue8.get())/255.0f);
      bass.add(lead8);
    }

    // taskAnalyser.stopTimerWithId(3);

    // taskAnalyser.startTimerWithId(4);

    bass.amplify(0.3).toFunction(sendData, NULL);

    // taskAnalyser.stopTimerWithId(4);
  }
}