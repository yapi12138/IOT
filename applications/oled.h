#ifndef _OLED_H_
#define _OLED_H_

#ifndef _OLED_C_
#endif

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>
#include <u8g2_port.h>


#define OLED_SPI_PIN_CLK                     GET_PIN(I, 1)
#define OLED_SPI_PIN_MOSI                    GET_PIN(I, 3)
#define OLED_SPI_PIN_RES                     GET_PIN(D, 13)
#define OLED_SPI_PIN_DC                      GET_PIN(H, 7)
#define OLED_SPI_PIN_CS                      GET_PIN(I, 0)

void ssdinit();
void ssdwifilink();
void ssdwifiok();
void ssdmqttlink();
void ssdmqttok();
void ssdwifiun();
void ssdme(char me[]);
void ssdme2(char me[],char me1[]);
void ssdme22(char me[],char me1[]);
void ssdmet(char me[],char me1[],char me2[],char me3[]);
void ssd130611(char ab[]);
#endif
