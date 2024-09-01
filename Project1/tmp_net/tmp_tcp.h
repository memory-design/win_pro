#ifndef __TMP_TCP_H__
#define __TMP_TCP_H__

#ifdef __cplusplus
extern "C"
{
#endif

#include "tmp_def.h"

#define MAX_SEND_BUF_SIZE (1024)
#define MAX_RECV_BUF_SIZE (1024)

    typedef struct _TMP_TCP_CLIENT
    {
        WSADATA wsa_data;                   /* socket ��ʼ����Ҫ������ */
        SOCKET tmp_socket;                  /* socket */
        struct sockaddr_in ser_addr;        /* socket api ��Ҫ�ķ�����ip�ṹ�� */
        u8 ser_ip[4];                       /* ������ip */
        char str_ser_ip[30];                /* ������ip�ַ�����ʽ */
        u16 ser_port;                       /* �������˿� */
        u8 *send_buf;                       /* �������ݻ����� */
        u32 send_len;                       /* �������ݳ��� */
        u8 *recv_buf;                       /* �������ݻ����� */
        u32 recv_len;                       /* �������ݳ��� */
        void (*open)(struct TMP_SOCKET *);  /* �� */
        void (*close)(struct TMP_SOCKET *); /* �ر� */
        void (*write)(struct TMP_SOCKET *); /* �������� */
        void (*read)(struct TMP_SOCKET *);  /* ��ȡ���� */
        /* data */
    } TMP_TCP_CLIENT;

    void tmp_tcp_init(TMP_TCP_CLIENT *tmp);

#ifdef __cplusplus
}
#endif

#endif