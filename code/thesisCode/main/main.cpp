#include "sdkconfig.h"
#include "adapter/button/button.h"
#include "adapter/dac/i2sDac.h"
#include "adapter/Encoder/Encoder.h"
#include "adapter/rgbLed/rgbLed.h"
#include "adapter/screen/screen.h"

#include "config.h"

#include "core/synthesizer/synthesizer.h"

//#include "../test/onHardwareTest/core/sound/soundInputTest.h"
//#include "../test/onHardwareTest/core/sound/soundOutputTest.h"


extern "C" void app_main(void) {

  buttons.init();
  dac.init(SAMPLE_RATE);
  encoder.init();
  rgbLed.init();
  screen.init();

  //runSoundInputTest_allWaveforms();
  //runSoundInputTest_switchWaveforms();
  //runSoundInputTest_waveformCalulationSpeed();

  //runSoundOutputTest();
  //runSoundOutputTest_unsigned();

  synth.run();

  while(1){
    vTaskDelay(100/portTICK_PERIOD_MS);
  }
}
