#include "synthesizer.h"

void Synthesizer::screenTask(void *param) {

  unsigned int lastEncoderValue = 0;

  screen.clear();
  screen.drawBitmap(Abra, 0, 0, 16, 16, false);
  menu.draw();
  screen.display();

  while (1) {
    bool somethingChanged = false;

    uint8_t queue = buttons.readQueue();

    if (queue == PIN_BTN_A) {
      if (menu.indexIsOnLeaf()) {
        /** @todo start value change save changes*/
      } else {
        somethingChanged = menu.moveForward();
      }
    }
    if (queue == PIN_BTN_B) {
      somethingChanged = menu.moveBack();
    }

    int encodervalue = encoder.getvalue();

    if (lastEncoderValue != encodervalue) {
      int diff = encodervalue - lastEncoderValue;
      if ((diff > 0 && diff < 180) || diff < -180) {
        somethingChanged = menu.moveDown();
      } else if ((diff < 0 && diff > -180) || diff > 180) {
        somethingChanged = menu.moveUp();
      }
    }
    lastEncoderValue = encodervalue;

    if (somethingChanged) {
      screen.clear();
      screen.drawBitmap(Abra, 0, 0, 16, 16, false);
      menu.draw();
      screen.display();
    }
    util.delay(100);
  }
}