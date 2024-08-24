#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include "tmp_def.h"
#include "tmp_socket.h"

#pragma comment(lib, "ws2_32.lib")

TMP_SOCKET *socket_p = NULL;
TMP_TCP_CLIENT *tcp_client_p = NULL;
TMP_CONFIG *config_p = NULL;
int main(void)
{
    /* �ṹ��ָ�븳ֵ */
    socket_p = &tmp_socket;
    tcp_client_p = &tmp_socket.tcp_client;
    config_p = &tmp_config;

    /* ���ó�ʼ�� */
    tmp_config_init(config_p);

    /* socket ��ʼ�� */
    tmp_socket_init(socket_p);

    /* tcp ��ʼ�� */
    tmp_tcp_init(tcp_client_p);

    /* ��tcp���ӷ����� */
    tcp_client_p->open(socket_p);

    while (1)
    {
        /* ��tcp��������ȡ���� */
        tcp_client_p->read(socket_p);

        /* ��tcp�������������� */
        memcpy(tcp_client_p->send_buf, "1234567890", strlen("1234567890"));
        tcp_client_p->send_len = strlen("1234567890");
        tcp_client_p->write(socket_p);

        /* �ӳ� */
        Sleep(10);
    }
    
    return 0;
}
