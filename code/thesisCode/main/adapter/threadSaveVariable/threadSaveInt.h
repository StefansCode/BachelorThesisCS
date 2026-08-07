#ifndef THREAD_SAVE_INT_H
#define THREAD_SAVE_INT_H
#include <atomic>

class ThreadSaveInt {
public:
  ThreadSaveInt(int initialValue);
  void set(int value);
  int get();

private:
  std::atomic<int> variable;
};

#endif // THREAD_SAVE_INT_H