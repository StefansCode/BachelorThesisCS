#include "screen.h"

Screen screen;

static i2c_ssd1306_handle_t i2c_ssd1306;
static i2c_master_bus_handle_t i2c_master_bus;

void Screen::init() {
  /* I2C Master */
  i2c_master_bus_config_t i2c_master_bus_config = {};
  i2c_master_bus_config.i2c_port = I2C_NUM_0;
  i2c_master_bus_config.sda_io_num = PIN_I2C_SDA;
  i2c_master_bus_config.scl_io_num = PIN_I2C_SCL;
  i2c_master_bus_config.clk_source = I2C_CLK_SRC_DEFAULT;
  i2c_master_bus_config.glitch_ignore_cnt = 7;
  i2c_master_bus_config.flags.enable_internal_pullup = true;

  /* SSD1306 */
  i2c_ssd1306_config_t i2c_ssd1306_config = {};
  i2c_ssd1306_config.i2c_device_address = 0x3C;
  i2c_ssd1306_config.i2c_scl_speed_hz = 400000;
  i2c_ssd1306_config.width = 128;
  i2c_ssd1306_config.height = 64;
  i2c_ssd1306_config.wise = SSD1306_BOTTOM_TO_TOP;

  i2c_new_master_bus(&i2c_master_bus_config, &i2c_master_bus);
  i2c_ssd1306_init(i2c_master_bus, i2c_ssd1306_config, &i2c_ssd1306);
  i2c_ssd1306_buffer_clear(&i2c_ssd1306);
  i2c_ssd1306_buffer_to_ram(&i2c_ssd1306);
}

void Screen::clear() {
  i2c_ssd1306_buffer_clear(&i2c_ssd1306);
}

/** TODO: only update the changed pages by keeping the old buffer */
void Screen::display() {
  i2c_ssd1306_buffer_to_ram(&i2c_ssd1306);
}

void Screen::drawBitmap(const uint8_t *bitmap, int x, int y, int width, int height, bool invert) {
  i2c_ssd1306_buffer_image(&i2c_ssd1306, x, y, bitmap, width, height, invert);
}

void Screen::drawPixel(int x, int y, bool fill) {
  i2c_ssd1306_buffer_fill_pixel(&i2c_ssd1306, x, y, fill);
}

void Screen::drawString(const char* string, int x, int y, bool invert) {
  i2c_ssd1306_buffer_text(&i2c_ssd1306, x, y, string, invert);
}

