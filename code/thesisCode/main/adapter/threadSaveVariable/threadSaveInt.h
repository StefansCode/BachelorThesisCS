#ifndef THREAD_SAVE_INT_H
#define THREAD_SAVE_INT_H
#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"

class ThreadSaveInt {
public:
  ThreadSaveInt(int initialValue);
  void set(int value);
  int get();

private:
  SemaphoreHandle_t mutex;
  int variable;
};

#endif // THREAD_SAVE_INT_H