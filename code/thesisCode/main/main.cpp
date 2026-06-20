#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "adapter/rgbLed/rgbLed.h"

RgbLed rgbLed;

extern "C" void app_main(void)
{
    printf("Hello world!\n");
    rgbLed.init();
    rgbLed.set(0, 0, 50);
    rgbLed.on();
    while(true) {

        printf("ESP is running...\n");
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}
