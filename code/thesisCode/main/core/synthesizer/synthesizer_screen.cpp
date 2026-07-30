#include "synthesizer.h"

void Synthesizer::screenTask(void *param) {

  screen.clear();
  screen.drawBitmap(Abra, 0, 0, 16, 16, false);
  menu.drawUnselected();
  screen.display();

  while (1) {
    screen.clear();

    bool somethingChanged = false;

    uint8_t queue = buttons.readQueue();
    int encoderValue = encoder.getvalue();

    if (menu.leaveIsSelected()) {
      handelValueChange();
      if (queue == PIN_BTN_B) {
        encoder.resetvalue();
        lastEncoderValue = 0;
        somethingChanged = menu.moveBack();
      }
      menu.drawSelected("LIL", "LAL", "LOL");
    } else {
      somethingChanged = navigateMenuWithEncoder(encoderValue);
      if (queue == PIN_BTN_A) {
        somethingChanged = menu.moveForward();
      }
      if (queue == PIN_BTN_B) {
        somethingChanged = menu.moveBack();
      }
      menu.drawUnselected();
    }

    if (1) {
      screen.drawBitmap(Abra, 0, 0, 16, 16, false);
      screen.display();
    }
    util.delay(100);
  }
}

bool Synthesizer::navigateMenuWithEncoder(int encoderValue) {

  bool somethingChanged = false;

  if (lastEncoderValue != encoderValue) {
    int diff = encoderValue - lastEncoderValue;
    if ((diff > 0 && diff < 180) || diff < -180) {
      somethingChanged = menu.moveDown();
    } else if ((diff < 0 && diff > -180) || diff > 180) {
      somethingChanged = menu.moveUp();
    }
  }
  lastEncoderValue = encoderValue;

  return somethingChanged;
}

void Synthesizer::handelValueChange() {
  /** @todo */
}