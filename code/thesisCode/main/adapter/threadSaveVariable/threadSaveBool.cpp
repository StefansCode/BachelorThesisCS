#include "threadSaveBool.h"

ThreadSaveBool::ThreadSaveBool(bool initialValue) {
  mutex = xSemaphoreCreateMutex();
  variable = initialValue;
}

void ThreadSaveBool::set(bool value) {
  xSemaphoreTake(mutex, portMAX_DELAY);
  variable = value;
  xSemaphoreGive(mutex);
}

bool ThreadSaveBool::get() {
  xSemaphoreTake(mutex, portMAX_DELAY);
  bool value = variable;
  xSemaphoreGive(mutex);
  return value;
}