/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author         Notes
 * 2019-08-01     LuoGong         the first version.
 * 2019-08-15     MurphyZhao      add lock and modify code style
 */

#include <rtthread.h>
#include <rtdevice.h>
#include "sensor.h"
#include "sensor_dallas_dht11.h"
#include "drv_gpio.h"
#include "oled.h"
#include <stdio.h>

#include <ntp.h>

#include "drv_common.h"
#include "paho_mqtt.h"


int a=1;

char param[];
char param1[];
char param2[];

char mstr[3];
char hstr[3];


/* Modify this pin according to the actual wiring situation */
#define DHT11_DATA_PIN    GET_PIN(I, 5)

static void read_temp_entry(void *parameter)
{
    rt_device_t dev = RT_NULL;
    struct rt_sensor_data sensor_data;
    rt_size_t res;
    rt_uint8_t get_data_freq = 1; /* 1Hz */

    dev = rt_device_find("temp_dht11");

    if (a==1) {


    if (dev == RT_NULL)
    {
        return;
    }

    if (rt_device_open(dev, RT_DEVICE_FLAG_RDWR) != RT_EOK)
    {
        rt_kprintf("open device failed!\n");
        return;
    }

    rt_device_control(dev, RT_SENSOR_CTRL_SET_ODR, (void *)(&get_data_freq));
    a=2;
    }

        res = rt_device_read(dev, 0, &sensor_data, 1);

        if (res != 1)
        {
            rt_kprintf("read data failed! result is %d\n", res);
            rt_device_close(dev);
            return;
        }
        else
        {
            if (sensor_data.data.temp >= 0)
            {
                 uint8_t temp = (sensor_data.data.temp & 0xffff) >> 0;      // get temp
                 uint8_t humi = (sensor_data.data.temp & 0xffff0000) >> 16; // get humi

                rt_kprintf("temp:%d, humi:%d\n" ,temp, humi);

                sprintf(param, "%d",temp);
                sprintf(param1, "%d",humi);

                sprintf(param2, "{/'T/':%d,/'H/':%d}",temp,humi);

                ssdmet(hstr, mstr, param,param1);

                paho_mqtt_publish(&client, QOS1, "/toYun",param2);


            }
        }

       // paho_mqtt_subscribe(&client, QOS1, "/toYun", param2);
}


static int dht11_read_temp_sample(void)
{
    time_t now;
    struct tm *p;
    int min = 0, hour = 0;
    now = time(RT_NULL);


    if (now)
    {
       // rt_kprintf("Cur Time: %s", ctime((const time_t*) &cur_time));

        //ssd130611(ctime((const time_t*) &cur_time));


            p=gmtime((const time_t*) &now);
            hour = p->tm_hour;
            min = p->tm_min;


        sprintf(mstr, "%02d", min);
        sprintf(hstr, "%02d", hour);

          // ssdmet(hstr, mstr, "20", "30");


    }
    else
    {
        rt_kprintf("NTP sync fail.\n");
    }

    rt_thread_t dht11_thread;

    dht11_thread = rt_thread_create("dht_tem",
                                     read_temp_entry,
                                     RT_NULL,
                                     1024,
                                     RT_THREAD_PRIORITY_MAX / 2,
                                     20);
    if (dht11_thread != RT_NULL)
    {
        rt_thread_startup(dht11_thread);
    }

    return RT_EOK;
}
MSH_CMD_EXPORT(dht11_read_temp_sample,aa);


static int rt_hw_dht11_port(void)
{
    struct rt_sensor_config cfg;
    
    cfg.intf.user_data = (void *)DHT11_DATA_PIN;
    rt_hw_dht11_init("dht11", &cfg);

    return RT_EOK;
}
INIT_COMPONENT_EXPORT(rt_hw_dht11_port);
