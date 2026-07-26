#ifndef TIMER_H
#define TIMER_H
#include "stdint.h"
#include "driver/gptimer.h"
#include "adapter/threadSaveVariable/threadSaveVariable.h"

class Timer {
private:
  gptimer_handle_t timerHandle = NULL;
  // EventGroupHandle_t eventHandle= NULL;
  ThreadSaveInt value;

public:
  Timer();
  uint64_t getValue();
  void setValue(uint64_t value);
  void increment();
  // bool waitForAlarm(uint8_t Ticket);
  // EventGroupHandle_t getEventhandle();
};

#endif // TIMER_H