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

    while (1)
    {
        /* 从tcp服务器读取数据 */
        tcp_client_p->read(socket_p);

        /* 向tcp服务器发送数据 */
        memcpy(tcp_client_p->send_buf, "1234567890", strlen("1234567890"));
        tcp_client_p->send_len = strlen("1234567890");
        tcp_client_p->write(socket_p);

        /* 延迟 */
        Sleep(10);
    }
    
    return 0;
}
