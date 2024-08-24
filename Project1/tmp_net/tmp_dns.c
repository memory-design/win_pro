#include "tmp_dns.h"

char tmp_dns_node[] = "4ae0d51c50.st1.iotda-device.cn-north-4.myhuaweicloud.com";

void read_dns_info(TMP_DNS *tmp);

/**
 * @brief DNS ��ʼ��
 * 
 * @param tmp dns�ṹ��ָ��
 * 
 * @return NULL
 */
void tmp_dns_init(TMP_DNS *tmp)
{
    /* ����Ҫʹ�õĵ�ַ��Ϣ */
    ZeroMemory(&tmp->hints, sizeof(tmp->hints));
    tmp->hints.ai_family = AF_UNSPEC;               // AF_INET �� AF_INET6
    tmp->hints.ai_socktype = SOCK_STREAM;
    tmp->hints.ai_protocol = IPPROTO_TCP;

    tmp->node = tmp_dns_node;
    tmp->service = NULL;
    tmp->result = NULL;
    tmp->ptr = NULL;

    tmp->read = read_dns_info;
}

/**
 * @brief ��ȡDNS��Ϣ
 * 
 * @param tmp ���ýṹ��ָ��
 * 
 * @return NULL
 */
void read_dns_info(TMP_DNS *tmp)
{
    /* ��ȡ������Ϣ */
    if (getaddrinfo(tmp->node, tmp->service, &tmp->hints, &tmp->result) != 0)
    {
        printf("getaddrinfo failed\n");
        WSACleanup();
        return;
    }

    /* �����������ӡ IP ��ַ */
    for (tmp->ptr = tmp->result; tmp->ptr != NULL; tmp->ptr = tmp->ptr->ai_next)
    {
        // static u32 tmp_cnt1 = 0;
        // tmp_cnt1++;
        // printf("tmp_cnt1 = %d\n", tmp_cnt1);

        void *addr;
        char ip_buf[100];

        /* ���� IPv4 */
        if (tmp->ptr->ai_family == AF_INET)
        {
            struct sockaddr_in *ipv4 = (struct sockaddr_in *)tmp->ptr->ai_addr;
            addr = &(ipv4->sin_addr);
        }
        /* ���� IPv6 */
        else if (tmp->ptr->ai_family == AF_INET6)
        {
            struct sockaddr_in6 *ipv6 = (struct sockaddr_in6 *)tmp->ptr->ai_addr;
            addr = &(ipv6->sin6_addr);
        }
        else
        {
            continue;
        }

        /* �� IP ��ַת��Ϊ�ַ��� */
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