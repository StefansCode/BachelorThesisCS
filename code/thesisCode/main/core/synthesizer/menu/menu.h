#ifndef MENU_H
#define MENU_H
#include "stdlib.h"
#include "stdint.h"
#include "adapter/screen/screen.h"

typedef struct entry {
  entry *parent;
  entry *children[8];             /** @todo maybe not allocate space for 8, but use pointer like string. */
  unsigned int numberOfChildren;
  uint32_t id;
  const char *name;
} entry_t;

class Menu {
private:
  entry_t root = {NULL, {NULL}, 0, 0, "ROOT"};

  /* root -> */
  //entry_t drums = {&root, {NULL}, 0, 0x0001, "DRUMS"};
  entry_t bass = {&root, {NULL}, 0, 0x0002, "BASS"};
  entry_t lead = {&root, {NULL}, 0, 0x0003, "LEAD"};
  entry_t settings = {&root, {NULL}, 0, 0x0004, "SETTINGS"};

  /** drums -> */
  // TODO

  /** bass -> */
  entry_t bass_note = {&root, {NULL}, 0, 0x0012, "NOTE"};
  entry_t bass_waveform = {&root, {NULL}, 0, 0x0022, "WAVEFORM"};
  entry_t bass_LFO = {&root, {NULL}, 0, 0x0032, "LFO"};

  /** lead -> */
  entry_t lead_scale = {&root, {NULL}, 0, 0x0013, "SCALE"};
  entry_t lead_waveform = {&root, {NULL}, 0, 0x0023, "WAVEFORM"};
  entry_t lead_envelope = {&root, {NULL}, 0, 0x0033, "ENVELOPE"};
  entry_t lead_LFO = {&root, {NULL}, 0, 0x0043, "LFO"};
  entry_t lead_filter = {&root, {NULL}, 0, 0x0053, "FILTER"};
  entry_t lead_fx = {&root, {NULL}, 0, 0x0063, "FX"};

  /* settings -> */
  entry_t settings_sampleRate = {NULL, {NULL}, 0, 0x0014, "SAMPLERATE"};



  void addChild(entry_t *target, entry_t *child);


  unsigned int index = 0;
  entry_t *current = &root;

public:
  Menu();
  bool moveBack();
  bool moveForward();
  bool moveUp();
  bool moveDown();
  unsigned int getID();
  const char *getName();
  bool indexIsOnLeaf();
  void draw();
};

#endif // MENU_H