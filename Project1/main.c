#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
#include "tmp_def.h"
#include "tmp_def.h"
#include "tmp_tcp.h"

#pragma comment(lib, "ws2_32.lib")
TMP_TCP_CLIENT *tmp1 = NULL;
int main(void)
{
    tmp1 = &tmp_tcp_client;
    tmp_tcp_init(tmp1);
    tmp1->open(tmp1);
    while(1)
    {
        tmp1->read(tmp1);
        memcpy(tmp1->send_buf, "123456890", strlen("123456890"));
        tmp1->send_len = strlen("123456890");
        tmp1->write(tmp1);
        Sleep(1000);
    }
    return 0;
}
