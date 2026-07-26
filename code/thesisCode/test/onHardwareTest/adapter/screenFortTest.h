#ifndef SCREEN_FONT_TEST_H
#define SCREEN_FONT_TEST_H
#include "adapter/screen/screen.h"
#include "adapter/util/util.h"

void runScreenFontTest() {
  /** 
   * Not possible:
   * § 
   * should be possible:
   * \
  */
  screen.drawString("ABCDEFGHIJKLMNOP", 0, 0, false);
  screen.drawString("QRSTUVWXYZ123456", 0, 16, false);
  screen.drawString("[]{}!$%&/()=?+*", 0, 32, false);
  screen.drawString("#',;.:-_@<>|^~ ", 0, 48, false);
  screen.display();
  while (1) {
    util.delay(1000);
  }
}

#endif // SCREEN_FONT_TEST_H