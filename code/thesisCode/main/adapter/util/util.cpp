#include "util.h"

Util util;

unsigned long Util::millis() {
  return esp_timer_get_time() / 1000;
}

unsigned long Util::micros() {
  return esp_timer_get_time();
}

void Util::delay(unsigned long ms) {
  vTaskDelay(ms/portTICK_PERIOD_MS);
}