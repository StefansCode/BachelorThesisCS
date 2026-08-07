#ifndef MENU_H
#define MENU_H
#include "adapter/screen/screen.h"
#include "synthesizer/notes/notes.h"
#include "stdint.h"
#include "stdlib.h"

typedef struct entry {
  entry *parent;
  entry *children[8]; /** @todo maybe not allocate space for 8, but use pointer like string. */
  unsigned int numberOfChildren;
  const char *name;
  const char **values;
  int numberOfValues;
  int indexOfValue;
} entry_t;

class Menu {
private:
  entry_t root = {NULL, {NULL}, 0, "MAIN", NULL, 0, 0};

  /* root -> */
  // entry_t drums = {&root, {NULL}, 0x001, "DRUMS", NULL};
  entry_t bass = {&root, {NULL}, 0, "BASS", NULL, 0, 0};
  entry_t lead = {&root, {NULL}, 0, "LEAD", NULL, 0, 0};
  entry_t settings = {&root, {NULL}, 0, "SETTINGS", NULL, 0, 0};

  /** drums -> */
  // TODO

  /** bass -> */
  const char *bass_onOff_values[2] = {"OFF", "ON"};
  entry_t bass_onOff = {&root, {NULL}, 0, "SWITCH", bass_onOff_values, 2, 0};
  entry_t bass_note = {&root, {NULL}, 0, "NOTE", noteNames, 12, 0};
  entry_t bass_waveform = {&root, {NULL}, 0, "WAVE", waveformNames, 4, 0};
  entry_t bass_LFO = {&root, {NULL}, 0, "LFO", NULL, 0, 0};

  /** lead -> */
  entry_t lead_scale = {&root, {NULL}, 0, "SCALE", scaleNames, 8, 1};
  entry_t lead_waveform = {&root, {NULL}, 0, "WAVE", waveformNames, 4, 0};
  entry_t lead_envelope = {&root, {NULL}, 0, "ENV", NULL, 0, 0};
  entry_t lead_LFO = {&root, {NULL}, 0, "LFO", NULL, 0, 0};
  entry_t lead_filter = {&root, {NULL}, 0, "FILTER", NULL, 0, 0};
  entry_t lead_fx = {&root, {NULL}, 0, "FX", NULL, 0, 0};

  entry_t bass_envelope_attack = {&lead_envelope, {NULL}, 0, "ATK", NULL, 256, 0};
  entry_t bass_envelope_decay = {&lead_envelope, {NULL}, 0, "DCY", NULL, 256, 32};
  entry_t bass_envelope_sustain = {&lead_envelope, {NULL}, 0, "SUS", NULL, 256, 64};
  entry_t bass_envelope_release = {&lead_envelope, {NULL}, 0, "REL", NULL, 256, 8};

  /* settings -> */
  entry_t settings_sampleRate = {&root, {NULL}, 0, "SMP_HZ", sampleRateNames, 3, 2};

  void addChild(entry_t *target, entry_t *child);
  const char * getValue(entry_t *entry);
  void setValueIndex(entry_t *entry, int index);

  unsigned int index = 0;
  entry_t *current = &root;

  bool leaveIsSelected_intern = false;

  void drawSelectedString(int valueIndex);
  void drawSelectedNumeric(int valueIndex);
  
public:
  Menu();
  bool moveBack();
  bool moveForward();
  bool moveUp();
  bool moveDown();
  const char *getName();
  const char *getSelectedName();
  int getValuesLength();
  int getSelectedValueIndex();
  void setSelectedValueIndex(int index);
  bool leaveIsSelected();
  void drawUnselected();
  void drawSelected(int valueIndex);
};

#endif // MENU_H