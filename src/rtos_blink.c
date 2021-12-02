#include <stdio.h>

#include "hardware/gpio.h"
#include "pico/stdlib.h"

#include "FreeRTOS.h"
#include "FreeRTOSConfig.h"
#include "task.h"

const uint led_pin = 25;

bool LED_Status = false;

void Blink(void* parameter) {
    while (true) {
        LED_Status = !LED_Status;
        if (LED_Status)
            printf("LED ON!\n");
        else
            printf("LED OFF!\n");
        gpio_put(led_pin, LED_Status);
        vTaskDelay(1000);
    }
}

int main() {
    gpio_init(led_pin);
    gpio_set_dir(led_pin, GPIO_OUT);
    stdio_init_all();

    TaskHandle_t TaskHandle = NULL;
    xTaskCreate(Blink, "Blink", 128, NULL, 1, &TaskHandle);
    vTaskStartScheduler();

    while (true) {
    }
}