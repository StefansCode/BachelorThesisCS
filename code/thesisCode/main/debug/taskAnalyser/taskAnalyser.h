#ifndef TASK_ANALYSER_H
#define TASK_ANALYSER_H
#include "stdint.h"
#include "sdkconfig.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <inttypes.h>
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gptimer.h"

class TaskAnalyser {
public:
  TaskAnalyser();
  void startTimerWithId(uint8_t id);
  void stopTimerWithId(uint8_t id);
};

#endif // TASK_ANALYSER_H