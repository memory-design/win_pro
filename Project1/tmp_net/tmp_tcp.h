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
    WSADATA wsa_data;                   /* socket 初始化需要的数据 */
    SOCKET tmp_socket;                  /* socket */
    struct sockaddr_in ser_addr;        /* socket api 需要的服务器ip结构体 */
    u8  ser_ip[4];                      /* 服务器ip */
    char str_ser_ip[30];                /* 服务器ip字符串格式 */
    u16 ser_port;                       /* 服务器端口 */
    u8  *send_buf;                      /* 发送数据缓冲区 */
    u32 send_len;                       /* 发送数据长度 */
    u8  *recv_buf;                      /* 接收数据缓冲区 */
    u32 recv_len;                       /* 接收数据长度 */
    void (*open)(struct _TMP_TCP_CLIENT *);          /* 打开 */
    void (*close)(struct _TMP_TCP_CLIENT *);         /* 关闭 */
    void (*write)(struct _TMP_TCP_CLIENT *);         /* 发送数据 */
    void (*read)(struct _TMP_TCP_CLIENT *);          /* 读取数据 */
    /* data */
}TMP_TCP_CLIENT;

extern TMP_TCP_CLIENT tmp_tcp_client;
void tmp_tcp_init(TMP_TCP_CLIENT *tmp);

#ifdef __cplusplus
}
#endif 

#endif 