#ifndef I2S_DAC_H
#define I2S_DAC_H
#include "driver/i2s_std.h"
#include <stdint.h>

class I2sDac {
public:
  esp_err_t init(unsigned int sampleRate, unsigned int bitsPerSample);
  size_t sendBuffer(const void *buffer, unsigned int len);
  esp_err_t getError();

private:
  esp_err_t error = ESP_OK;
};

extern I2sDac dac;

#endif // I2S_DAC_H