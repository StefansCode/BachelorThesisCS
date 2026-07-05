idf_component_register(
     SRCS 
          "main.cpp" 
                            
          "adapter/dac/i2sDac.cpp"
          "adapter/screen/screen.cpp"
          "adapter/screen/SSD1306/ssd1306.c"
          "adapter/rgbLed/rgbLed.cpp"
          "adapter/rotaryEncoder/rotaryEncoder.cpp"
          "adapter/button/button.cpp"

          "core/config.h"
          "core/signal/signal.cpp"
          "core/sound/sound.cpp"
     
     INCLUDE_DIRS 
          "."
          "./core"
)