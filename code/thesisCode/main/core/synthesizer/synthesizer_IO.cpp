#include "synthesizer.h"

void Synthesizer::IOTask(void *param) {

  // int lightLvl = 1;

  while (1) {
    // uint8_t queue = buttons.readQueue();
    // uint32_t allButton = buttons.getStateAll();

    // if (queue == PIN_BTN_A) {
    //   leadScale.set((leadScale.get() + 1) % 3);
    // }
    // if (queue == PIN_BTN_B) {
    //   bassPlay.set(!bassPlay.get());
    // }

    // encoder.changeExternalValue(lightLvl, 0, 15, 1);

    envelope1.set(envelopeAttack.get(), envelopeDecay.get(), envelopeSustain.get(), envelopeRelease.get());
    envelope2.set(envelopeAttack.get(), envelopeDecay.get(), envelopeSustain.get(), envelopeRelease.get());
    envelope3.set(envelopeAttack.get(), envelopeDecay.get(), envelopeSustain.get(), envelopeRelease.get());
    envelope4.set(envelopeAttack.get(), envelopeDecay.get(), envelopeSustain.get(), envelopeRelease.get());
    envelope5.set(envelopeAttack.get(), envelopeDecay.get(), envelopeSustain.get(), envelopeRelease.get());
    envelope6.set(envelopeAttack.get(), envelopeDecay.get(), envelopeSustain.get(), envelopeRelease.get());
    envelope7.set(envelopeAttack.get(), envelopeDecay.get(), envelopeSustain.get(), envelopeRelease.get());
    envelope8.set(envelopeAttack.get(), envelopeDecay.get(), envelopeSustain.get(), envelopeRelease.get());

    envelope1.apply(buttons.getState(PIN_BTN_11));
    envelope2.apply(buttons.getState(PIN_BTN_12));
    envelope3.apply(buttons.getState(PIN_BTN_13));
    envelope4.apply(buttons.getState(PIN_BTN_14));

    envelope5.apply(buttons.getState(PIN_BTN_21));
    envelope6.apply(buttons.getState(PIN_BTN_22));
    envelope7.apply(buttons.getState(PIN_BTN_23));
    envelope8.apply(buttons.getState(PIN_BTN_24));

    // printf("Encoder value: %d  lightLvl: %d  buttonState: ", encoder.getvalue(), lightLvl);
    // for (int i = 0; i < 32; i++) {
    //   printf("%d", int((allButton >> i) & (1U)));
    // }
    // printf("\r\n");

    // if (leadScale.get() == 0) {
    //   rgbLed.set(0, lightLvl * 16, 0);
    // } else if (leadScale.get() == 1) {
    //   rgbLed.set(lightLvl * 16, 0, 0);
    // } else {
    //   rgbLed.set(0, 0, lightLvl * 16);
    // }
    // rgbLed.on();

    util.delay(100);
  }
}
