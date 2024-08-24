#ifndef __TMP_DNS_H__
#define __TMP_DNS_H__

#ifdef __cplusplus
extern "C"
{
#endif

#include "tmp_def.h"

typedef struct TMP_DNS
{
    char *node;             /* ������ */
    char *service;          /* ������ */
    struct addrinfo hints;
    struct addrinfo *result;
    struct addrinfo *ptr;
    void (*read)(struct TMP_DNS *);
}TMP_DNS;

void tmp_dns_init(TMP_DNS *tmp);

#ifdef __cplusplus
}
#endif

#endif