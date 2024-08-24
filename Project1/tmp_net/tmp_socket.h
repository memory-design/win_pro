#ifndef __TMP_SOCKET_H__
#define __TMP_SOCKET_H__

#ifdef __cplusplus
extern "C"
{
#endif

#include "tmp_def.h"

typedef struct TMP_SOCKET
{
    WSADATA wsa_data;               /* socket 初始化需要的数据 */
    SOCKET socket;                  /* socket */
    TMP_TCP_CLIENT tcp_client;      /* tcp 客户端结构体 */
    TMP_DNS dns;                    /* dns 结构体 */
}TMP_SOCKET;
extern TMP_SOCKET tmp_socket;


#ifdef __cplusplus
}
#endif

#endif