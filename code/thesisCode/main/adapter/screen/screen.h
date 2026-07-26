#ifndef SCREEN_H
#define SCREEN_H
#include "../resources/bitmaps.h"
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
  void drawString(const char* string, int x, int y, bool invert);
};

extern Screen screen;

#endif // SCREEN_H