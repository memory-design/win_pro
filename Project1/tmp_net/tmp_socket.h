#ifndef __TMP_SOCKET_H__
#define __TMP_SOCKET_H__

#ifdef __cplusplus
extern "C"
{
#endif

#include "tmp_def.h"

typedef struct TMP_SOCKET
{
    WSADATA wsa_data;               /* socket ��ʼ����Ҫ������ */
    SOCKET socket;                  /* socket */
    TMP_TCP_CLIENT tcp_client;      /* tcp �ͻ��˽ṹ�� */
    TMP_DNS dns;                    /* dns �ṹ�� */
}TMP_SOCKET;
extern TMP_SOCKET tmp_socket;


#ifdef __cplusplus
}
#endif

#endif