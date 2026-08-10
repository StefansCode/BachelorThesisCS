#ifndef SOUND_OUTPUT_TEST_H
#define SOUND_OUTPUT_TEST_H

#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <stdint.h>
#include <stdio.h>

//#include "../test/onHardwareTest/core/sound/soundInputTest.h"

#include "adapter/button/button.h"
#include "adapter/dac/i2sDac.h"
#include "adapter/Encoder/Encoder.h"

#include "core/sound/sound.h"

Sound sound;
float apmlifier = 0.01;

void sendData(sample *data, void *param) {
  unsigned int len = *(unsigned int *)param;
  dac.sendBuffer(data, len);
}

int lastEncoderValue = 0;
void encoderChangeValue(float *variable, float min, float max, float step) {
  int v = encoder.getvalue();
  if (v > lastEncoderValue && *variable < max && (v - lastEncoderValue) < 128) {
    *variable += step;
  } else if (v < lastEncoderValue && *variable > min && (lastEncoderValue - v) < 128) {
    *variable -= step;
  }
  lastEncoderValue = v;
}

void SoundTask(void *param) {
  unsigned int len = BUFFER_SIZE * sizeof(sample);
  uint8_t waveform = 0;
  while (1) {
    encoderChangeValue(&apmlifier, 0.0, 1.0, 0.01);
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

    sound.amplify(apmlifier).toFunction(sendData, (void *)&len);
    // vTaskDelay(20/portTICK_PERIOD_MS);
  }
}

void runSoundOutputTest(void) {

  xTaskCreate(SoundTask, "SoundTask", 4096, NULL, 5, NULL);

  while (1) {
    printf("amplifier: %f\n", apmlifier);
    
    vTaskDelay(100 / portTICK_PERIOD_MS);
  }
}


uint16_t buffer[BUFFER_SIZE] = {0};

void fillBufferWithSaw(uint64_t time, uint32_t freq, uint32_t divisor) {
  for (int i = 0; i < BUFFER_SIZE; i++) {
    buffer[i] = ((((time * UINT16_MAX * freq) / STANDART_SAMPLE_RATE)) % UINT16_MAX) / divisor;
    time = (time + 1) % STANDART_SAMPLE_RATE;
  }
}
uint64_t globalTime = 0;
void sendUnsignded(void* lal) {
  while(1) {
    encoderChangeValue(&apmlifier, 0.0, 1.0, 0.01);
    fillBufferWithSaw(globalTime, 440, (uint32_t)(1.0 / apmlifier));
    dac.sendBuffer(buffer, BUFFER_SIZE * 2);
  }
}

void runSoundOutputTest_unsigned(void) {

  xTaskCreate(sendUnsignded, "SoundTaskUnsigned", 4096, NULL, 5, NULL);

  while (1) {
    printf("amplifier: %f\n", apmlifier);
    
    vTaskDelay(100 / portTICK_PERIOD_MS);
  }
}

#endif // SOUND_OUTPUT_TEST_H