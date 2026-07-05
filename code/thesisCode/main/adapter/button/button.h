#ifndef BUTTON_H
#define BUTTON_H
#include "../pinDefines.h"
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"

class Buttons {
public:
  void init();
  uint8_t readQueue();
  uint8_t getState(uint8_t pin);
  uint32_t getStateAll();
};

extern Buttons buttons;

#endif // BUTTON_H