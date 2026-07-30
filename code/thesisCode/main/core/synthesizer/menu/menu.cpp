#include "menu.h"

Menu::Menu() {
  // addChild(&root, &drums);
  addChild(&root, &bass);
  addChild(&root, &lead);
  addChild(&root, &settings);

  addChild(&bass, &bass_onOff);
  addChild(&bass, &bass_note);
  addChild(&bass, &bass_waveform);
  addChild(&bass, &bass_LFO);

  addChild(&lead, &lead_scale);
  addChild(&lead, &lead_waveform);
  addChild(&lead, &lead_envelope);
  addChild(&lead, &lead_filter);
  addChild(&lead, &lead_fx);

  addChild(&settings, &settings_sampleRate);
}

void Menu::addChild(entry_t *target, entry_t *child) {
  if (target->numberOfChildren < 7) {
    unsigned int freeIndex = target->numberOfChildren;
    target->children[freeIndex] = child;
    target->numberOfChildren++;
  }
}

bool Menu::moveBack() {
  if (leaveIsSelected_intern) {
    leaveIsSelected_intern = false;
    return true;
  } else if (current->parent != NULL) {
    current = current->parent;
    index = 0;
    return true;
  } else {
    return false;
  }
}

bool Menu::moveForward() {
  if (current->children[index]->numberOfChildren != 0) {
    current = current->children[index];
    index = 0;
    return true;
  } else if (!leaveIsSelected_intern) {
    leaveIsSelected_intern = true;
    return true;
  } else {
    return false;
  }
}

bool Menu::moveUp() {
  if (index > 0) {
    index--;
    return true;
  } else {
    return false;
  }
}

bool Menu::moveDown() {
  if (index + 1 < current->numberOfChildren) {
    index++;
    return true;
  } else {
    return false;
  }
}

unsigned int Menu::getID() {
  return current->id;
}
const char *Menu::getName() {
  return current->name;
}
void Menu::setValue(const char *newValue) {
  current->value = newValue;
}

/** @todo maybe move into seperat class/komponent and or use more variables for position*/
#define VALUE_X 80
void Menu::drawUnselected() {
  /** draw Headline */
  screen.drawString(current->name, 16, 2, false);
  if (current->numberOfChildren == 0) {
    return;
  }

  /* draw index - 1*/
  if (index > 0) {
    screen.drawString(current->children[index - 1]->name, 16, 16, false);
    if (current->children[index - 1]->value != NULL) {
      screen.drawString(current->children[index - 1]->value, VALUE_X, 16, false);
    }
  }

  /** draw index */
  screen.drawString("->", 0, 32, false);
  screen.drawString(current->children[index]->name, 16, 32, false);

  if (current->children[index]->value == NULL) {
    screen.drawString("->", 112, 32, false);
  } else {
    screen.drawString(current->children[index]->value, VALUE_X, 32, false);
  }

  /** draw index + 1 */
  if (index + 1 < current->numberOfChildren) {
    screen.drawString(current->children[index + 1]->name, 16, 48, false);
    if (current->children[index + 1]->value != NULL) {
      screen.drawString(current->children[index + 1]->value, VALUE_X, 48, false);
    }
  }
}

void Menu::drawSelected(const char *lastValue, const char *currentValue, const char *nextValue) {

  screen.drawString(current->name, 16, 2, false);

  if (current->children[index]->value == NULL) {
    screen.drawString("->", VALUE_X - 16, 2, false);
    screen.drawString(current->children[index]->name, VALUE_X, 2, false);
    return;// the rest is handled externaly
  }

  screen.drawString(current->children[index]->name, 16, 32, false);
  screen.drawString("->", VALUE_X - 16, 32, false);
  if(lastValue != NULL) {
    screen.drawString(lastValue, VALUE_X, 16, false);
  }
  screen.drawString(currentValue, VALUE_X, 32, false);
  if(nextValue != NULL) {
    screen.drawString(nextValue, VALUE_X, 48, false);
  }
}

bool Menu::leaveIsSelected() {
  if (leaveIsSelected_intern) {
    return true;
  } else {
    return false;
  }
}