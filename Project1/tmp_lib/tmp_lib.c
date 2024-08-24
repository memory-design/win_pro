#include "tmp_lib.h"

/**
 * @brief 打印数组
 * 
 * @param buf 数组指针
 * @param len 需要打印的数组长度
 * @param name 需要打印的字符串指针
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