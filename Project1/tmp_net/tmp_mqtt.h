#ifndef __TMP_MQTT_H__
#define __TMP_MQTT_H__

#ifdef __cplusplus
extern "C"
{
#endif

#include "tmp_def.h"

#pragma pack(1)
    typedef struct
    {
        u8 msb;
        u8 lsb;
    } MQTT_BYTE_FORMAT;

/************************CONNECT*********************************/
#define CTRL_PACK_TYPE_RESERVED1 0x00
#define CTRL_PACK_TYPE_CONNECT 0x01
#define CTRL_PACK_TYPE_CONNACK 0x02
#define CTRL_PACK_TYPE_PUBLISH 0x03
#define CTRL_PACK_TYPE_PUBACK 0x04
#define CTRL_PACK_TYPE_PUBREC 0x05
#define CTRL_PACK_TYPE_PUBREL 0x06
#define CTRL_PACK_TYPE_PUBCOMP 0x07
#define CTRL_PACK_TYPE_SUBSCRIBE 0x08
#define CTRL_PACK_TYPE_SUBACK 0x09
#define CTRL_PACK_TYPE_UNSUBSCRIBE 0x0a
#define CTRL_PACK_TYPE_UNSUBACK 0x0b
#define CTRL_PACK_TYPE_PINGREQ 0x0c
#define CTRL_PACK_TYPE_PINGRESP 0x0d
#define CTRL_PACK_TYPE_DISCONNECT 0x0e
#define CTRL_PACK_TYPE_RESERVED2 0x0f

    /*****************************************固定报头***************************************************/
    typedef union
    {
        u8 data;
        struct
        {
            u8 reserved : 4;
            u8 packet_type : 4;
        } bits;
    } MQTT_FIX_HEAD_BYTE1;

    typedef struct
    {
        MQTT_FIX_HEAD_BYTE1 byte1;
        u8 remain_len[4];
        u8 reman_index;
    } MQTT_FIX_HEAD;
    /*****************************************固定报头***************************************************/

    /*****************************************连接可变报头***************************************************/
    typedef struct
    {
        MQTT_BYTE_FORMAT length;
        u8 name[4];
    } MQTT_CON_VAR_HEAD_PROTOCOL_NAME;

    typedef union
    {
        u8 flag;
        struct
        {
            u8 reserved : 1;
            u8 clean_session : 1;
            u8 will_flag : 1;
            u8 will_qos : 2;
            u8 will_retain : 1;
            u8 password_flag : 1;
            u8 user_name_flag : 1;
        } bit;
    } MQTT_CON_VAR_HEAD_CON_FLAG;

    typedef struct
    {
        MQTT_CON_VAR_HEAD_PROTOCOL_NAME protocol_name;
        u8 protocol_level;
        MQTT_CON_VAR_HEAD_CON_FLAG con_flag;
        MQTT_BYTE_FORMAT keep_alive;
        u8 buf[];
    } MQTT_CON_VAR_HEAD;
    /*****************************************连接可变报头***************************************************/

    /*****************************************订阅可变报头***************************************************/
    typedef struct
    {
        MQTT_BYTE_FORMAT packet_identifier;
        u8 buf[];
    } MQTT_SUB_VAR_HEAD;
    /*****************************************订阅可变报头***************************************************/

    /*****************************************推送可变报头***************************************************/
    typedef struct
    {
        MQTT_BYTE_FORMAT topic_len;
        u8 buf[];
    } MQTT_PUB_VAR_HEAD;
    /*****************************************推送可变报头***************************************************/

    /************************MQTT_CTRL*********************************/
    typedef struct MQTT_CTRL
    {
        char *client_id; /*设备ID*/
        char *user_name; /*用户名*/
        char *password;  /*密码*/
        char *sub_topic; /*订阅主题*/
        char *pub_topic; /*发布主题*/
        char *pub_msg;   /*发布消息*/
        void (*connect)(struct MQTT_CTRL *);
        void (*sub_usub)(struct MQTT_CTRL *, u8, u8);
        void (*publish)(struct MQTT_CTRL *, u8);
        void (*refresh_pub_msg)(struct MQTT_CTRL *, u8 *buf, u16 len);
        void (*handle)(struct MQTT_CTRL *);
    } MQTT_CTRL;
    extern MQTT_CTRL mqtt_ctrl;
    /************************MQTT_CTRL*********************************/
#pragma pack()

    void mqtt_init(MQTT_CTRL *ctrl);
    void mqtt_connect(MQTT_CTRL *ctrl);
    void mqtt_sub_usub_topic(MQTT_CTRL *ctrl, u8 qos, u8 sub_usub_flag);
    void mqtt_publish(MQTT_CTRL *ctrl, u8 qos);
    void refresh_publish_msg(MQTT_CTRL *ctrl);
    void mqtt_handle(MQTT_CTRL *ctrl);
    void mqtt_task(void);

    /*
    华为云的MQTT服务器地址：117.78.5.125
    华为云的MQTT端口号：1883

    {
        "device_id": "66ca9910d8c5af5f58f49361_humiture",
        "secret": "12345678"
    }

    {
        "ClientId": "66ca9910d8c5af5f58f49361_humiture_0_0_2024082722",
        "Username": "66ca9910d8c5af5f58f49361_humiture",
        "Password": "fe930ab33d7237d2febddb3588b1e32552debbe440aba1c337a75d8a97622f0c"
    }

    以当前设备为例，最终订阅主题的格式如下:
    $oc/devices/{device_id}/sys/messages/down

    最终的格式:
    $oc/devices/66ca9910d8c5af5f58f49361_humiture/sys/messages/down

    发布的主题格式:
    $oc/devices/{device_id}/sys/properties/report

    最终的格式:
    $oc/devices/66ca9910d8c5af5f58f49361_humiture/sys/properties/report
    发布主题时，需要上传数据，这个数据格式是JSON格式。

    上传的JSON数据格式如下:

    {
      "services": [
        {
          "service_id": <填服务ID>,
          "properties": {
            "<填属性名称1>": <填属性值>,
            "<填属性名称2>": <填属性值>,
            ..........
          }
        }
      ]
    }
    根据JSON格式，一次可以上传多个属性字段。 这个JSON格式里的，服务ID，属性字段名称，属性值类型，在前面创建产品的时候就已经介绍了，不记得可以翻到前面去查看。

    根据这个格式，组合一次上传的属性数据:
    {"services": [{"service_id": "stm32","properties":{"TEMP":36.2}}]}

    */

#ifdef __cplusplus
}
#endif

#endif