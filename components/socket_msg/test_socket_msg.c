#include<stdio.h>
#include<string.h>
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "socket_msg.h"

static const char *TAG = "TEST_SOCKET_MSG";

void test_socket()
{
    init_socket();
    int count = 20;
    while (count) {
        count--;
        vTaskDelay(3000 / portTICK_RATE_MS);
        send_socket_msg("Send from ESP32\n");
    }
    release_socket();
}
