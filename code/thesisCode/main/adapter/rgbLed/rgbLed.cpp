#include "rgbLed.h"

led_strip_handle_t led_strip;

void RgbLed::init() {
  led_strip_config_t strip_config = {
      .strip_gpio_num = BUILDIN_RGB_LED,
      .max_leds = 1, // at least one LED on board
  };
  led_strip_rmt_config_t rmt_config = {};
  rmt_config.resolution_hz = 10 * 1000 * 1000; // 10MHz
  rmt_config.flags.with_dma = false;
  ESP_ERROR_CHECK(
      led_strip_new_rmt_device(&strip_config, &rmt_config, &led_strip));
}

uint8_t RgbLed::getR() { return RState; }

uint8_t RgbLed::getG() { return GState; }

uint8_t RgbLed::getB() { return BState; }

void RgbLed::set(uint8_t R, uint8_t G, uint8_t B) {
  RState = R;
  GState = G;
  BState = B;
}

void RgbLed::on() {
  led_strip_set_pixel(led_strip, 0, RState, GState, BState);
  led_strip_refresh(led_strip);
}

void RgbLed::off() {
  led_strip_set_pixel(led_strip, 0, 0, 0, 0);
  led_strip_refresh(led_strip);
}

void RgbLed::blink(uint32_t delayMs) {
  on();
  vTaskDelay(pdMS_TO_TICKS(delayMs));
  off();
  vTaskDelay(pdMS_TO_TICKS(delayMs));
}

void RgbLed::pulse(uint32_t delayMs) {
  for (int i = 0; i < 20; i++) {
    led_strip_set_pixel(led_strip, 0, 
                        (abs(i - 10) * RState) / 10,
                        (abs(i - 10) * GState) / 10, 
                        (abs(i - 10) * BState) / 10);
    led_strip_refresh(led_strip);
    vTaskDelay(pdMS_TO_TICKS(delayMs));
  }
}