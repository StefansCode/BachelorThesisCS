#ifndef THREAD_SAVE_BOOL_H
#define THREAD_SAVE_BOOL_H
#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"

class ThreadSaveBool {
public:
  ThreadSaveBool(bool initialValue);
  void set(bool value);
  bool get();

private:
  SemaphoreHandle_t mutex;
  bool variable;
};

#endif // THREAD_SAVE_BOOL_H