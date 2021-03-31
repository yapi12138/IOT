/*
 * Copyright (c) 2006-2020, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-09-02     RT-Thread    first version
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <drv_common.h>

#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <rtdbg.h>
#include "paho_mqtt.h"
#include <cJSON.h>

#include <mypi.h>
#include "oled.h"

static rt_timer_t timer2;

#define DBG_ENABLE
#define DBG_SECTION_NAME    "mqtt.sample"
#define DBG_LEVEL           DBG_LOG
#define DBG_COLOR

#define MQTT_URI                "tcp://192.168.43.26:1883"
#define MQTT_USERNAME           "My Pi"
#define MQTT_PASSWORD           "My Pi"
#define MQTT_SUBTOPIC           "/toPi"
//#define MQTT_SUBTOPIC1          "/toAll"
#define MQTT_PUBTOPIC           "/toyun"
#define MQTT_WILLMSG            "Goodbye!"

#define WLAN_SSID               "ZTT"
#define WLAN_PASSWORD           "zzz123456"

int is_started = 0;

void mqtt_sub_callback(MQTTClient *c, MessageData *msg_data)
{
    *((char *)msg_data->message->payload + msg_data->message->payloadlen) = '\0';
    LOG_D("mqtt sub callback: %.*s %.*s",
               msg_data->topicName->lenstring.len,
               msg_data->topicName->lenstring.data,
               msg_data->message->payloadlen,
               (char *)msg_data->message->payload);
    //rt_kprintf((char *)msg_data->message->payload);

    //ssdme((char *)msg_data->message->payload);
  /*  sprintf(param,"%s",(char *)msg_data->message->payload);

    if(param=="/'LED5:0/'") rt_pin_write(LED5, PIN_LOW);
     if(param=="/'LED5:1/'") rt_pin_write(LED5, PIN_HIGH);

     if((char *)msg_data->message->payload=="KA1:0") rt_pin_write(KA1, PIN_LOW);
     if((char *)msg_data->message->payload=="/'KA1:1/'") rt_pin_write(KA1, PIN_HIGH);

     if(param=="KA2:0") rt_pin_write(KA2, PIN_LOW);
     if(param=="KA2:1") rt_pin_write(KA2, PIN_HIGH);*/

     cJSON *root = RT_NULL, *device = RT_NULL, *statu = RT_NULL;

        root = cJSON_Parse( (char *)msg_data->message->payload);
        if (!root)
        {
            rt_kprintf("No memory for cJSON root!\n");
            return;
        }

        device= cJSON_GetObjectItem(root, "device");
        statu = cJSON_GetObjectItem(root, "statu");

        //rt_pin_write(device->valueint, statu->valueint);
        rt_kprintf("\ndevice:%d,statu:%d", device->valueint,statu->valueint);
       // u8g2_DrawStr(&u8g2, 10, 25,  "device :");




        if(device->valueint==1)
        {
            if(statu->valueint)
            {
                ssdme22("1", "1");
                rt_pin_write(LED5, PIN_HIGH);
            }
            else
            {
                ssdme22("1", "0");
                rt_pin_write(LED5, PIN_LOW);
            }
        }

        if(device->valueint==2)
        {
            if(statu->valueint)
            {
                ssdme22("2", "1");
                rt_pin_write(KA1, PIN_HIGH);
            }
            else
            {
                ssdme22("2", "0");
                rt_pin_write(KA1, PIN_LOW);
            }
        }

        if(device->valueint==3)
        {
            if(statu->valueint)
            {
                ssdme22("3", "1");
                rt_pin_write(KA2, PIN_HIGH);
            }
            else
            {
                ssdme22("3", "0");
                rt_pin_write(KA2, PIN_LOW);
            }

         }


        if (root != RT_NULL)
            cJSON_Delete(root);
}


void mqtt_sub_callback1(MQTTClient *c, MessageData *msg_data)
{
    *((char *)msg_data->message->payload + msg_data->message->payloadlen) = '\0';
    LOG_D("mqtt sub callback: %.*s %.*s",
               msg_data->topicName->lenstring.len,
               msg_data->topicName->lenstring.data,
               msg_data->message->payloadlen,
               void ssdme(char me[],char me1[]););

    ssdme((char *)msg_data->message->payload);


}


