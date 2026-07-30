#ifndef MENU_H
#define MENU_H
#include "adapter/screen/screen.h"
#include "stdint.h"
#include "stdlib.h"

typedef struct entry {
  entry *parent;
  entry *children[8]; /** @todo maybe not allocate space for 8, but use pointer like string. */
  unsigned int numberOfChildren;
  const char *name;
  const char *value;
} entry_t;

class Menu {
private:
  entry_t root = {NULL, {NULL}, 0, "MAIN", NULL};

  /* root -> */
  // entry_t drums = {&root, {NULL}, 0x0001, "DRUMS", NULL};
  entry_t bass = {&root, {NULL}, 0x0002, "BASS", NULL};
  entry_t lead = {&root, {NULL}, 0x0003, "LEAD", NULL};
  entry_t settings = {&root, {NULL}, 0x0004, "SETTINGS", NULL};

  /** drums -> */
  // TODO

  /** bass -> */
  entry_t bass_onOff = {&root, {NULL}, 0x0012, "SWITCH", "OFF"};
  entry_t bass_note = {&root, {NULL}, 0x0022, "NOTE", "A"};
  entry_t bass_waveform = {&root, {NULL}, 0x0032, "WAVE", "SAW"};
  entry_t bass_LFO = {&root, {NULL}, 0x0042, "LFO", "TODO"};

  /** lead -> */
  entry_t lead_scale = {&root, {NULL}, 0x0013, "SCALE", "IONIAN"};
  entry_t lead_waveform = {&root, {NULL}, 0x0023, "WAVE", "SAW"};
  entry_t lead_envelope = {&root, {NULL}, 0x0033, "ENV", NULL};
  entry_t lead_LFO = {&root, {NULL}, 0x0043, "LFO", "TODO->"};
  entry_t lead_filter = {&root, {NULL}, 0x0053, "FILTER", "TODO->"};
  entry_t lead_fx = {&root, {NULL}, 0x0063, "FX", "TODO->"};

  /* settings -> */
  entry_t settings_sampleRate = {NULL, {NULL}, 0x0014, "SMP_HZ", "44100"};

  void addChild(entry_t *target, entry_t *child);

  unsigned int index = 0;
  entry_t *current = &root;

  bool leaveIsSelected_intern = false;

public:
  Menu();
  bool moveBack();
  bool moveForward();
  bool moveUp();
  bool moveDown();
  unsigned int getID();
  const char *getName();
  void setValue(const char *newValue);
  bool leaveIsSelected();
  void drawUnselected();
  void drawSelected(const char *lastValue, const char *currentValue, const char *nextValue);
};

#endif // MENU_H