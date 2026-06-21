/**
 * https://docs.espressif.com/projects/esp-idf/en/stable/esp32/api-reference/peripherals/i2s.html#std-tx-mode *
 *
 */
#include "i2sDac.h"
#include "../pinDefines.h"
#include <portmacro.h> // for portMAX_DELAY

i2s_chan_handle_t i2s_tx_handle;

esp_err_t I2sDac::init(unsigned int sampleRate) {

  i2s_chan_config_t chan_cfg = I2S_CHANNEL_DEFAULT_CONFIG(I2S_NUM_AUTO, I2S_ROLE_MASTER);

  i2s_std_config_t i2s_config = {
      .clk_cfg = I2S_STD_CLK_DEFAULT_CONFIG(sampleRate),
      .slot_cfg = I2S_STD_PHILIPS_SLOT_DEFAULT_CONFIG(I2S_DATA_BIT_WIDTH_16BIT, I2S_SLOT_MODE_MONO),
      .gpio_cfg = {
          .mclk = I2S_GPIO_UNUSED,
          .bclk = PIN_I2S_BCLK,
          .ws = PIN_I2S_WS,
          .dout = PIN_I2S_DOUT,
          .din = I2S_GPIO_UNUSED,
          .invert_flags = {
              .mclk_inv = false,
              .bclk_inv = false,
              .ws_inv = false}}};

  this->error = i2s_new_channel(&chan_cfg, &i2s_tx_handle, NULL);

  if (this->error != ESP_OK) {
    return this->error;
  }

  this->error = i2s_channel_init_std_mode(i2s_tx_handle, &i2s_config);

  if (this->error != ESP_OK) {
    return this->error;
  }

  this->error = i2s_channel_enable(i2s_tx_handle);
  if (this->error != ESP_OK) {
    return this->error;
  } else {
    return ESP_OK;
  }
}

size_t I2sDac::sendBuffer(const void *buffer, unsigned int len) {

  size_t bytes_written;

  this->error = i2s_channel_write(i2s_tx_handle, buffer, len, &bytes_written, portMAX_DELAY);

  return bytes_written;
}

esp_err_t I2sDac::getError() {
  return this->error;
}