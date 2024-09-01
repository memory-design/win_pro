#define _CRT_SECURE_NO_WARNINGS
#include "tmp_mqtt.h"
#include "tmp_socket.h"
#include "tmp_tcp.h"
#include "tmp_def.h"

#define MAX_PUB_MSG_SIZE (256)
char tmp_client_id[] = "66ca9910d8c5af5f58f49361_humiture_0_0_2024082815";
char tmp_user_name[] = "66ca9910d8c5af5f58f49361_humiture";
char tmp_password[] = "71948183c5783b5e816e1c8dbca33398da11c8e0c27451afc71ca10c08478e13";
char tmp_sub_topic[] = "$oc/devices/66ca9910d8c5af5f58f49361_humiture/sys/messages/down";
char tmp_pub_topic[] = "$oc/devices/66ca9910d8c5af5f58f49361_humiture/sys/properties/report";
char tmp_pub_msg[MAX_PUB_MSG_SIZE] = {0x00};

MQTT_CTRL mqtt_ctrl = {0};

/**
 * @brief mqtt��ʼ��
 *
 * @param ctrl ����ָ��
 *
 * @return NULL
 */
void mqtt_init(MQTT_CTRL *ctrl)
{
    ctrl->client_id = tmp_client_id;
    ctrl->user_name = tmp_user_name;
    ctrl->password = tmp_password;
    ctrl->sub_topic = tmp_sub_topic;
    ctrl->pub_topic = tmp_pub_topic;
    ctrl->pub_msg = tmp_pub_msg;

    ctrl->connect = mqtt_connect;
    ctrl->sub_usub = mqtt_sub_usub_topic;
    ctrl->publish = mqtt_publish;
    ctrl->refresh_pub_msg = refresh_publish_msg;
    ctrl->handle = mqtt_handle;
}

/**
 * @brief ����ʣ�೤��
 *
 * @param tmp_head �̶���ͷָ��
 * @param data_len ʣ�೤��
 *
 * @return NULL
 */
void tmp_cal_remain_len(MQTT_FIX_HEAD *tmp_head, u32 data_len)
{
    /* ��ʼ��ʣ�೤�Ⱥ��ֽڼ���Ϊ0 */
    memset(tmp_head->remain_len, 0x00, sizeof(tmp_head->remain_len));
    tmp_head->reman_index = 0;

    do
    {
        u8 encodedByte = data_len % 128;
        data_len = data_len / 128;

        // if there are more data to encode, set the top bit of this byte
        if (data_len > 0)
            encodedByte = encodedByte | 128;
        tmp_head->remain_len[tmp_head->reman_index++] = encodedByte;
    } while (data_len > 0);
}

/**
 * @brief mqtt ����
 *
 * @param ctrl mqtt ���ƽṹ��ָ��
 *
 * @return NULL
 */
void mqtt_connect(MQTT_CTRL *ctrl)
{
    TMP_SOCKET *socket_p = &tmp_socket;
    MQTT_FIX_HEAD *fix_head = (MQTT_FIX_HEAD *)(socket_p->tcp_client.send_buf);
    u32 tmp_remain_len = 10 + (u32)strlen(ctrl->client_id) + (u32)strlen(ctrl->user_name) + (u32)strlen(ctrl->password) + 2 * 3;

    TMP_U16 tmp_u16 = {0};

    /* ������ͻ����� */
    memset(socket_p->tcp_client.send_buf, 0, MAX_SEND_BUF_SIZE);

    /* ����ʣ�೤�� */
    tmp_cal_remain_len(fix_head, tmp_remain_len);

    /* ���㷢�ͳ��� */
    socket_p->tcp_client.send_len = tmp_remain_len + 1 + fix_head->reman_index;

    /* �̶���ͷ */
    fix_head->byte1.bits.packet_type = CTRL_PACK_TYPE_CONNECT;

    /* �ɱ䱨ͷ */
    MQTT_CON_VAR_HEAD *var_head = (MQTT_CON_VAR_HEAD *)(socket_p->tcp_client.send_buf + 1 + fix_head->reman_index);
    tmp_u16.u16_val = 4;
    var_head->protocol_name.length.msb = tmp_u16.byte.msb;
    var_head->protocol_name.length.lsb = tmp_u16.byte.lsb;
    memcpy(var_head->protocol_name.name, "MQTT", 4);

    var_head->protocol_level = 4;

    var_head->con_flag.bit.reserved = 0;
    var_head->con_flag.bit.clean_session = 1;
    var_head->con_flag.bit.will_flag = 0;
    var_head->con_flag.bit.will_qos = 0;
    var_head->con_flag.bit.will_retain = 0;
    var_head->con_flag.bit.password_flag = 1;
    var_head->con_flag.bit.user_name_flag = 1;

    tmp_u16.u16_val = 100;
    var_head->keep_alive.msb = tmp_u16.byte.msb;
    var_head->keep_alive.lsb = tmp_u16.byte.lsb;

    /* ��Ч�غ� */
    u8 *payload = var_head->buf;
    u32 tmp_index = 0;

    tmp_u16.u16_val = (u16)strlen(ctrl->client_id);
    payload[tmp_index++] = tmp_u16.byte.msb;
    payload[tmp_index++] = tmp_u16.byte.lsb;
    memcpy(payload + tmp_index, ctrl->client_id, tmp_u16.u16_val);

    tmp_index += tmp_u16.u16_val;
    tmp_u16.u16_val = (u16)strlen(ctrl->user_name);
    payload[tmp_index++] = tmp_u16.byte.msb;
    payload[tmp_index++] = tmp_u16.byte.lsb;
    memcpy(payload + tmp_index, ctrl->user_name, tmp_u16.u16_val);

    tmp_index += tmp_u16.u16_val;
    tmp_u16.u16_val = (u16)strlen(ctrl->password);
    payload[tmp_index++] = tmp_u16.byte.msb;
    payload[tmp_index++] = tmp_u16.byte.lsb;
    memcpy(payload + tmp_index, ctrl->password, tmp_u16.u16_val);

    PRINTF_FUNC_NAME;

    /* �������� */
    socket_p->tcp_client.write(socket_p);

    /* �������� */
    socket_p->tcp_client.read(socket_p);
}

