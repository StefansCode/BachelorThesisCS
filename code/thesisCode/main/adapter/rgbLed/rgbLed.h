#ifndef RGB_LED_H
#define RGB_LED_H
#include "../pinDefines.h"
#include "esp_log.h"
#include "led_strip.h"
#include <stdint.h>

class RgbLed {
public:
  void init();
  uint8_t getR();
  uint8_t getG();
  uint8_t getB();
  void set(uint8_t R, uint8_t G, uint8_t B);
  void on();
  void off();
  void blink(uint32_t delayMs);
  void pulse(uint32_t delayMs);

private:
  uint8_t RState = 0;
  uint8_t GState = 0;
  uint8_t BState = 0;
};

extern RgbLed rgbLed;

#endif // RGB_LED_H