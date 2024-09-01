#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include "tmp_def.h"
#include "tmp_socket.h"

#pragma comment(lib, "ws2_32.lib")

TMP_SOCKET *socket_p = NULL;
TMP_TCP_CLIENT *tcp_client_p = NULL;
TMP_CONFIG *config_p = NULL;

int main(void)
{
    /* 结构体指针赋值 */
    socket_p = &tmp_socket;
    tcp_client_p = &tmp_socket.tcp_client;
    config_p = &tmp_config;

    /* 配置初始化 */
    tmp_config_init(config_p);

    /* socket 初始化 */
    tmp_socket_init(socket_p);

    /* tcp 初始化 */
    tmp_tcp_init(tcp_client_p);

    /* 打开tcp连接服务器 */
    tcp_client_p->open(socket_p);

    /* mqtt 任务 */
    mqtt_task();

    return 0;
}