void mqtt_sub_default_callback(MQTTClient *c, MessageData *msg_data)
{
    *((char *)msg_data->message->payload + msg_data->message->payloadlen) = '\0';
    LOG_D("mqtt sub default callback: %.*s %.*s",
               msg_data->topicName->lenstring.len,
               msg_data->topicName->lenstring.data,
               msg_data->message->payloadlen,
               (char *)msg_data->message->payload);

   // ssdme((char *)msg_data->message->payload);
}


void mqtt_connect_callback(MQTTClient *c)
{
    LOG_D("inter mqtt_connect_callback!");
}


void mqtt_online_callback(MQTTClient *c)
{
    LOG_D("inter mqtt_online_callback!");
    rt_pin_write(LED4, PIN_HIGH);
    ssdmqttok();
}


void mqtt_offline_callback(MQTTClient *c)
{
    LOG_D("inter mqtt_offline_callback!");
    rt_pin_write(LED4, PIN_LOW);
}


int mqtt_start(int argc, char **argv)
{
    /* init condata param by using MQTTPacket_connectData_initializer */
    MQTTPacket_connectData condata = MQTTPacket_connectData_initializer;
    //static char cid[20] = { 0 };

    if (argc != 1)
    {
        rt_kprintf("mqtt_start    --start a mqtt worker thread.\n");
        return -1;
    }

    if (is_started)
    {
        LOG_E("mqtt client is already connected.");
        return -1;
    }
    /* config MQTT context param */
    {
        client.isconnected = 0;
        client.uri = MQTT_URI;

        /* generate the random client ID */
        //rt_snprintf(cid, sizeof(cid), "rtthread%d", rt_tick_get());
        /* config connect param */
        memcpy(&client.condata, &condata, sizeof(condata));
        client.condata.clientID.cstring = "My Pi";
        client.condata.keepAliveInterval = 60;
        client.condata.cleansession = 1;
        client.condata.username.cstring = MQTT_USERNAME;
        client.condata.password.cstring = MQTT_PASSWORD;

        /* config MQTT will param. */
        client.condata.willFlag = 1;
        client.condata.will.qos = 1;
        client.condata.will.retained = 0;
        client.condata.will.topicName.cstring = MQTT_PUBTOPIC;
        client.condata.will.message.cstring = MQTT_WILLMSG;

        /* malloc buffer. */
        client.buf_size = client.readbuf_size = 1024;
        client.buf = rt_calloc(1, client.buf_size);
        client.readbuf = rt_calloc(1, client.readbuf_size);
        if (!(client.buf && client.readbuf))
        {
            LOG_E("no memory for MQTT client buffer!");
            return -1;
        }

        /* set event callback function */
        client.connect_callback = mqtt_connect_callback;
        client.online_callback = mqtt_online_callback;
        client.offline_callback = mqtt_offline_callback;

        /* set subscribe table and event callback */
        client.messageHandlers[0].topicFilter = rt_strdup(MQTT_SUBTOPIC);
        client.messageHandlers[0].callback = mqtt_sub_callback;
        client.messageHandlers[0].qos = QOS1;

        //client.messageHandlers[1].topicFilter = rt_strdup(MQTT_SUBTOPIC1);
       // client.messageHandlers[1].callback = mqtt_sub_callback1;
        //client.messageHandlers[1].qos = QOS1;


        /* set default subscribe event callback */
        client.defaultMessageHandler = mqtt_sub_default_callback;
    }

    /* run mqtt client */
    paho_mqtt_start(&client);
    is_started = 1;

    return 0;
}


int mqtt_stop(int argc, char **argv)
{
    if (argc != 1)
    {
        rt_kprintf("mqtt_stop    --stop mqtt worker thread and free mqtt client object.\n");
    }

    is_started = 0;

    return paho_mqtt_stop(&client);
}


