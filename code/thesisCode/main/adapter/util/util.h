#ifndef UTIL_H
#define UTIL_H

#include <esp_timer.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

class Util {
public:
    unsigned long millis();
    unsigned long micros();
    void delay(unsigned long ms);
};

extern Util util;
#endif // UTIL_H