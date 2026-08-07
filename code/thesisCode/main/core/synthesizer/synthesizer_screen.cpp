#include "string.h"
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
      somethingChanged = handelValueChange(queue);
    } else {
      somethingChanged = navigateMenuWithEncoder(encoderValue);
      if (queue == PIN_BTN_A) {
        encoder.resetvalue();
        lastEncoderValue = 0;
        somethingChanged = menu.moveForward();
      }
      if (queue == PIN_BTN_B) {
        encoder.resetvalue();
        lastEncoderValue = 0;
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

bool Synthesizer::handelValueChange(uint8_t queue) {

  if (strcmp(menu.getName(), "BASS") == 0) {
    if (strcmp(menu.getSelectedName(), "SWITCH") == 0) {
      return handleVariableChange(queue, bassPlay);
    } else if (strcmp(menu.getSelectedName(), "NOTE") == 0) {
      return handleVariableChange(queue, bassNote);
    } else if (strcmp(menu.getSelectedName(), "WAVE") == 0) {
      return handleVariableChange(queue, bassWaveform);
    } else {
      return handleTODO(queue);
    }
  } else if (strcmp(menu.getName(), "LEAD") == 0) {
    if(strcmp(menu.getSelectedName(), "SCALE") == 0) {
      return handleVariableChange(queue, leadScale);
    } else if(strcmp(menu.getSelectedName(), "WAVE") == 0) {
      return handleVariableChange(queue, leadWaveform);
    }else {
      return handleTODO(queue);
    }
    return handleTODO(queue);
  } else if (strcmp(menu.getName(), "ENV") == 0) {
    if(strcmp(menu.getSelectedName(), "ATK") == 0) {
      return handleVariableChange(queue, envelopeAttack);
    } else if(strcmp(menu.getSelectedName(), "DCY") == 0) {
      return handleVariableChange(queue, envelopeDecay);
    } else if(strcmp(menu.getSelectedName(), "SUS") == 0) {
      return handleVariableChange(queue, envelopeSustain);
    } else if(strcmp(menu.getSelectedName(), "REL") == 0) {
      return handleVariableChange(queue, envelopeRelease);
    } else {
      return handleTODO(queue);
    }
  }
  else if (strcmp(menu.getName(), "SETTINGS") == 0) {
    return handleTODO(queue);
  }
  else {
    return handleTODO(queue);
  }
  return false;
}

bool Synthesizer::handleVariableChange(uint8_t queue, ThreadSaveInt &variable) {

  bool somethingChanged = false;
  int step = 1;
  /** @todo das ist nicht gut. */
  if(strcmp(menu.getSelectedName(), "ATK") == 0 || strcmp(menu.getSelectedName(), "DCY") == 0 || strcmp(menu.getSelectedName(), "SUS") == 0 || strcmp(menu.getSelectedName(), "REL") == 0) {
    step = 8;
  }

  encoder.changeExternalValue(variable, 0, menu.getValuesLength() - step, step);
  menu.drawSelected(variable.get());

  if (queue == PIN_BTN_A) {
    encoder.resetvalue();
    lastEncoderValue = 0;
    menu.setSelectedValueIndex(variable.get());
    somethingChanged = menu.moveBack();
  }
  if (queue == PIN_BTN_B) {
    encoder.resetvalue();
    lastEncoderValue = 0;
    variable.set(menu.getSelectedValueIndex());
    somethingChanged = menu.moveBack();
  }

  return somethingChanged;
}

bool Synthesizer::handleTODO(uint8_t queue) {
  screen.drawString("TODO", 64 - 16, 32, false);
  if (queue == PIN_BTN_A) {
    encoder.resetvalue();
    lastEncoderValue = 0;
    return menu.moveBack();
  }
  if (queue == PIN_BTN_B) {
    encoder.resetvalue();
    lastEncoderValue = 0;
    return menu.moveBack();
  }
  return false;
}