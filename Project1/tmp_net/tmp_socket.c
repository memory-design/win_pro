#include "tmp_socket.h"

TMP_SOCKET tmp_socket = {0};

/**
 * @brief socket ��ʼ��
 * 
 * @param tmp socket �ṹ��ָ��
 * 
 * @return NULL
 */
void tmp_socket_init(TMP_SOCKET *tmp)
{
	PRINTF_FUNC_NAME;

    /* ��ʼ�� Winsock */
    if (WSAStartup(MAKEWORD(2, 2), &(tmp->wsa_data)) != 0)
    {
        printf("��ʼ�� Winsock ʧ��\n");
        return;
    }
    printf("��ʼ�� Winsock �ɹ�\n");

    if(tmp_config.cfg1.bit.use_dns == 1)
    {
        tmp_dns_init(&(tmp->dns));
        tmp->dns.read(&(tmp->dns));
    }

    /* �����׽��� */
    tmp->socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (tmp->socket == INVALID_SOCKET)
    {
        printf("���� Socket ʧ��\n");
        WSACleanup();
        return;
    }
    printf("���� Socket �ɹ�\n");
}