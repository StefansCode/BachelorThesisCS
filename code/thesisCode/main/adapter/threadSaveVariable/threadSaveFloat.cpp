#include "threadSaveFloat.h"

ThreadSaveFloat::ThreadSaveFloat(float initialValue) : variable(initialValue) {
}

void ThreadSaveFloat::set(float value) {
  variable.store(value);
}

float ThreadSaveFloat::get() {
  return variable.load();
}