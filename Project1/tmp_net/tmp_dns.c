#include "tmp_dns.h"

char tmp_dns_node[] = "4ae0d51c50.st1.iotda-device.cn-north-4.myhuaweicloud.com";

void read_dns_info(TMP_DNS *tmp);

/**
 * @brief DNS 初始化
 * 
 * @param tmp dns结构体指针
 * 
 * @return NULL
 */
void tmp_dns_init(TMP_DNS *tmp)
{
    /* 设置要使用的地址信息 */
    ZeroMemory(&tmp->hints, sizeof(tmp->hints));
    tmp->hints.ai_family = AF_UNSPEC;               // AF_INET 或 AF_INET6
    tmp->hints.ai_socktype = SOCK_STREAM;
    tmp->hints.ai_protocol = IPPROTO_TCP;

    tmp->node = tmp_dns_node;
    tmp->service = NULL;
    tmp->result = NULL;
    tmp->ptr = NULL;

    tmp->read = read_dns_info;
}

/**
 * @brief 读取DNS信息
 * 
 * @param tmp 配置结构体指针
 * 
 * @return NULL
 */
void read_dns_info(TMP_DNS *tmp)
{
    /* 获取主机信息 */
    if (getaddrinfo(tmp->node, tmp->service, &tmp->hints, &tmp->result) != 0)
    {
        printf("getaddrinfo failed\n");
        WSACleanup();
        return;
    }

    /* 遍历结果并打印 IP 地址 */
    for (tmp->ptr = tmp->result; tmp->ptr != NULL; tmp->ptr = tmp->ptr->ai_next)
    {
        // static u32 tmp_cnt1 = 0;
        // tmp_cnt1++;
        // printf("tmp_cnt1 = %d\n", tmp_cnt1);

        void *addr;
        char ip_buf[100];

        /* 处理 IPv4 */
        if (tmp->ptr->ai_family == AF_INET)
        {
            struct sockaddr_in *ipv4 = (struct sockaddr_in *)tmp->ptr->ai_addr;
            addr = &(ipv4->sin_addr);
        }
        /* 处理 IPv6 */
        else if (tmp->ptr->ai_family == AF_INET6)
        {
            struct sockaddr_in6 *ipv6 = (struct sockaddr_in6 *)tmp->ptr->ai_addr;
            addr = &(ipv6->sin6_addr);
        }
        else
        {
            continue;
        }

        /* 将 IP 地址转换为字符串 */
        if (inet_ntop(tmp->ptr->ai_family, addr, ip_buf, sizeof(ip_buf)) != NULL)
        {
            printf("IP address: %s\n", ip_buf);
        }
        else
        {
            fprintf(stderr, "inet_ntop failed.\n");
        }
    }
}