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
        WSADATA wsa_data;                   /* socket 初始化需要的数据 */
        SOCKET tmp_socket;                  /* socket */
        struct sockaddr_in ser_addr;        /* socket api 需要的服务器ip结构体 */
        u8 ser_ip[4];                       /* 服务器ip */
        char str_ser_ip[30];                /* 服务器ip字符串格式 */
        u16 ser_port;                       /* 服务器端口 */
        u8 *send_buf;                       /* 发送数据缓冲区 */
        u32 send_len;                       /* 发送数据长度 */
        u8 *recv_buf;                       /* 接收数据缓冲区 */
        u32 recv_len;                       /* 接收数据长度 */
        void (*open)(struct TMP_SOCKET *);  /* 打开 */
        void (*close)(struct TMP_SOCKET *); /* 关闭 */
        void (*write)(struct TMP_SOCKET *); /* 发送数据 */
        void (*read)(struct TMP_SOCKET *);  /* 读取数据 */
        /* data */
    } TMP_TCP_CLIENT;

    void tmp_tcp_init(TMP_TCP_CLIENT *tmp);

#ifdef __cplusplus
}
#endif

#endif