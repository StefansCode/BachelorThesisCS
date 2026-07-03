#ifndef RING_BUFFER_H
#define RING_BUFFER_H

#include "../core/config.h"

class RingBuffer {
public:
  bool write(sample data);
  bool read(sample &data);
  sample getNthLastElement(int n);

private:
  sample buffer[BUFFER_SIZE];

  unsigned int writeIndex = 0;
  unsigned int readIndex = 0;
  bool isFullFlag = false;
  bool noNewElementFlag = true;
};

#endif // RING_BUFFER_H