#ifndef __TMP_DEF_H__
#define __TMP_DEF_H__

#ifdef __cplusplus
extern "C"
{
#endif

/* 声明数据类型 */
    typedef unsigned char u8;
    typedef unsigned short u16;
    typedef unsigned int u32;

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include "tmp_tcp.h"
#include "tmp_dns.h"
#include "tmp_config.h"

/* 宏定义打印函数名 */
#define PRINTF_FUNC_NAME printf("%s\n", __FUNCTION__);

#ifdef __cplusplus
}
#endif

#endif