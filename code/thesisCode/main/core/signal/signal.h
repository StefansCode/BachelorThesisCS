#ifndef SIGNAL_H
#define SIGNAL_H
#include "config.h"

template <typename T>
class Signal {
private:
  T buffer[BUFFER_SIZE] = {0};
  unsigned int index = 0;
  unsigned int size = BUFFER_SIZE;

public:

  Signal& fromFunction(T (*input)(void *param), void *param);
  Signal& fromValue(T value);

  Signal& applyFunction(T (*func)(T data, void *param), void *param);

  Signal& add(Signal<T> &other);
  Signal& add(T value);

  Signal& multiply(Signal<T> &other);
  Signal& multiply(T value);
  Signal& multiply(float value);

  Signal& FourierTransform();

  void toFunction(void (*output)(T data, void *param), void *param);
  void toFunction(void (*output)(T *data, void *param), void *param);
};


/**
 * Input
 */
template <typename T>
Signal<T>& Signal<T>::fromFunction(T (*input)(void *param), void *param) {
  buffer[index] = input(param);
  return *this;
}

template <typename T>
Signal<T>& Signal<T>::fromValue(T value) {
  buffer[index] = value;
  return *this;
}

/**
 * General Operations
 */

template <typename T>
Signal<T>& Signal<T>::applyFunction(T (*func)(T data, void *param), void *param) {
  buffer[index] = func(buffer[index], param);
  return *this;
}

/**
 * Arithmetic Operations
 */

template <typename T>
Signal<T>& Signal<T>::add(Signal<T> &other) {
  this->buffer[index] += other.buffer[other.index];
  return *this;
}

template <typename T>
Signal<T>& Signal<T>::add(T value) {
  this->buffer[index] += value;
  return *this;
}

template <typename T>
Signal<T>& Signal<T>::multiply(Signal<T> &other) {
  this->buffer[index] *= other.buffer[other.index];
  return *this;
}

template <typename T>
Signal<T>& Signal<T>::multiply(T value) {
  this->buffer[index] *= value;
  return *this;
}

template <typename T>
Signal<T>& Signal<T>::multiply(float value) {
  this->buffer[index] = T(this->buffer[index] * value);
  return *this;
}

/**
 * Output
 */

template <typename T>
void Signal<T>::toFunction(void (*output)(T data, void *param), void *param) {
  output(buffer[index], param);
  index = (index + 1) % BUFFER_SIZE;
}

template <typename T>
void Signal<T>::toFunction(void (*output)(T *data, void *param), void *param) {
  index = (index + 1) % BUFFER_SIZE;
  if(index == 0) {
    output(buffer, param);
  }
}

#endif // SIGNAL_H