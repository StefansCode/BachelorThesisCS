#ifndef SOUND_INPUT_TEST_H
#define SOUND_INPUT_TEST_H
#include <esp_timer.h>
#include "adapter/button/button.h"
#include "core/sound/sound.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <stdio.h>

Sound saw;
Sound saw2;
Sound sine;
Sound square;
Sound triangle;

Sound sound;

void printOneSignal(sample data, void *param) {
  const char *name = (const char *)param;
  printf(">%s:%d\r\n", name, data);
}

void printSignal(sample data, void *param) {
  const char *name = (const char *)param;
  printf("%s:%d ", name, data);
}

void runSoundInputTest_allWaveforms() {
  double x = 0;
  while (1) {
    x = x + 0.1;
    printf(">");
    saw.fromSaw(440).toFunction(printSignal, (void *)"Saw");
    printf(",");
    saw2.fromSaw(880).toFunction(printSignal, (void *)"Saw2");
    printf(",");
    sine.fromSine(440).toFunction(printSignal, (void *)"Sine");
    printf(",");
    square.fromSquare(440).toFunction(printSignal, (void *)"Square");
    printf(",");
    triangle.fromTriangle(440).toFunction(printSignal, (void *)"Triangle");
    printf("\r\n");
    vTaskDelay(pdMS_TO_TICKS(100));
  }
}

void runSoundInputTest_switchWaveforms() {
  buttons.init();
  uint8_t waveform = 0;
  while (1) {
    uint8_t queue = buttons.readQueue();
    if (queue == PIN_BTN_11) {
      waveform = 0;
    }
    if (queue == PIN_BTN_12) {
      waveform = 1;
    }
    if (queue == PIN_BTN_13) {
      waveform = 2;
    }
    if (queue == PIN_BTN_14) {
      waveform = 3;
    }

    if (waveform == 0) {
      sound = sound.fromSaw(440);
    } else if (waveform == 1) {
      sound = sound.fromSine(440);
    } else if (waveform == 2) {
      sound = sound.fromSquare(440);
    } else if (waveform == 3) {
      sound = sound.fromTriangle(440);
    }

    sound.toFunction(printOneSignal, (void *)"sound");
    vTaskDelay(20 / portTICK_PERIOD_MS);
  }
}

void emptyFunction(sample data, void *param) {
  // Do nothing
}

uint32_t millis() {
  return esp_timer_get_time() / 1000;
}

void runSoundInputTest_waveformCalulationSpeed() {
  while (1) {
    uint32_t t1 = millis();
    for (int i = 0; i < SAMPLE_RATE; i++) {
      sound.fromSaw(440).toFunction(emptyFunction, NULL);
    }
    uint32_t t2 = millis();
    for (int i = 0; i < SAMPLE_RATE; i++) {
      sound.fromSine(440).toFunction(emptyFunction, NULL);
    }
    uint32_t t3 = millis();
    for (int i = 0; i < SAMPLE_RATE; i++) {
      sound.fromSquare(440).toFunction(emptyFunction, NULL);
    }
    uint32_t t4 = millis();
    for (int i = 0; i < SAMPLE_RATE; i++) {
      sound.fromTriangle(440).toFunction(emptyFunction, NULL);
    }
    uint32_t t5 = millis();
    printf("Saw: %lu ms, Sine: %lu ms, Square: %lu ms, Triangle: %lu ms\r\n", t2 - t1, t3 - t2, t4 - t3, t5 - t4);
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}
#endif // SOUND_INPUT_TEST_H