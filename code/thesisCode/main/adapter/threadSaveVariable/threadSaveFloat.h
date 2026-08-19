#ifndef THREAD_SAVE_FLOAT_H
#define THREAD_SAVE_FLOAT_H
#include <atomic>

class ThreadSaveFloat {
public:
  ThreadSaveFloat(float initialValue);
  void set(float value);
  float get();

private:
  std::atomic<float> variable;
};

#endif // THREAD_SAVE_FLOAT_H