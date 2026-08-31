#ifndef SOUND_INPUT_TEST_H
#define SOUND_INPUT_TEST_H
#include "adapter/button/button.h"
#include "adapter/util/util.h"
#include "core/sound/sound.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <esp_random.h>
#include <esp_timer.h>
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

Sound sine220;
Sound sine220_2;
Sound sine330;
Sound sine330_2;

void runSoundInputTest_overflow() {
  while (1) {
    printf(">");
    sine220.fromSine(220).applyFunction(printSignal, (void *)"Sine220");
    printf(",");
    sine330.fromSine(330).applyFunction(printSignal, (void *)"Sine330");
    printf(",");
    sine220.add(sine330_2.fromSine(330)).applyFunction(printSignal, (void *)"Sine330Sine220");
    printf(",");
    sine330.amplify(0.5f).add(sine220_2.fromSine(220).amplify(0.5f)).applyFunction(printSignal, (void *)"Sine33005Sine22005");
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

ThreadSaveFloat testVariableFloat(0.25f);

sample x[256] = {0};
sample y[256] = {0};

void runSoundInputTest_calulationSpeeds() {
  float sum = 0;
  int count = 0;
  while (1) {
    for (int j = 0; j < 1000; j++) {
      for (int i = 0; i < 10; i++) {
        y[i]++;
      }
      float t1 = ((float)util.micros()) / 1000.0f / 1000.0f * 100.0f;
      for (int i = 0; i < STANDART_SAMPLE_RATE; i++) {
        saw.fromSaw(j);
      }
      float t2 = ((float)util.micros()) / 1000.0f / 1000.0f * 100.0f;
      for (int i = 0; i < STANDART_SAMPLE_RATE; i++) {
        sine.fromSine(j);
      }
      float t3 = ((float)util.micros()) / 1000.0f / 1000.0f * 100.0f;
      for (int i = 0; i < STANDART_SAMPLE_RATE; i++) {
        saw.add(sine);
      }
      float t4 = ((float)util.micros()) / 1000.0f / 1000.0f * 100.0f;
      for (int i = 0; i < STANDART_SAMPLE_RATE; i++) {
        saw.amplify(testVariableFloat.get());
      }
      float t5 = ((float)util.micros()) / 1000.0f / 1000.0f * 100.0f;
      for (int i = 0; i < STANDART_SAMPLE_RATE; i++) {
        x[i%10] = saw.returnValue();
      }
      float t6 = ((float)util.micros()) / 1000.0f / 1000.0f * 100.0f;

      for (int i = 0; i < STANDART_SAMPLE_RATE; i++) {
        int index = i % 256;
        y[index] = testVariableFloat.get() + y[index];
      }
      float t7 = ((float)util.micros()) / 1000.0f / 1000.0f * 100.0f;

      sum += t3 - t2;
      count++;
      float average = sum / count;

      printf("SampleRate: %d, Bitdepth: %d, fromSaw: %f %%,  fromSine: %f %%, average fromSine : %f %%, add: %f %%, amplify: %f %%, return: %f %%, simpleMult: %f %%\r\n", STANDART_SAMPLE_RATE, BITS_PER_SAMPLE, t2 - t1, t3 - t2, average, t4 - t3, t5 - t4, t6 - t5, t7 - t6 );
      vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
    printf("%d", saw.returnValue());
    printf("%d", sine.returnValue());
    for (int i = 0; i < 10; i++) {
      printf("%d", x[i]);
      printf("%d", y[i]);
    }
  } 
}

// frequenzy: 35, Generate saw: 1.354980 %, generate sine: 6.885986 %, average Sine : 4.547216 %, amplify: 1.169922 %, add: 0.780029 %, return: 0.511963 %

#endif // SOUND_INPUT_TEST_H