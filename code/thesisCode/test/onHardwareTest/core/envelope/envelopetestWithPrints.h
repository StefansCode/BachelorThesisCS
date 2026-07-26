#ifndef ENVELOPE_TEST_WITH_PRINTS
#define ENVELOPE_TEST_WITH_PRINTS

#include "adapter/button/button.h"
#include "adapter/util/util.h"

#include "synthesizer/envelope/envelope.h"

#include "adapter/util/util.h"

Timer timer;

Envelope envelope11(timer);
Envelope envelope12(timer);
Envelope envelope13(timer);
Envelope envelope14(timer);

Envelope envelope21(timer);
Envelope envelope22(timer);
Envelope envelope23(timer);
Envelope envelope24(timer);


void runEnvelopeTestWithPrints() {
  envelope11.set(25,25,128,25);
  envelope12.set(255,255,128,255);
  envelope13.set(0,255,128,255);
  envelope14.set(10,0,128,50);

  envelope21.set(25,25,128,25);
  envelope22.set(25,25,0,25);
  envelope23.set(55,55,128,55);
  envelope24.set(55,0,255,255);

  while (1) {
    
    unsigned long t0 = util.micros();
    
    printf(">EnvelopeValue11:%d\r\n", envelope11.apply(buttons.getState(PIN_BTN_11)));
    printf(">EnvelopeValue12:%d\r\n", envelope12.apply(buttons.getState(PIN_BTN_12)));
    printf(">EnvelopeValue13:%d\r\n", envelope13.apply(buttons.getState(PIN_BTN_13)));
    printf(">EnvelopeValue14:%d\r\n", envelope14.apply(buttons.getState(PIN_BTN_14)));
    
    printf(">EnvelopeValue21:%d\r\n", envelope21.apply(buttons.getState(PIN_BTN_21)));
    printf(">EnvelopeValue22:%d\r\n", envelope22.apply(buttons.getState(PIN_BTN_22)));
    printf(">EnvelopeValue23:%d\r\n", envelope23.apply(buttons.getState(PIN_BTN_23)));
    printf(">EnvelopeValue24:%d\r\n", envelope24.apply(buttons.getState(PIN_BTN_24)));
    
    printf("Timervalue:%lld\r\n", timer.getValue());

    
    unsigned long t1 = util.micros();

    int lal11 = envelope11.apply(buttons.getState(PIN_BTN_11));
    int lal12 = envelope12.apply(buttons.getState(PIN_BTN_12));
    int lal13 = envelope13.apply(buttons.getState(PIN_BTN_13));
    int lal14 = envelope14.apply(buttons.getState(PIN_BTN_14));

    int lal21 = envelope21.apply(buttons.getState(PIN_BTN_21));
    int lal22 = envelope22.apply(buttons.getState(PIN_BTN_22));
    int lal23 = envelope23.apply(buttons.getState(PIN_BTN_23));
    int lal24 = envelope24.apply(buttons.getState(PIN_BTN_24));

    unsigned long t2 = util.micros();
    printf("looptime with prints: %ld", t1-t0);
    printf("looptime: %ld\r\n", t2-t1);

    vTaskDelay(100/portTICK_PERIOD_MS);
  }
}

#endif // ENVELOPE_TEST_WITH_PRINTS