#include "tmp_lib.h"

/**
 * @brief ��ӡ����
 * 
 * @param buf ����ָ��
 * @param len ��Ҫ��ӡ�����鳤��
 * @param name ��Ҫ��ӡ���ַ���ָ��
 * 
 * @return NULL
 */
void printf_array(u8 *buf, u16 len, char *name)
{
    int i = 0;
    printf("%s\n", name);
    printf("len = %d\n", len);
    for(i=0; i<len; i++)
    {
        printf("%02x ", buf[i]);
    }
    printf("\n\n");
}