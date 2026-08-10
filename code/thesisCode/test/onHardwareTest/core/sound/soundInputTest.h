#ifndef SOUND_INPUT_TEST_H
#define SOUND_INPUT_TEST_H
#include "adapter/button/button.h"
#include "core/sound/sound.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <esp_timer.h>
#include <esp_random.h>
#include <stdio.h>

Sound saw;
Sound saw2;
Sound sine;
Sound square;
Sound triangle;

Sound sound;

sample printOneSignal(sample data, void *param) {
  const char *name = (const char *)param;
  printf(">%s:%d\r\n", name, data);
  return data;
}

sample printSignal(sample data, void *param) {
  const char *name = (const char *)param;
  printf("%s:%d ", name, data);
  return data;
}

void runSoundInputTest_allWaveforms() {
  double x = 0;
  while (1) {
    x = x + 0.1;
    printf(">");
    saw.fromSaw(440).applyFunction(printSignal, (void *)"Saw");
    printf(",");
    saw2.fromSaw(880).applyFunction(printSignal, (void *)"Saw2");
    printf(",");
    sine.fromSine(440).applyFunction(printSignal, (void *)"Sine");
    printf(",");
    square.fromSquare(440).applyFunction(printSignal, (void *)"Square");
    printf(",");
    triangle.fromTriangle(440).applyFunction(printSignal, (void *)"Triangle");
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

    sound.applyFunction(printOneSignal, (void *)"sound");
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
    for (int i = 0; i < STANDART_SAMPLE_RATE; i++) {
      sound.fromSaw(440);
    }
    uint32_t t2 = millis();
    for (int i = 0; i < STANDART_SAMPLE_RATE; i++) {
      sound.fromSine(440);
    }
    uint32_t t3 = millis();
    for (int i = 0; i < STANDART_SAMPLE_RATE; i++) {
      sound.fromSquare(440);
    }
    uint32_t t4 = millis();
    for (int i = 0; i < STANDART_SAMPLE_RATE; i++) {
      sound.fromTriangle(440);
    }
    uint32_t t5 = millis();
    printf("Saw: %lu ms, Sine: %lu ms, Square: %lu ms, Triangle: %lu ms\r\n", t2 - t1, t3 - t2, t4 - t3, t5 - t4);
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}

ThreadSaveInt testVariable(256);

void runSoundInputTest_calulationSpeeds() {

  int x = testVariable.get();
  while (1) {
    uint32_t t1 = millis();
    for (int i = 0; i < STANDART_SAMPLE_RATE; i++) {
      sound.fromSaw(440);
    }
    uint32_t t2 = millis();
    for (int i = 0; i < STANDART_SAMPLE_RATE; i++) {
      sound.amplify(x);
    }
    uint32_t t3 = millis();
    for (int i = 0; i < STANDART_SAMPLE_RATE; i++) {
      sound.amplify(float(testVariable.get()) / 255.0f );
    }
    uint32_t t4 = millis();
    for (int i = 0; i < STANDART_SAMPLE_RATE; i++) {
      int x = testVariable.get();
    }
    uint32_t t5 = millis();
    for (int i = 0; i < STANDART_SAMPLE_RATE; i++) {
      sound.add(sound);
    }
    uint32_t t6 = millis();
    for (int i = 0; i < STANDART_SAMPLE_RATE; i++) {
      sound.returnBuffer();
    }
    uint32_t t7 = millis();
    printf("Generate: %lu ms, Amplify: %lu ms, Amplify (Variable): %lu ms,set Variable: %lu ms, Add: %lu ms, Output: %lu ms\r\n", t2 - t1, t3 - t2, t4 - t3, t5 - t4, t6 - t5, t7 - t6);
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}
#endif // SOUND_INPUT_TEST_H