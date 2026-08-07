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

  addChild(&lead_envelope, &bass_envelope_attack);
  addChild(&lead_envelope, &bass_envelope_decay);
  addChild(&lead_envelope, &bass_envelope_sustain);
  addChild(&lead_envelope, &bass_envelope_release);

  addChild(&settings, &settings_sampleRate);
}

void Menu::addChild(entry_t *target, entry_t *child) {
  if (target->numberOfChildren < 7) {
    unsigned int freeIndex = target->numberOfChildren;
    target->children[freeIndex] = child;
    target->numberOfChildren++;
  }
}

const char * Menu::getValue(entry_t *entry) {
  if (entry->values == NULL) {
    return NULL;
  }
  return entry->values[entry->indexOfValue];
}

void Menu::setValueIndex(entry_t *entry, int index) {
  if (entry->values == NULL) {
    entry->indexOfValue = index;
    return;
  }
  if (index < 0 || index >= entry->numberOfValues) {
    return;
  }
  entry->indexOfValue = index;
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

const char *Menu::getName() {
  return current->name;
}
const char *Menu::getSelectedName() {
  return current->children[index]->name;
}

int Menu::getSelectedValueIndex() {
  return current->children[index]->indexOfValue;
}
void Menu::setSelectedValueIndex(int index) {
  setValueIndex(current->children[this->index], index);
}

int Menu::getValuesLength() {
  return current->children[index]->numberOfValues;
}

/** @todo maybe move into seperat class/komponent and or use more variables for position
 * and better variable use
*/
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
    if (getValue(current->children[index - 1]) != NULL) {
      screen.drawString(getValue(current->children[index - 1]), VALUE_X, 16, false);
    } else if(current->children[index - 1]->numberOfValues != 0) {
      screen.drawNumber(current->children[index - 1]->indexOfValue, VALUE_X, 16, false);
    }
  }

  /** draw index */
  screen.drawString("->", 0, 32, false);
  screen.drawString(current->children[index]->name, 16, 32, false);

  if (getValue(current->children[index]) != NULL) {
    screen.drawString(getValue(current->children[index]), VALUE_X, 32, false);
  } else if (current->children[index]->numberOfValues != 0) {
    screen.drawNumber(current->children[index]->indexOfValue, VALUE_X, 32, false);
  }else {
    screen.drawString("->", 112, 32, false);
  }

  /** draw index + 1 */
  if (index + 1 < current->numberOfChildren) {
    screen.drawString(current->children[index + 1]->name, 16, 48, false);
    if (getValue(current->children[index + 1]) != NULL) {
      screen.drawString(getValue(current->children[index + 1]), VALUE_X, 48, false);
    } else if(current->children[index + 1]->numberOfValues != 0) {
      screen.drawNumber(current->children[index + 1]->indexOfValue, VALUE_X, 48, false);
    }
  }
}

void Menu::drawSelected(int valueIndex) {
  if (current->children[index]->numberOfValues != 0 && current->children[index]->values != NULL) {
    drawSelectedString(valueIndex);
  } else if (current->children[index]->numberOfValues != 0 && current->children[index]->values == NULL) {
    drawSelectedNumeric(valueIndex);
  } else {
    return; // the rest is handled externaly;
  }
}

void Menu::drawSelectedString(int valueIndex) {

  screen.drawString(current->name, 16, 2, false);

  if(valueIndex < 0 || valueIndex >= current->children[index]->numberOfValues) {
    return; // invalid valueIndex
  }

  screen.drawString(current->children[index]->name, 16, 32, false);
  screen.drawString("->", VALUE_X - 16, 32, false);
  screen.drawString(current->children[index]->values[valueIndex], VALUE_X, 32, false);

  if(valueIndex > 0) {
    screen.drawString(current->children[index]->values[valueIndex - 1], VALUE_X, 16, false);
  }
  if(valueIndex + 1 < current->children[index]->numberOfValues) {
    screen.drawString(current->children[index]->values[valueIndex + 1], VALUE_X, 48, false);
  }
}

void Menu::drawSelectedNumeric(int valueIndex) {
  screen.drawString(current->name, 16, 2, false);

  screen.drawString(current->children[index]->name, 16, 32, false);
  screen.drawString("->", VALUE_X - 16, 32, false);
  screen.drawNumber(valueIndex, VALUE_X, 32, false);

  if(valueIndex > 0) {
    screen.drawNumber(valueIndex - 1, VALUE_X, 16, false);
  }
  if(valueIndex + 1 < current->children[index]->numberOfValues) {
    screen.drawNumber(valueIndex + 1, VALUE_X, 48, false);
  }
}

bool Menu::leaveIsSelected() {
  if (leaveIsSelected_intern) {
    return true;
  } else {
    return false;
  }
}