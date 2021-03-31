#ifndef _MYPI_H_
#define _MYPI_H_

#ifndef _MYPI_C_
#endif

#include <rtthread.h>
#include <rtdevice.h>
#include "drv_common.h"

//LED
#define LED1  GET_PIN(I, 8)
#define LED2 GET_PIN(G, 11)
#define LED3 GET_PIN(G, 13)
#define LED4 GET_PIN(H, 2)
#define LED5 GET_PIN(H, 3)

//KA
#define KA1  GET_PIN(B, 12)
#define KA2  GET_PIN(B, 13)

//KEY
#define LINE1  GET_PIN(H, 8)
#define LINE2  GET_PIN(H, 9)
#define ROW1   GET_PIN(H, 10)
#define ROW2   GET_PIN(H, 13)
#define ROW3   GET_PIN(H, 14)
#define ROW4   GET_PIN(H, 15)

//MOTO
#define S1  GET_PIN(A, 6)
#define S2  GET_PIN(A, 7)
#define S3  GET_PIN(A, 8)
#define S4  GET_PIN(A, 9)
#define S5  GET_PIN(A, 10)
#define S6  GET_PIN(A, 11)
#define S7  GET_PIN(A, 12)

/*                  7P OLED
#define OLED_SPI_PIN_CLK                     GET_PIN(I, 1)
#define OLED_SPI_PIN_MOSI                    GET_PIN(I, 3)
#define OLED_SPI_PIN_RES                     GET_PIN(D, 13)
#define OLED_SPI_PIN_DC                      GET_PIN(H, 7)
#define OLED_SPI_PIN_CS                      GET_PIN(I, 0)*/

//TEMPERATURE
#define TEMP     GET_PIN(I, 5)

//USART
#define USARTR   GET_PIN(H, 13)
#define USARTT   GET_PIN(H, 14)

//IIC
#define SCL   GET_PIN(H, 11)
#define SDA   GET_PIN(H, 12)

//433M
#define OUT   GET_PIN(C, 6)
#define IN    GET_PIN(C, 7)

/*ADC
#define ADC1   GET_PIN(C, 6)
#define ADC2   GET_PIN(C, 7)
#define ADC3   GET_PIN(C, 7)
#define ADC4   GET_PIN(C, 7)*/

//SPI
#define SCK    GET_PIN(E, 2)
#define MISO   GET_PIN(E, 5)
#define MOSI   GET_PIN(E, 6)
#define NSS    GET_PIN(E, 4)


#define PA1   GET_PIN(A, 1)
#define PA2   GET_PIN(A, 2)
#define PA3   GET_PIN(A, 3)

#define PB0   GET_PIN(B, 0)
#define PB1   GET_PIN(B, 1)
#define PB2   GET_PIN(B, 2)

#define PC1   GET_PIN(C, 1)
#define PC4   GET_PIN(C, 4)
#define PC5   GET_PIN(C, 5)


/*
                      7P OLED
#define OLED_SPI_PIN_CLK                     GET_PIN(I, 1)
#define OLED_SPI_PIN_MOSI                    GET_PIN(I, 3)
#define OLED_SPI_PIN_RES                     GET_PIN(D, 13)
#define OLED_SPI_PIN_DC                      GET_PIN(H, 7)
#define OLED_SPI_PIN_CS                      GET_PIN(I, 0)

 */

void piledinit();

void pikainit();

int pireadkey();

void pimotoinit(int s);

#endif
