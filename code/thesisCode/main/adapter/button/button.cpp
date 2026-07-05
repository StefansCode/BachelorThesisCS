#include "button.h"

Buttons buttons;

#define PIN_MSK (1ULL << PIN_BTN_11) | (1ULL << PIN_BTN_12) | (1ULL << PIN_BTN_13) | (1ULL << PIN_BTN_14) |     \
                    (1ULL << PIN_BTN_21) | (1ULL << PIN_BTN_22) | (1ULL << PIN_BTN_23) | (1ULL << PIN_BTN_24) | \
                    (1ULL << PIN_BTN_A) | (1ULL << PIN_BTN_B) | (1ULL << PIN_ENCODER_SW)

#define DEBOUNCE_TIME_MS 200

static QueueHandle_t gpio_evt_queue = NULL;

TickType_t last_interrupt_time = 0;

uint8_t pinNums[11] = {
    PIN_BTN_11, PIN_BTN_12, PIN_BTN_13, PIN_BTN_14,
    PIN_BTN_21, PIN_BTN_22, PIN_BTN_23, PIN_BTN_24,
    PIN_BTN_A, PIN_BTN_B, PIN_ENCODER_SW};

static void IRAM_ATTR button_isr_handler(void *arg) {
  uint8_t pin = *(uint8_t *)arg;
  if ((xTaskGetTickCountFromISR() - last_interrupt_time) < pdMS_TO_TICKS(DEBOUNCE_TIME_MS)) {
    return; // debounce
  }
  if (gpio_get_level((gpio_num_t)pin) == 1) {
    return; // We only care about falling edge
  }
  last_interrupt_time = xTaskGetTickCountFromISR();
  xQueueSendFromISR(gpio_evt_queue, &pin, NULL);
}

void Buttons::init() {
  gpio_config_t io_conf = {};
  io_conf.intr_type = GPIO_INTR_NEGEDGE;
  io_conf.mode = GPIO_MODE_INPUT;
  io_conf.pin_bit_mask = PIN_MSK;
  io_conf.pull_down_en = GPIO_PULLDOWN_DISABLE;
  io_conf.pull_up_en = GPIO_PULLUP_ENABLE;
  gpio_config(&io_conf);

  gpio_install_isr_service(0);
  gpio_evt_queue = xQueueCreate(10, sizeof(uint8_t));
  for (uint8_t pin = 0; pin < 11; pin++) {
    gpio_isr_handler_add((gpio_num_t)pinNums[pin], button_isr_handler, (void *)(pinNums + pin));
  }
}

uint8_t Buttons::readQueue() {
  uint8_t pin;
  if (xQueueReceive(gpio_evt_queue, &pin, 0) == pdTRUE) {
    return pin;
  }
  return 255; // No event
}

uint8_t Buttons::getState(uint8_t pin) {
  return !gpio_get_level((gpio_num_t)pin);
}

uint32_t Buttons::getStateAll() {
  uint32_t state = 0;
  for (uint8_t pin = 0; pin < 32; pin++) {
    if ((PIN_MSK) & (1ULL << pin)) {
      state |= (getState(pin) << pin);
    }
  }
  return state;
}