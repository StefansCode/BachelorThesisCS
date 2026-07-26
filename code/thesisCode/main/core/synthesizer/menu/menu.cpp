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
  if (current->parent != NULL) {
    current = current->parent;
    index = 0;
    return true;
  } else {
    return false;
  }
}
bool Menu::moveForward() {
  if (current->numberOfChildren != 0) {
    current = current->children[index];
    index = 0;
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

/** @todo maybe move into seperat class/komponent */
#define VALUE_X 80
void Menu::draw() {
  screen.drawString(current->name, 16, 2, false);

  if (index > 0) {
    screen.drawString(current->children[index - 1]->name, 16, 16, false);
    if (current->children[index - 1]->value != NULL) {
      screen.drawString(current->children[index - 1]->value, VALUE_X, 16, false);
    }
  }

  /** @todo maybe 5 tight lines 
   * screen.drawString("LALLOOL", 16, 24, false);
   * */
  
  screen.drawString("->", 0, 32, false);
  screen.drawString(current->children[index]->name, 16, 32, false);
  if (current->children[index]->value == NULL) {
    screen.drawString("->", 112, 32, false);
  } else {
    screen.drawString(current->children[index]->value, VALUE_X, 32, false);
  }

  if (index + 1 < current->numberOfChildren) {
    screen.drawString(current->children[index + 1]->name, 16, 48, false);
    if (current->children[index + 1]->value != NULL) {
      screen.drawString(current->children[index + 1]->value, VALUE_X, 48, false);
    }
  }
}

bool Menu::indexIsOnLeaf() {
  if (current->children[index]->numberOfChildren == 0) {
    return true;
  } else {
    return false;
  }
}