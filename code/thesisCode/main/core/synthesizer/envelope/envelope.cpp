#include "envelope.h"

Envelope::Envelope(Timer &timer_)
    : timer(timer_),
      returnValue(0),
      returnValueAtrelease(0),
      timeAtpress(0),
      lastTimerValue(0),
      lastPressValue(false) {
}

void Envelope::set(uint8_t attack_, uint8_t decay_, uint8_t sustain_, uint8_t release_) {
  this->attack = attack_;
  this->decay = decay_;
  this->sustain = sustain_;
  this->release = release_;
}

void Envelope::get(uint8_t *attack_, uint8_t *decay_, uint8_t *sustain_, uint8_t *release_) {
  *attack_ = this->attack;
  *decay_ = this->decay;
  *sustain_ = this->sustain;
  *release_ = this->release;
}

uint8_t Envelope::apply(bool pressed) {
  uint64_t currentTime = timer.getValue();
  if (lastTimerValue == currentTime) {
    return returnValue;
  } else {
    calculateValue(pressed, currentTime);
    lastPressValue = pressed;
    lastTimerValue = currentTime;
  }
  return returnValue;
}

void Envelope::calculateValue(bool pressed, uint64_t currentTime) {

  // timer.waitForAlarm(1);

  if (pressed) {
    if (!lastPressValue) {
      timeAtpress = currentTime;
    }
    int timeValue = currentTime - timeAtpress;
    if (timeValue < attack) {
      returnValue = (timeValue * 255) / attack;
    } else if (timeValue < attack + decay) {
      int timeSinceEndOfAttack = timeValue - attack;
      int decayAmount0to255 = (timeSinceEndOfAttack * 255) / decay;
      int decayAmountToSustain = (decayAmount0to255 * (255 - sustain)) / 255;
      returnValue = (255 - decayAmountToSustain);
    } else {
      returnValue = (sustain);
    }
  } else if (returnValue != 0) {
    if (lastPressValue) {
      timeAtpress = currentTime;
      returnValueAtrelease = returnValue;
    }
    int timeValue = currentTime - timeAtpress;
    if (timeValue < release) {
      int releaseAmount0to255 = (timeValue * 255) / release;
      int releaseAmountfromSustain = (releaseAmount0to255 * returnValueAtrelease) / 255;
      returnValue = (returnValueAtrelease - releaseAmountfromSustain);
      if (returnValue < 0) {
        returnValue = 0;
      }
    }else {
        returnValue = 0;
      }
  } else {
    returnValue = 0;
  }
}