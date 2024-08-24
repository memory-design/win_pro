#ifndef __TMP_TCP_H__
#define __TMP_TCP_H__

#ifdef __cplusplus
extern "C" { 
#endif 

#include <stdio.h>
#include <winsock2.h>
#include "tmp_def.h"

typedef struct _TMP_TCP_CLIENT  
{
    WSADATA wsa_data;                   /* socket ��ʼ����Ҫ������ */
    SOCKET tmp_socket;                  /* socket */
    struct sockaddr_in ser_addr;        /* socket api ��Ҫ�ķ�����ip�ṹ�� */
    u8  ser_ip[4];                      /* ������ip */
    char str_ser_ip[30];                /* ������ip�ַ�����ʽ */
    u16 ser_port;                       /* �������˿� */
    u8  *send_buf;                      /* �������ݻ����� */
    u32 send_len;                       /* �������ݳ��� */
    u8  *recv_buf;                      /* �������ݻ����� */
    u32 recv_len;                       /* �������ݳ��� */
    void (*open)(struct _TMP_TCP_CLIENT *);          /* �� */
    void (*close)(struct _TMP_TCP_CLIENT *);         /* �ر� */
    void (*write)(struct _TMP_TCP_CLIENT *);         /* �������� */
    void (*read)(struct _TMP_TCP_CLIENT *);          /* ��ȡ���� */
    /* data */
}TMP_TCP_CLIENT;

extern TMP_TCP_CLIENT tmp_tcp_client;
void tmp_tcp_init(TMP_TCP_CLIENT *tmp);

#ifdef __cplusplus
}
#endif 

#endif 