int mqtt_publish(int argc, char **argv)
{
   if (is_started == 0)
    {
        LOG_E("mqtt client is not connected.");
        return -1;
    }

    if (argc == 2)
    {
        paho_mqtt_publish(&client, QOS1, MQTT_PUBTOPIC, argv[1]);
    }
    else if (argc == 3)
    {
        paho_mqtt_publish(&client, QOS1, "toYun", "argv");
    }

    else
    {
        rt_kprintf("mqtt_publish <topic> [message]  --mqtt publish message to specified topic.\n");
        return -1;
    }

    return 0;
}


void mqtt_new_sub_callback(MQTTClient *client, MessageData *msg_data)
{
    *((char *)msg_data->message->payload + msg_data->message->payloadlen) = '\0';
    LOG_D("mqtt new subscribe callback: %.*s %.*s",
               msg_data->topicName->lenstring.len,
               msg_data->topicName->lenstring.data,
               msg_data->message->payloadlen,
               (char *)msg_data->message->payload);
}


int mqtt_subscribe(int argc, char **argv)
{
    if (argc != 2)
    {
        rt_kprintf("mqtt_subscribe [topic]  --send an mqtt subscribe packet and wait for suback before returning.\n");
        return -1;
    }

    if (is_started == 0)
    {
        LOG_E("mqtt client is not connected.");
        return -1;
    }

    return paho_mqtt_subscribe(&client, QOS1, argv[1], mqtt_new_sub_callback);
}


int mqtt_unsubscribe(int argc, char **argv)
{
    if (argc != 2)
    {
        rt_kprintf("mqtt_unsubscribe [topic]  --send an mqtt unsubscribe packet and wait for suback before returning.\n");
        return -1;
    }

    if (is_started == 0)
    {
        LOG_E("mqtt client is not connected.");
        return -1;
    }

    return paho_mqtt_unsubscribe(&client, argv[1]);
}


int main(void)
{
    rt_uint32_t count = 1;

    //timer2 = rt_timer_create("timer2",ti,RT_NULL,1000,RT_TIMER_FLAG_PERIODIC|RT_TIMER_FLAG_SOFT_TIMER);



    piledinit();
    pikainit();
    ssdinit();

    while(count++)
    {
        rt_thread_mdelay(500);
        rt_pin_write(LED2, PIN_HIGH);
        rt_thread_mdelay(500);
        rt_pin_write(LED2, PIN_LOW);
      //  rt_pin_write(LED5, PIN_HIGH);


        if (rt_wlan_is_ready()==RT_TRUE)
            rt_pin_write(LED3, PIN_HIGH);
        else
            rt_pin_write(LED3, PIN_LOW);


        switch(pireadkey())
        {
            case 1: rt_pin_write(KA1, PIN_HIGH);
                paho_mqtt_publish(&client, QOS1, "/toYun","{ \"device\":2,\"statu\":1}");
                break;

            case 2:paho_mqtt_publish(&client, QOS1, "/to8266","{ \"device\":1,\"statu\":1}");
                break;

            case 3: rt_pin_write(KA1, PIN_LOW);
                paho_mqtt_publish(&client, QOS1, "/toYun","{ \"device\":2,\"statu\":0}");
                break;

            case 4:paho_mqtt_publish(&client, QOS1, "/to8266","{ \"device\":1,\"statu\":0}");
                break;

            case 5:while(RT_FALSE==rt_wlan_is_ready())
                {
                    ssdwifilink();

                    rt_wlan_connect(WLAN_SSID, WLAN_PASSWORD);
                }
                ssdwifiok();
                break;

           case 6:ssdmqttlink();
                mqtt_start(1,"ok");
                break;

           case 7://if (timer2 != RT_NULL) rt_timer_start(timer2);
               msh_exec("dht11_read_temp_sample", strlen("dht11_read_temp_sample"));
                break;




        }

    }
    return RT_EOK;
}


#include "stm32h7xx.h"
static int vtor_config(void)
{
    /* Vector Table Relocation in Internal QSPI_FLASH */
    SCB->VTOR = QSPI_BASE;
    return 0;
}
INIT_BOARD_EXPORT(vtor_config);



