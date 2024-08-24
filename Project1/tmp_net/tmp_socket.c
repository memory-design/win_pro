#include "tmp_socket.h"

TMP_SOCKET tmp_socket = {0};

/**
 * @brief socket 初始化
 * 
 * @param tmp socket 结构体指针
 * 
 * @return NULL
 */
void tmp_socket_init(TMP_SOCKET *tmp)
{
	PRINTF_FUNC_NAME;

    /* 初始化 Winsock */
    if (WSAStartup(MAKEWORD(2, 2), &(tmp->wsa_data)) != 0)
    {
        printf("初始化 Winsock 失败\n");
        return;
    }
    printf("初始化 Winsock 成功\n");

    if(tmp_config.cfg1.bit.use_dns == 1)
    {
        tmp_dns_init(&(tmp->dns));
        tmp->dns.read(&(tmp->dns));
    }

    /* 创建套接字 */
    tmp->socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (tmp->socket == INVALID_SOCKET)
    {
        printf("创建 Socket 失败\n");
        WSACleanup();
        return;
    }
    printf("创建 Socket 成功\n");
}