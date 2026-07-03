#include "ringBuffer.h"

bool RingBuffer::write(sample data) {
    if(isFullFlag) {
        return false;
    }
    noNewElementFlag = false;
    buffer[writeIndex] = data;
    writeIndex = (writeIndex + 1) % BUFFER_SIZE;
    return true;
}

bool RingBuffer::read(sample &data) {
    if(noNewElementFlag) {
        return false;
    }
    isFullFlag = false;
    data = buffer[(readIndex + 1) % BUFFER_SIZE];
    readIndex = (readIndex + 1) % BUFFER_SIZE;    
    return true;
}

sample RingBuffer::getNthLastElement(int n) {
    return buffer[writeIndex - n];
}