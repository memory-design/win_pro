#ifndef __TMP_CONFIG_H__
#define __TMP_CONFIG_H__

#ifdef __cplusplus
extern "C"
{
#endif

#include "tmp_def.h"

typedef union 
{
    u32 value;
    struct
    {
        u32 use_dns : 1;    /*  «∑Ò π”√DNS */
        u32 bit1 : 1;
        u32 bit2 : 1;
        u32 bit3 : 1;
        u32 bit4 : 1;
        u32 bit5 : 1;
        u32 bit6 : 1;
        u32 bit7 : 1;
        u32 bit8 : 1;
        u32 bit9 : 1;

        u32 bit10 : 1;
        u32 bit11 : 1;
        u32 bit12 : 1;
        u32 bit13 : 1;
        u32 bit14 : 1;
        u32 bit15 : 1;
        u32 bit16 : 1;
        u32 bit17 : 1;
        u32 bit18 : 1;
        u32 bit19 : 1;

        u32 bit20 : 1;
        u32 bit21 : 1;
        u32 bit22 : 1;
        u32 bit23 : 1;
        u32 bit24 : 1;
        u32 bit25 : 1;
        u32 bit26 : 1;
        u32 bit27 : 1;
        u32 bit28 : 1;
        u32 bit29 : 1;

        u32 bit30 : 1;
        u32 bit31 : 1;
    }bit;
}CONFIG;

typedef struct
{
    CONFIG cfg1;
}TMP_CONFIG;

void tmp_config_init(TMP_CONFIG *tmp);
extern TMP_CONFIG tmp_config;

#ifdef __cplusplus
}
#endif

#endif