idf_component_register(
     SRCS 
          "main.cpp" 

          "debug/taskAnalyser/taskAnalyser.cpp"
                            
          "adapter/dac/i2sDac.cpp"
          "adapter/screen/screen.cpp"
          "adapter/screen/SSD1306/ssd1306.c"
          "adapter/rgbLed/rgbLed.cpp"
          "adapter/Encoder/Encoder.cpp"
          "adapter/button/button.cpp"
          "adapter/threadSaveVariable/threadSaveInt.cpp"
          "adapter/threadSaveVariable/threadSaveBool.cpp"

          "core/config.h"
          "core/signal/signal.cpp"
          "core/sound/sound.cpp"
          "core/synthesizer/synthesizer.cpp"
          "core/synthesizer/notes/notes.cpp"
     
     INCLUDE_DIRS 
          "."
          "./core"
)