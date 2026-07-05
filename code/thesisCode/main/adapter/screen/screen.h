#ifndef SCREEN_H
#define SCREEN_H
#include "../pinDefines.h"
#include <stdint.h>
extern "C" {
#include "SSD1306/ssd1306.h"
}

class Screen {
public:
  void init();
  void clear();
  void display();
  void drawBitmap(const uint8_t *bitmap, int x, int y, int width, int height, bool invert);
  void drawPixel(int x, int y, bool fill);
};

extern Screen screen;

#endif // SCREEN_H