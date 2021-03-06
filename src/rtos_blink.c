#include <stdio.h>

#include "pico/stdlib.h"

#include "FreeRTOS.h"
#include "FreeRTOSConfig.h"
#include "task.h"

const uint led_pin = 25;
bool LED_Status = false;

void Blink(void* parameter);

int main() {
    gpio_init(led_pin);
    gpio_set_dir(led_pin, GPIO_OUT);
    stdio_init_all();

    TaskHandle_t TaskHandle = NULL;                          // set task handle
    xTaskCreate(Blink, "Blink", 128, NULL, 1, &TaskHandle);  // creat a task
    vTaskStartScheduler();                                   // start task

    while (true) {
        if (LED_Status)
            printf("LED ON!\n");
        else
            printf("LED OFF!\n");
    }
    return 0;
}

void Blink(void* parameter) {
    while (true) {
        LED_Status = !LED_Status;
        gpio_put(led_pin, LED_Status);
        vTaskDelay(1000);  // this would not block programe
    }
}
