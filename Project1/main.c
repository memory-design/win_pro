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

    /* mqtt ���� */
    mqtt_task();

    return 0;
}