/**
 * @brief mqtt ����/ȡ�� ����
 *
 * @param ctrl mqtt ���ƽṹ��ָ��
 * @param qos QoS����
 * @param sub_usub_flag ����/ȡ����־ 1 ����, 0 ȡ��
 *
 * @return NULL
 */
void mqtt_sub_usub_topic(MQTT_CTRL *ctrl, u8 qos, u8 sub_usub_flag)
{
    u32 tmp_index = 0;

    TMP_SOCKET *socket_p = &tmp_socket;
    MQTT_FIX_HEAD *fix_head = (MQTT_FIX_HEAD *)(socket_p->tcp_client.send_buf);
    u32 topiclen = (u32)strlen(ctrl->sub_topic);
    u32 tmp_remain_len = 2 + (topiclen + 2) + (sub_usub_flag ? 1 : 0); // �ɱ䱨ͷ�ĳ��ȣ�2�ֽڣ�������Ч�غɵĳ���

    TMP_U16 tmp_u16 = {0};

    /* ������ͻ����� */
    memset(socket_p->tcp_client.send_buf, 0, MAX_SEND_BUF_SIZE);

    /* ����ʣ�೤�� */
    tmp_cal_remain_len(fix_head, tmp_remain_len);

    /* ���㷢�ͳ��� */
    socket_p->tcp_client.send_len = tmp_remain_len + 1 + fix_head->reman_index;

    fix_head->byte1.bits.packet_type = CTRL_PACK_TYPE_CONNECT;

    /* �̶���ͷ */
    if (sub_usub_flag)
    {
        fix_head->byte1.bits.packet_type = CTRL_PACK_TYPE_SUBSCRIBE;
        fix_head->byte1.bits.reserved = 0x02;
    }
    else
    {
        fix_head->byte1.bits.packet_type = CTRL_PACK_TYPE_UNSUBSCRIBE;
        fix_head->byte1.bits.reserved = 0x02;
    }

    // �ɱ䱨ͷ
    MQTT_SUB_VAR_HEAD *var_head = (MQTT_SUB_VAR_HEAD *)(socket_p->tcp_client.send_buf + 1 + fix_head->reman_index);
    tmp_u16.u16_val = 1;
    var_head->packet_identifier.msb = tmp_u16.byte.msb;
    var_head->packet_identifier.lsb = tmp_u16.byte.lsb;

    // ��Ч�غ�
    u8 *payload = var_head->buf;
    tmp_u16.u16_val = topiclen;
    payload[tmp_index++] = tmp_u16.byte.msb;
    payload[tmp_index++] = tmp_u16.byte.lsb;
    memcpy(payload + tmp_index, ctrl->sub_topic, topiclen);
    tmp_index += topiclen;
    if (sub_usub_flag)
    {
        payload[tmp_index++] = qos; // QoS����
    }

    PRINTF_FUNC_NAME;

    /* �������� */
    socket_p->tcp_client.write(socket_p);

    /* �������� */
    socket_p->tcp_client.read(socket_p);
}

