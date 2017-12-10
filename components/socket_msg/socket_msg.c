#include<stdio.h>
#include<string.h>
#include "esp_log.h"

#include "lwip/sockets.h"
#include "lwip/dns.h"
#include "lwip/netdb.h"
#include "lwip/igmp.h"
#include "lwip/err.h"
#include "lwip/sys.h"

#if CONFIG_SOCKET_MSG
static const char *TAG = "SOCKET_MSG";

int sock;
struct sockaddr_in server_address;

int init_socket()
{
    int count = 5;
    while(count) {
        server_address.sin_family = AF_INET;
        sock = socket(PF_INET, SOCK_STREAM, 0);

        inet_pton(AF_INET, CONFIG_SOCKET_IP, &server_address.sin_addr.s_addr);
        server_address.sin_port = htons(CONFIG_SOCKET_PORT);
        ESP_LOGI(TAG, "Connect socket %s:%d",CONFIG_SOCKET_IP,CONFIG_SOCKET_PORT);

        struct timeval tv_out;
        tv_out.tv_sec = 3; //Wait 10 seconds.
        tv_out.tv_usec = 0;
        setsockopt(sock,SOL_SOCKET,SO_RCVTIMEO,&tv_out, sizeof(tv_out));

        int rs = connect(sock, (struct sockaddr *)&server_address, sizeof(struct sockaddr_in));
        if(rs < 0) {
            ESP_LOGI(TAG, "%s:%d: Error connect socket failed,ErrNo:%d", __func__, __LINE__, errno);
            close(sock);
            goto reconnect;
        }
        return 0;
reconnect:
        count--;
        vTaskDelay(5000 / portTICK_RATE_MS);
    }
    return -1;
}
void send_socket_msg(char *msg)
{
    ESP_LOGI(TAG, "Send msg:%s , len: %d", msg, strlen(msg));
    int rs = write(sock, msg, strlen(msg));
    if(rs < 0) {
        ESP_LOGI(TAG, "%s:%d:Error write socket failed,ErrNo:%d", __func__, __LINE__, errno);
    }

}

void release_socket()
{
    close(sock);
}

#else
void init_socket(){}
void send_msg(char *msg){}
#endif
