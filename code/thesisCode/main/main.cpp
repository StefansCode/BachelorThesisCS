#include "adapter/button/button.h"
#include "adapter/dac/i2sDac.h"
#include "adapter/rgbLed/rgbLed.h"
#include "adapter/rotaryEncoder/rotaryEncoder.h"
#include "adapter/screen/screen.h"

#include "../resources/bitmaps.h"

#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <stdint.h>
#include <stdio.h>

const uint32_t SAMPLE_RATE = 44100;
const uint8_t BITS_PER_SAMPLE = 16;
typedef uint16_t sample;
const sample MAX_SAMPLE_VALUE = (1 << BITS_PER_SAMPLE) - 1;
const uint32_t BUFFER_SIZE = 512;

sample buffer[BUFFER_SIZE];
void DacTask(void *lul);
void ScreenTask(void *lul);
void fillBufferWithSaw(uint32_t freq);
void fillBufferWithChordAm();
void fillBufferWithChordG();

void EncodeLightButton();

RotaryEncoder rotaryEncoder;
Buttons button;
RgbLed rgbLed;
I2sDac dac;
Screen screen;

extern "C" void app_main(void) {

  xTaskCreate(DacTask, "dacTask", 4096, NULL, 5, NULL);
  xTaskCreate(ScreenTask, "screenTask", 4096, NULL, 4, NULL);
  EncodeLightButton();

  while (1) {
    printf("Main loop should not be reached...\r\n");
    vTaskDelay(pdMS_TO_TICKS(1000));
  }
}

void DacTask(void *lul) {
  dac.init(SAMPLE_RATE);
  while (1) {
    if (button.getState(PIN_BTN_A)) {
      fillBufferWithChordAm();
    } else if (button.getState(PIN_BTN_B)) {
      fillBufferWithChordG();
    } else {
      fillBufferWithSaw(440);
    }
    dac.sendBuffer(buffer, BUFFER_SIZE * sizeof(sample));
    // printf("Bytes written: %d  error: %d\r\n", bytes_written, dac.getError());
    //  printf(">lul:%d\r\n", y++);
    //  vTaskDelay(pdMS_TO_TICKS(3000));
  }
}

void ScreenTask(void *lul) {
  screen.init();
  screen.drawBitmap(Abra, 0, 0, 16, 16, false);
  screen.drawBitmap(coolguys, 0, 16, 128, 48, false);
  while (1) {
    screen.display();
    vTaskDelay(pdMS_TO_TICKS(2000));
    printf("Screen updated\r\n");
  }
}

uint64_t x = 0;
void fillBufferWithSaw(uint32_t freq) {
  for (int i = 0; i < BUFFER_SIZE; i++) {
    buffer[i] = ((((x * MAX_SAMPLE_VALUE * freq) / SAMPLE_RATE)) % MAX_SAMPLE_VALUE) / 30;
    // printf(">signal:%d\r\n", buffer[i]);
    //  Weil ja alles in Hz also pro secunde ist
    x = (x + 1) % SAMPLE_RATE;
  }
}

void fillBufferWithChordAm() {
  uint32_t freq1 = 440;
  uint32_t freq2 = 523;
  uint32_t freq3 = 659;
  for (int i = 0; i < BUFFER_SIZE; i++) {
    buffer[i] = ((((((x * MAX_SAMPLE_VALUE * freq1) / SAMPLE_RATE)) % MAX_SAMPLE_VALUE) / 30) + (((((x * MAX_SAMPLE_VALUE * freq2) / SAMPLE_RATE)) % MAX_SAMPLE_VALUE) / 30) + (((((x * MAX_SAMPLE_VALUE * freq3) / SAMPLE_RATE)) % MAX_SAMPLE_VALUE) / 30));
    // printf(">signal:%d\r\n", buffer[i]);
    //  Weil ja alles in Hz also pro secunde ist
    x = (x + 1) % SAMPLE_RATE;
  }
}

void fillBufferWithChordG() {
  uint32_t freq1 = 392;
  uint32_t freq2 = 494;
  uint32_t freq3 = 587;
  for (int i = 0; i < BUFFER_SIZE; i++) {
    buffer[i] = ((((((x * MAX_SAMPLE_VALUE * freq1) / SAMPLE_RATE)) % MAX_SAMPLE_VALUE) / 30) + (((((x * MAX_SAMPLE_VALUE * freq2) / SAMPLE_RATE)) % MAX_SAMPLE_VALUE) / 30) + (((((x * MAX_SAMPLE_VALUE * freq3) / SAMPLE_RATE)) % MAX_SAMPLE_VALUE) / 30));
    // printf(">signal:%d\r\n", buffer[i]);
    //  Weil ja alles in Hz also pro secunde ist
    x = (x + 1) % SAMPLE_RATE;
  }
}

void EncodeLightButton() {

  rotaryEncoder.init();
  button.init();
  rgbLed.init();

  uint8_t color = 0;
  uint8_t lightLvl = 0;
  int lastEncoderValue = 0;

  while (1) {
    int v = rotaryEncoder.getvalue();
    uint32_t allButton = button.getStateAll();
    uint8_t queue = button.readQueue();
    if (queue == PIN_ENCODER_SW) {
      color = (color + 1) % 3;
    }
    if (v > lastEncoderValue && lightLvl < 15 && (v - lastEncoderValue) < 128) {
      lightLvl++;
    } else if (v < lastEncoderValue && lightLvl > 0 && (lastEncoderValue - v) < 128) {
      lightLvl--;
    }
    lastEncoderValue = v;
    printf("Encoder value: %d  lightLvl: %d  queue: %d  buttonState: ", v, lightLvl, queue);
    for (int i = 0; i < 32; i++) {
      printf("%d", int((allButton >> i) & (1U)));
    }
    printf("\r\n");
    if (color == 0) {
      rgbLed.set(lightLvl * 16, 0, 0);
    } else if (color == 1) {
      rgbLed.set(0, lightLvl * 16, 0);
    } else {
      rgbLed.set(0, 0, lightLvl * 16);
    }
    rgbLed.on();
    vTaskDelay(pdMS_TO_TICKS(100));
  }
}