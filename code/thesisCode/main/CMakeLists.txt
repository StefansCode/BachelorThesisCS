idf_component_register(
     SRCS 
          "main.cpp" 

          "debug/taskAnalyser/taskAnalyser.cpp"
                            
          "adapter/button/button.cpp"
          "adapter/dac/i2sDac.cpp"
          "adapter/Encoder/Encoder.cpp"
          "adapter/rgbLed/rgbLed.cpp"
          "adapter/screen/screen.cpp"
          "adapter/screen/SSD1306/ssd1306.c"
          "adapter/threadSaveVariable/threadSaveInt.cpp"
          "adapter/threadSaveVariable/threadSaveBool.cpp"
          "adapter/timer/timer.cpp"
          "adapter/util/util.cpp"

          
          "core/signal/signal.cpp"
          "core/sound/sound.cpp"
          "core/synthesizer/synthesizer_main.cpp"
          "core/synthesizer/synthesizer_synth.cpp"
          "core/synthesizer/synthesizer_IO.cpp"
          "core/synthesizer/synthesizer_screen.cpp"
          "core/synthesizer/notes/notes.cpp"
          "core/synthesizer/envelope/envelope.cpp"
          "core/synthesizer/menu/menu.cpp"
     
     INCLUDE_DIRS 
          "."
          "./core"
)