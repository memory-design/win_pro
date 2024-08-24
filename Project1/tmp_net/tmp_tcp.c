#define _CRT_SECURE_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include "tmp_tcp.h"
#include "tmp_lib.h"

TMP_TCP_CLIENT tmp_tcp_client = {0x00};
#define MAX_SEND_BUF_SIZE (1024)
#define MAX_RECV_BUF_SIZE (1024)
u8 tcp_send_buf[MAX_SEND_BUF_SIZE] = {0x00};
u8 tcp_recv_buf[MAX_RECV_BUF_SIZE] = {0x00};

void tmp_tcp_client_open(TMP_TCP_CLIENT *tmp);
void tmp_tcp_client_close(TMP_TCP_CLIENT *tmp);
void tmp_tcp_client_write(TMP_TCP_CLIENT *tmp);
void tmp_tcp_client_read(TMP_TCP_CLIENT *tmp);

/**
 * @brief tcp client 参数初始化
 *
 * @param tmp tcp client 结构体指针
 *
 * @return NULL
 */
void tmp_tcp_init(TMP_TCP_CLIENT *tmp)
{
    /* 设置服务器ip */
    tmp->ser_ip[0] = 192;
    tmp->ser_ip[1] = 168;
    tmp->ser_ip[2] = 31;
    tmp->ser_ip[3] = 39;
    sprintf(tmp->str_ser_ip, "%u.%u.%u.%u", tmp->ser_ip[0], tmp->ser_ip[1], tmp->ser_ip[2], tmp->ser_ip[3]);

    /* 设置服务器端口 */
    tmp->ser_port = 8080;

    /* 设置发送接收缓存区指针 */
    tmp->send_buf = tcp_send_buf;
    tmp->recv_buf = tcp_recv_buf;
    tmp->recv_len = MAX_RECV_BUF_SIZE;

    /* 注册函数指针 */
    tmp->open = tmp_tcp_client_open;
    tmp->close = tmp_tcp_client_close;
    tmp->write = tmp_tcp_client_write;
    tmp->read = tmp_tcp_client_read;
}

/**
 * @brief tcp client 打开socket 连接服务器
 *
 * @param tmp tcp client 结构体指针
 *
 * @return NULL
 */
void tmp_tcp_client_open(TMP_TCP_CLIENT *tmp)
{
    /* 初始化 Winsock */
    if (WSAStartup(MAKEWORD(2, 2), &(tmp->wsa_data)) != 0)
    {
        printf("初始化 Winsock 失败\n");
        return;
    }
    printf("初始化 Winsock 成功\n");

    /* 创建套接字 */
    tmp->tmp_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (tmp->tmp_socket == INVALID_SOCKET)
    {
        printf("创建 Socket 失败\n");
        WSACleanup();
        return;
    }
    printf("创建 Socket 成功\n");

    /* 设置服务器地址结构 */
    tmp->ser_addr.sin_family = AF_INET;
    tmp->ser_addr.sin_addr.s_addr = inet_addr(tmp->str_ser_ip);
    tmp->ser_addr.sin_port = htons(tmp->ser_port);

    /* 连接到服务器 */
    if (connect(tmp->tmp_socket, (struct sockaddr *)&tmp->ser_addr, sizeof(tmp->ser_addr)) == SOCKET_ERROR)
    {
        printf("连接服务器失败\n");
        closesocket(tmp->tmp_socket);
        WSACleanup();
        return;
    }
    printf("连接服务器成功\n\n");
}

/**
 * @brief tcp client 关闭socket 连接
 *
 * @param tmp tcp client 结构体指针
 *
 * @return NULL
 */
void tmp_tcp_client_close(TMP_TCP_CLIENT *tmp)
{
    /* 关闭套接字和清理 Winsock */
    PRINTF_FUNC_NAME
    closesocket(tmp->tmp_socket);
    WSACleanup();
}

/**
 * @brief tcp client 向服务器发送数据
 *
 * @param tmp tcp client 结构体指针
 *
 * @return NULL
 */
void tmp_tcp_client_write(TMP_TCP_CLIENT *tmp)
{
    int result;
    /* 发送数据 */
    result = send(tmp->tmp_socket, tmp->send_buf, tmp->send_len, 0);
    if (result == SOCKET_ERROR)
    {
        printf("发送失败\n");
    }
    else
    {
        printf("发送成功\n");
        printf_array(tmp->send_buf, tmp->send_len, "send_buf");
    }
}

/**
 * @brief tcp client 接收服务器数据
 *
 * @param tmp tcp client 结构体指针
 *
 * @return NULL
 */
void tmp_tcp_client_read(TMP_TCP_CLIENT *tmp)
{
    int result;
    /* 接收数据 */
    result = recv(tmp->tmp_socket, tmp->recv_buf, tmp->recv_len, 0);
    if (result > 0)
    {
        printf("接收成功\n");
        printf_array(tmp->recv_buf, result, "recv_buf");
    }
    else if (result == 0)
    {
        printf("连接关闭或连接超时\n");
    }
    else
    {
        printf("接收失败\n");
    }
}