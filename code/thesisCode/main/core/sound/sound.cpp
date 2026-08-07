#include "sound.h"
#if SAMPLE_RATE == 44100
  #include "sineTable44100.h"
#elif SAMPLE_RATE == 22050
  #include "sineTable22050.h"
#elif SAMPLE_RATE == 11025
  #include "sineTable11025.h"
#else
  #error "Unsupported SAMPLE_RATE. Please use 44100, 22050, or 11025."
#endif

int Sound::calculateSaw(unsigned int frequency) {
  return (SAMPLE_MIN + (((time * frequency * SAMPLE_RANGE)/SAMPLE_RATE) % (SAMPLE_RANGE)));
}

Sound& Sound::fromSilence() {
  time = (time + 1) % SAMPLE_RATE;
  signal.fromValue(0);
  return *this;
}

Sound& Sound::fromSaw(unsigned int frequency) {
  time = (time + 1) % SAMPLE_RATE;
  sample value = (sample)(calculateSaw(frequency));
  signal.fromValue(value);
  return *this;
}

Sound& Sound::fromSine(unsigned int frequency) {
  time = (time + 1) % SAMPLE_RATE;
  // sample value = (sample)((sin(M_TWOPI * (double(time * frequency) / SAMPLE_RATE))) * SAMPLE_MAX);
  sample value = sineLookupTable[(time * frequency) % SAMPLE_RATE];
  signal.fromValue(value);
  return *this;
}

Sound& Sound::fromSquare(unsigned int frequency) {
  time = (time + 1) % SAMPLE_RATE;
  sample value = (calculateSaw(frequency) < 0) ? SAMPLE_MIN: SAMPLE_MAX;
  signal.fromValue(value);
  return *this;
}

Sound& Sound::fromTriangle(unsigned int frequency) {
  time = (time + 1) % SAMPLE_RATE;
  int currentSaw = calculateSaw(frequency);
  sample value = (currentSaw < 0) ? ((currentSaw+SAMPLE_MAX)+currentSaw) : (SAMPLE_MAX - (currentSaw * 2));
  signal.fromValue(value);
  return *this;
}

Sound& Sound::amplify(float value) {
  signal.multiply(value);
  return *this;
}

Sound& Sound::add(Sound &other) {
  signal.add(other.signal);
  return *this;
}

Sound& Sound::add(sample value) {
  signal.add(value);
  return *this;
}

void Sound::toFunction(void (*output)(sample data, void *param), void *param) {
  signal.toFunction(output, param);
}

void Sound::toFunction(void (*output)(sample *data, void *param), void *param) {
  signal.toFunction(output, param);
}