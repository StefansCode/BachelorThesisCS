#include "Encoder.h"

Encoder encoder;

#define FILTER_VALUE 1000

#define MAX_ENCODER_VALUE 255
#define MIN_ENCODER_VALUE -255

pcnt_unit_handle_t pcnt_unit = NULL;

Encoder::Encoder() {}

void Encoder::init() {
  /* set min and max values */
  pcnt_unit_config_t unit_config = {};
  unit_config.high_limit = MAX_ENCODER_VALUE * 4;
  unit_config.low_limit = MIN_ENCODER_VALUE * 4;

  ESP_ERROR_CHECK(pcnt_new_unit(&unit_config, &pcnt_unit));

  /* set glitch filter */
  pcnt_glitch_filter_config_t filter_config = {};
  filter_config.max_glitch_ns = FILTER_VALUE;
  ESP_ERROR_CHECK(pcnt_unit_set_glitch_filter(pcnt_unit, &filter_config));

  /* install pcnt channels*/
  pcnt_chan_config_t chan_a_config = {};
  chan_a_config.edge_gpio_num = PIN_ENCODER_CLK;
  chan_a_config.level_gpio_num = PIN_ENCODER_DT;

  pcnt_channel_handle_t pcnt_chan_a = NULL;
  ESP_ERROR_CHECK(pcnt_new_channel(pcnt_unit, &chan_a_config, &pcnt_chan_a));

  pcnt_chan_config_t chan_b_config = {};
  chan_b_config.edge_gpio_num = PIN_ENCODER_DT;
  chan_b_config.level_gpio_num = PIN_ENCODER_CLK;

  pcnt_channel_handle_t pcnt_chan_b = NULL;
  ESP_ERROR_CHECK(pcnt_new_channel(pcnt_unit, &chan_b_config, &pcnt_chan_b));

  ESP_ERROR_CHECK(pcnt_channel_set_edge_action(pcnt_chan_a, PCNT_CHANNEL_EDGE_ACTION_DECREASE, PCNT_CHANNEL_EDGE_ACTION_INCREASE));
  ESP_ERROR_CHECK(pcnt_channel_set_level_action(pcnt_chan_a, PCNT_CHANNEL_LEVEL_ACTION_KEEP, PCNT_CHANNEL_LEVEL_ACTION_INVERSE));
  ESP_ERROR_CHECK(pcnt_channel_set_edge_action(pcnt_chan_b, PCNT_CHANNEL_EDGE_ACTION_INCREASE, PCNT_CHANNEL_EDGE_ACTION_DECREASE));
  ESP_ERROR_CHECK(pcnt_channel_set_level_action(pcnt_chan_b, PCNT_CHANNEL_LEVEL_ACTION_KEEP, PCNT_CHANNEL_LEVEL_ACTION_INVERSE));

  ESP_ERROR_CHECK(pcnt_unit_enable(pcnt_unit));
  ESP_ERROR_CHECK(pcnt_unit_clear_count(pcnt_unit));
  ESP_ERROR_CHECK(pcnt_unit_start(pcnt_unit));
}

int Encoder::getvalue() {
  int pulse_count;
  ESP_ERROR_CHECK(pcnt_unit_get_count(pcnt_unit, &pulse_count));
  return pulse_count / 4;
}

int Encoder::getLastValue() {
  return lastEncoderValue;
}

void Encoder::resetvalue() {
  ESP_ERROR_CHECK(pcnt_unit_clear_count(pcnt_unit));
  lastEncoderValue = 0;
}

void Encoder::changeExternalValue(ThreadSaveInt &value, int min, int max, int step) {

  int encoderValue = getvalue();

  if (encoderValue > lastEncoderValue && value.get() < max && (encoderValue - lastEncoderValue) < 128) {
    value.set(value.get() + step);
  } else if (encoderValue < lastEncoderValue && value.get() > min && (lastEncoderValue - encoderValue) < 128) {
    value.set(value.get() - step);
  }

  lastEncoderValue = encoderValue;
}