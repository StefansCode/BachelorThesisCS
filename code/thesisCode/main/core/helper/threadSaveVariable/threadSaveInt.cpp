#include "threadSaveInt.h"

ThreadSaveInt::ThreadSaveInt(int initialValue) : variable(initialValue) {
}

void ThreadSaveInt::set(int value) {
  variable.store(value);
}

int ThreadSaveInt::get() {
  return variable.load();
}