#include "timer.h"

bool timerAlarmCallback(gptimer_handle_t timer, const gptimer_alarm_event_data_t *edata, void *user_ctx) {
  Timer *givenTimer = (Timer *)user_ctx;
  givenTimer->increment();
  // xEventGroupSetBitsFromISR(givenTimer->getEventhandle(), 0xFF, 0);
  return true;
}

Timer::Timer() : value(0) {

  // eventHandle = xEventGroupCreate();

  gptimer_config_t timerConfig = {};
  timerConfig.clk_src = GPTIMER_CLK_SRC_DEFAULT;
  timerConfig.direction = GPTIMER_COUNT_UP;
  timerConfig.resolution_hz = 16 * 16 * 16 * 16;

  gptimer_new_timer(&timerConfig, &timerHandle);

  gptimer_alarm_config_t alarmConfig = {};
  alarmConfig.reload_count = 0;
  alarmConfig.alarm_count = 16 * 16 * 16;
  alarmConfig.flags.auto_reload_on_alarm = true;

  gptimer_set_alarm_action(timerHandle, &alarmConfig);

  gptimer_event_callbacks_t alarmCallback = {};
  alarmCallback.on_alarm = timerAlarmCallback;

  gptimer_register_event_callbacks(timerHandle, &alarmCallback, this);


  gptimer_enable(timerHandle);

  gptimer_start(timerHandle);
}

uint64_t Timer::getValue() {
  // uint64_t value;
  // gptimer_get_raw_count(timerHandle, &value);
  return value.get();
}

void Timer::setValue(uint64_t newValue) {
  // gptimer_set_raw_count(timerHandle, value);
  value.set(newValue);
}

void Timer::increment() {
  value.set(value.get() + 1);
}

// bool Timer::waitForAlarm(uint8_t Ticket) {
//   uint8_t requestedBit = 1U << Ticket;
//   EventBits_t setBits = xEventGroupWaitBits(eventHandle, requestedBit, pdTRUE, pdTRUE, portMAX_DELAY);
//   if ((setBits & requestedBit) == requestedBit) {
//     return true;
//   }
//   return false;
// }

// EventGroupHandle_t Timer::getEventhandle() {
//   return eventHandle;
// }