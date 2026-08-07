#include "signal.h"

/**
 * Input
 */

Signal& Signal::fromFunction(sample (*input)(void *param), void *param) {
  buffer[index] = input(param);
  return *this;
}

Signal& Signal::fromValue(sample value) {
  buffer[index] = value;
  return *this;
}

/**
 * General Operations
 */

Signal& Signal::applyFunction(sample (*func)(sample data, void *param), void *param) {
  buffer[index] = func(buffer[index], param);
  return *this;
}

/**
 * Arithmetic Operations
 */

Signal& Signal::add(Signal &other) {
  this->buffer[index] += other.buffer[other.index];
  return *this;
}

Signal& Signal::add(sample value) {
  this->buffer[index] += value;
  return *this;
}

Signal& Signal::multiply(Signal &other) {
  this->buffer[index] *= other.buffer[other.index];
  return *this;
}

Signal& Signal::multiply(sample value) {
  this->buffer[index] *= value;
  return *this;
}

Signal& Signal::multiply(float value) {
  this->buffer[index] = sample(this->buffer[index] * value);
  return *this;
}

/**
 * Output
 */

void Signal::toFunction(void (*output)(sample data, void *param), void *param) {
  output(buffer[index], param);
  index = (index + 1) % BUFFER_SIZE;
}

void Signal::toFunction(void (*output)(sample *data, void *param), void *param) {
  index = (index + 1) % BUFFER_SIZE;
  if(index == 0) {
    output(buffer, param);
  }
}