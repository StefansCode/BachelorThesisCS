#ifndef GENERATOR_H
#define GENERATOR_H

#include "config.h"

class Generator {
    uint32_t time = 0;
public:
    sample saw(void *param);
    sample sine(void *param);
    sample square(void *param);
    sample triangle(void *param);
};

#endif // GENERATOR_H