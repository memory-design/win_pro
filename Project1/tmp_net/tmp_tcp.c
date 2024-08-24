#define _CRT_SECURE_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include "tmp_tcp.h"
#include "tmp_socket.h"

#define MAX_SEND_BUF_SIZE (1024)
#define MAX_RECV_BUF_SIZE (1024)
u8 tcp_send_buf[MAX_SEND_BUF_SIZE] = {0x00};
u8 tcp_recv_buf[MAX_RECV_BUF_SIZE] = {0x00};

void tmp_tcp_client_open(TMP_TCP_CLIENT *tmp);
void tmp_tcp_client_close(TMP_TCP_CLIENT *tmp);
void tmp_tcp_client_write(TMP_TCP_CLIENT *tmp);
void tmp_tcp_client_read(TMP_TCP_CLIENT *tmp);

/**
 * @brief tcp client ������ʼ��
 *
 * @param tmp tcp client �ṹ��ָ��
 *
 * @return NULL
 */
void tmp_tcp_init(TMP_TCP_CLIENT *tmp)
{
    /* ���÷�����ip */
    tmp->ser_ip[0] = 192;
    tmp->ser_ip[1] = 168;
    tmp->ser_ip[2] = 31;
    tmp->ser_ip[3] = 39;
    sprintf(tmp->str_ser_ip, "%u.%u.%u.%u", tmp->ser_ip[0], tmp->ser_ip[1], tmp->ser_ip[2], tmp->ser_ip[3]);

    /* ���÷������˿� */
    tmp->ser_port = 8080;

    /* ���÷��ͽ��ջ�����ָ�� */
    tmp->send_buf = tcp_send_buf;
    tmp->recv_buf = tcp_recv_buf;
    tmp->recv_len = MAX_RECV_BUF_SIZE;

    /* ע�ắ��ָ�� */
    tmp->open = tmp_tcp_client_open;
    tmp->close = tmp_tcp_client_close;
    tmp->write = tmp_tcp_client_write;
    tmp->read = tmp_tcp_client_read;
}

/**
 * @brief tcp client ��socket ���ӷ�����
 *
 * @param tmp tcp client �ṹ��ָ��
 *
 * @return NULL
 */
void tmp_tcp_client_open(TMP_SOCKET *tmp)
{
    /* ���÷�������ַ�ṹ */
    tmp->tcp_client.ser_addr.sin_family = AF_INET;
    tmp->tcp_client.ser_addr.sin_addr.s_addr = inet_addr(tmp->tcp_client.str_ser_ip);
    tmp->tcp_client.ser_addr.sin_port = htons(tmp->tcp_client.ser_port);

    /* ���ӵ������� */
    if (connect(tmp->socket, (struct sockaddr *)&tmp->tcp_client.ser_addr, sizeof(tmp->tcp_client.ser_addr)) == SOCKET_ERROR)
    {
        printf("���ӷ�����ʧ��\n");
        closesocket(tmp->socket);
        WSACleanup();
        return;
    }
    printf("���ӷ������ɹ�\n\n");
}

/**
 * @brief tcp client �ر�socket ����
 *
 * @param tmp tcp client �ṹ��ָ��
 *
 * @return NULL
 */
void tmp_tcp_client_close(TMP_SOCKET *tmp)
{
    /* �ر��׽��ֺ����� Winsock */
    PRINTF_FUNC_NAME
    closesocket(tmp->socket);
    WSACleanup();
}

/**
 * @brief tcp client ���������������
 *
 * @param tmp tcp client �ṹ��ָ��
 *
 * @return NULL
 */
void tmp_tcp_client_write(TMP_SOCKET *tmp)
{
    int result;
    /* �������� */
    result = send(tmp->socket, tmp->tcp_client.send_buf, tmp->tcp_client.send_len, 0);
    if (result == SOCKET_ERROR)
    {
        printf("����ʧ��\n");
    }
    else
    {
        printf("���ͳɹ�\n");
        printf_array(tmp->tcp_client.send_buf, tmp->tcp_client.send_len, "send_buf");
    }
}

/**
 * @brief tcp client ���շ���������
 *
 * @param tmp tcp client �ṹ��ָ��
 *
 * @return NULL
 */
void tmp_tcp_client_read(TMP_SOCKET *tmp)
{
    int result;
    /* �������� */
    result = recv(tmp->socket, tmp->tcp_client.recv_buf, tmp->tcp_client.recv_len, 0);
    if (result > 0)
    {
        printf("���ճɹ�\n");
        printf_array(tmp->tcp_client.recv_buf, result, "recv_buf");
    }
    else if (result == 0)
    {
        printf("���ӹرջ����ӳ�ʱ\n");
    }
    else
    {
        printf("����ʧ��\n");
    }
}