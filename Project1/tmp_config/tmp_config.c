#include "tmp_config.h"
TMP_CONFIG tmp_config = { 0x00 };

/**
 * @brief 配置初始化
 * 
 * @param tmp 配置结构体指针
 * 
 * @return NULL
 */
void tmp_config_init(TMP_CONFIG *tmp)
{
    PRINTF_FUNC_NAME
    tmp->cfg1.bit.use_dns = 0x01;
}