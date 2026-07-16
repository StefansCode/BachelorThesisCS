#include "threadSaveInt.h"

ThreadSaveInt::ThreadSaveInt(int initialValue) {
  mutex = xSemaphoreCreateMutex();
  variable = initialValue;
}

void ThreadSaveInt::set(int value) {
  xSemaphoreTake(mutex, portMAX_DELAY);
  variable = value;
  xSemaphoreGive(mutex);
}

int ThreadSaveInt::get() {
  xSemaphoreTake(mutex, portMAX_DELAY);
  int value = variable;
  xSemaphoreGive(mutex);
  return value;
}