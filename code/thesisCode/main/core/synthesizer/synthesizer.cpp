#include "synthesizer.h"
#include "debug/taskAnalyser/taskAnalyser.h"

TaskAnalyser taskAnalyser;

Synthesizer synth;

Synthesizer::Synthesizer() : scaleCounter(0), playBass(false) {}

/** @todo mit der static methode machen  */
void IOTaskWrapper(void *param) {
  synth.IOTask(param);
}

void synthTaskWrapper(void *param) {
  synth.synthTask(param);
}

void Synthesizer::run() {
  xTaskCreate(IOTaskWrapper, "IOTask", 4096, NULL, 5, NULL);
  xTaskCreate(synthTaskWrapper, "SynthTask", 4096, NULL, 5, NULL);

  while (1) {
    //printf("Synth main running  ");
    printf("scaleCounter: %d  playBass: %d   ", scaleCounter.get(), playBass.get());
    vTaskDelay(100 / portTICK_PERIOD_MS);
  }
}

void Synthesizer::IOTask(void *param) {

  int lightLvl = 1;

  while (1) {
    vTaskDelay(100 / portTICK_PERIOD_MS);

    uint8_t queue = buttons.readQueue();
    uint32_t allButton = buttons.getStateAll();

    if (queue == PIN_BTN_A) {
      scaleCounter.set((scaleCounter.get() + 1) % 3);
    }
    if ( queue == PIN_BTN_B) {
      playBass.set(!playBass.get());
    }

    encoder.changeExternalValue(lightLvl, 0, 15, 1);

    printf("Encoder value: %d  lightLvl: %d  queue: %d  buttonState: ", encoder.getvalue(), lightLvl, queue);
    for (int i = 0; i < 32; i++) {
      printf("%d", int((allButton >> i) & (1U)));
    }
    printf("\r\n");

    if (scaleCounter.get() == 0) {
      rgbLed.set(0, lightLvl * 16, 0);
    } else if (scaleCounter.get() == 1) {
      rgbLed.set(lightLvl * 16, 0, 0);
    } else {
      rgbLed.set(0, 0, lightLvl * 16);
    }
    rgbLed.on();
  }
}

void sendData(sample *data, void *param) {
  dac.sendBuffer(data, BUFFER_SIZE * sizeof(sample));
}
uint8_t time = 0;
void Synthesizer::synthTask(void *param) {
  while (1) {

    // taskAnalyser.startTimerWithId(1);

    bass.fromSine(NOTES[root - 12]);

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

    if (buttons.getState(PIN_BTN_11)) {
      lead1.fromSine(NOTES[root + scale[0]]).amplify(0.1);
      bass.add(lead1);
    }
    if (buttons.getState(PIN_BTN_12)) {
      lead2.fromSine(NOTES[root + scale[1]]).amplify(0.1);
      bass.add(lead2);
    }
    if (buttons.getState(PIN_BTN_13)) {
      lead3.fromSine(NOTES[root + scale[2]]).amplify(0.1);
      bass.add(lead3);
    }
    if (buttons.getState(PIN_BTN_14)) {
      lead4.fromSine(NOTES[root + scale[3]]).amplify(0.1);
      bass.add(lead4);
    }
    if (buttons.getState(PIN_BTN_21)) {
      lead5.fromSine(NOTES[root + scale[4]]).amplify(0.1);
      bass.add(lead5);
    }
    if (buttons.getState(PIN_BTN_22)) {
      lead6.fromSine(NOTES[root + scale[5]]).amplify(0.1);
      bass.add(lead6);
    }
    if (buttons.getState(PIN_BTN_23)) {
      lead7.fromSine(NOTES[root + scale[6]]).amplify(0.1);
      bass.add(lead7);
    }
    if (buttons.getState(PIN_BTN_24)) {
      lead8.fromSine(NOTES[root + scale[7]]).amplify(0.1);
      bass.add(lead8);
    }

    // taskAnalyser.stopTimerWithId(3);

    taskAnalyser.startTimerWithId(4);

    bass.amplify(0.3).toFunction(sendData, NULL);

    taskAnalyser.stopTimerWithId(4);

  }
}