/**
 * @brief mqtt ��������
 *
 * @param ctrl mqtt ���ƽṹ��ָ��
 * @param qos QoS����
 *
 * @return NULL
 */
void mqtt_publish(MQTT_CTRL *ctrl, u8 qos)
{
    TMP_U16 tmp_u16 = {0};
    u32 topicLength = (u32)strlen(ctrl->pub_topic);
    u32 messageLength = (u32)strlen(ctrl->pub_msg);
    u16 id = 0;
    u32 tmp_remain_len;
    u32 tmp_index = 0;

    TMP_SOCKET *socket_p = &tmp_socket;
    MQTT_FIX_HEAD *fix_head = (MQTT_FIX_HEAD *)(socket_p->tcp_client.send_buf);

    if (qos)
        tmp_remain_len = (2 + topicLength) + 2 + messageLength;
    else
        tmp_remain_len = (2 + topicLength) + messageLength;

    /* ������ͻ����� */
    memset(socket_p->tcp_client.send_buf, 0, MAX_SEND_BUF_SIZE);

    /* ����ʣ�೤�� */
    tmp_cal_remain_len(fix_head, tmp_remain_len);

    /* ���㷢�ͳ��� */
    socket_p->tcp_client.send_len = tmp_remain_len + 1 + fix_head->reman_index;

    /* �̶���ͷ */
    fix_head->byte1.bits.packet_type = CTRL_PACK_TYPE_PUBLISH;

    /* �ɱ䱨ͷ */
    MQTT_PUB_VAR_HEAD *var_head = (MQTT_PUB_VAR_HEAD *)(socket_p->tcp_client.send_buf + 1 + fix_head->reman_index);
    tmp_u16.u16_val = topicLength;
    var_head->topic_len.msb = tmp_u16.byte.msb;
    var_head->topic_len.lsb = tmp_u16.byte.lsb;
    memcpy(var_head->buf, ctrl->pub_topic, topicLength);

    // ���ı�ʶ��
    if (qos)
    {
        tmp_u16.u16_val = id;
        var_head->buf[topicLength + 0] = tmp_u16.byte.msb;
        var_head->buf[topicLength + 1] = tmp_u16.byte.lsb;
        id++;
        memcpy(var_head->buf + topicLength + 2, ctrl->pub_msg, messageLength);
    }
    else
    {
        memcpy(var_head->buf + topicLength, ctrl->pub_msg, messageLength);
    }

    PRINTF_FUNC_NAME;

    /* �������� */
    socket_p->tcp_client.write(socket_p);
}

/**
 * @brief ˢ�·�������
 *
 * @param ctrl mqtt ���ƽṹ��ָ��
 *
 * @return NULL
 */
void refresh_publish_msg(MQTT_CTRL *ctrl, u8 *buf, u16 len)
{
    static double TEMP = 10.0;
    memset(ctrl->pub_msg, 0, MAX_PUB_MSG_SIZE);
    memcpy(ctrl->pub_msg, buf, len);
}

/**
 * @brief mqtt ����
 *
 * @param ctrl mqtt ���ƽṹ��ָ��
 *
 * @return NULL
 */
void mqtt_handle(MQTT_CTRL *ctrl)
{
    double TEMP = 10.0;
    u8 tmp_pub_buf[MAX_PUB_MSG_SIZE] = {0};

    /* mqtt ���� */
    ctrl->connect(ctrl);

    /* mqtt �������� */
    ctrl->sub_usub(ctrl, 1, 1);

    while (1)
    {
        memset(tmp_pub_buf, 0, MAX_PUB_MSG_SIZE);
        sprintf(tmp_pub_buf, "{\"services\": [{\"service_id\": \"humiture\",\"properties\":{\"TEMP\":%.1f}}]}", (double)(TEMP += 0.2));
        printf("TEMP = %.1f\r\n\n", TEMP);

        /* ˢ�·�����Ϣ */
        ctrl->refresh_pub_msg(ctrl, tmp_pub_buf, strlen(tmp_pub_buf));

        /* mqtt ������Ϣ */
        ctrl->publish(ctrl, 0);
        Sleep(5000);
    }
}

/**
 * @brief mqtt ����
 *
 * @param NULL
 *
 * @return NULL
 */
void mqtt_task(void)
{
    MQTT_CTRL *ctrl = &mqtt_ctrl;

    /* mqtt ��ʼ�� */
    mqtt_init(ctrl);

    /* mqtt ���� */
    ctrl->handle(ctrl);
}