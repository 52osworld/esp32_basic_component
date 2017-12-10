# Config
Please config the socket IP/PORT in menuconfig

# Example
```
void task()
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
```
# Test Tools
In Linux server you can use the tools netcat/nc

> nc -l port
