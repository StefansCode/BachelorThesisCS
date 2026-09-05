#ifndef SIGNAL_H
#define SIGNAL_H

template <typename T, unsigned int BUFFER_SIZE = 256>
class Signal {
private:
  T buffer[BUFFER_SIZE] = {0};
  unsigned int index = BUFFER_SIZE - 1;

public:
  unsigned int getSize();

  Signal &fromFunction(T (*input)(void *param), void *param);
  Signal &fromValue(T value);

  Signal &applyFunction(T (*func)(T data, void *param), void *param);
  Signal &applyFunction(T (*func)(T data, const void *param), const void *param);     /** @todo will ich das wirklich so machen? */
  Signal &applyFunction(T (*func)(T *data, void *param), void *param);
  Signal &applyFunction(T (*func)(T *data, const void *param), const void *param);

  Signal &add(Signal<T, BUFFER_SIZE> &other);
  Signal &add(T value);

  Signal &multiply(Signal<T, BUFFER_SIZE> &other);
  Signal &multiply(T value);
  Signal &multiply(float value);

  Signal &average(unsigned int numberOfValues);

  Signal &FourierTransform();

  T returnValue();
  T *returnBuffer();
};

template <typename T, unsigned int BUFFER_SIZE>
unsigned int Signal<T, BUFFER_SIZE>::getSize() {
  return BUFFER_SIZE;
}

/**
 * Input
 */
template <typename T, unsigned int BUFFER_SIZE>
Signal<T, BUFFER_SIZE> &Signal<T, BUFFER_SIZE>::fromFunction(T (*input)(void *param), void *param) {
  index = (index + 1) % BUFFER_SIZE;
  buffer[index] = input(param);
  return *this;
}

template <typename T, unsigned int BUFFER_SIZE>
Signal<T, BUFFER_SIZE> &Signal<T, BUFFER_SIZE>::fromValue(T value) {
  index = (index + 1) % BUFFER_SIZE;
  buffer[index] = value;
  return *this;
}

/**
 * General Operations
 */

template <typename T, unsigned int BUFFER_SIZE>
Signal<T, BUFFER_SIZE> &Signal<T, BUFFER_SIZE>::applyFunction(T (*func)(T data, void *param), void *param) {
  buffer[index] = func(buffer[index], param);
  return *this;
}

template <typename T, unsigned int BUFFER_SIZE>
Signal<T, BUFFER_SIZE> &Signal<T, BUFFER_SIZE>::applyFunction(T (*func)(T *data, void *param), void *param) {
  if (index == 0) {
    func(buffer, param);
  }
  return *this;
}

template <typename T, unsigned int BUFFER_SIZE>
Signal<T, BUFFER_SIZE> &Signal<T, BUFFER_SIZE>::applyFunction(T (*func)(T data, const void *param), const void *param) {
  buffer[index] = func(buffer[index], param);
  return *this;
}

template <typename T, unsigned int BUFFER_SIZE>
Signal<T, BUFFER_SIZE> &Signal<T, BUFFER_SIZE>::applyFunction(T (*func)(T *data, const void *param), const void *param) {
  if (index == 0) {
    func(buffer, param);
  }
  return *this;
}

/**
 * Arithmetic Operations
 */

template <typename T, unsigned int BUFFER_SIZE>
Signal<T, BUFFER_SIZE> &Signal<T, BUFFER_SIZE>::add(Signal<T, BUFFER_SIZE> &other) {
  this->buffer[index] += other.buffer[other.index];
  return *this;
}

template <typename T, unsigned int BUFFER_SIZE>
Signal<T, BUFFER_SIZE> &Signal<T, BUFFER_SIZE>::add(T value) {
  this->buffer[index] += value;
  return *this;
}

template <typename T, unsigned int BUFFER_SIZE>
Signal<T, BUFFER_SIZE> &Signal<T, BUFFER_SIZE>::multiply(Signal<T, BUFFER_SIZE> &other) {
  this->buffer[index] *= other.buffer[other.index];
  return *this;
}

template <typename T, unsigned int BUFFER_SIZE>
Signal<T, BUFFER_SIZE> &Signal<T, BUFFER_SIZE>::multiply(T value) {
  this->buffer[index] *= value;
  return *this;
}

template <typename T, unsigned int BUFFER_SIZE>
Signal<T, BUFFER_SIZE> &Signal<T, BUFFER_SIZE>::multiply(float value) {
  this->buffer[index] = T(this->buffer[index] * value);
  return *this;
}

/**
 * Averaging
 */

template <typename T, unsigned int BUFFER_SIZE>
Signal<T, BUFFER_SIZE> &Signal<T, BUFFER_SIZE>::average(unsigned int numberOfValues) {
  T sum = T(0);
  for (unsigned int i = 0; i < numberOfValues; i++) {
    sum += buffer[(index - i + BUFFER_SIZE) % BUFFER_SIZE];
  }
  buffer[index] = sum / T(numberOfValues);
  return *this;
}

/**
 * Output
 */

template <typename T, unsigned int BUFFER_SIZE>
T Signal<T, BUFFER_SIZE>::returnValue() {
  return buffer[index];
}

template <typename T, unsigned int BUFFER_SIZE>
T *Signal<T, BUFFER_SIZE>::returnBuffer() {
  return buffer;
}

#endif // SIGNAL_H