/********************************** (C) COPYRIGHT *******************************
 * File Name          : tauno_gpio.h
 * Author             : Tauno Erik
 * Version            : V1.0.0
 * Date               : 16.07.2024
 * Description        : This file contains the headers of the GPIO functions
*******************************************************************************/
#ifndef TAUNO_GPIO_H
#define TAUNO_GPIO_H

#include <ch32v00x.h>
#include <stdio.h>

#define HIGH   1
#define LOW    0

#define INPUT  0
#define OUTPUT 1

// GPIO Pins names
#define PC0    0
#define PC1    1
#define PC2    2
#define PC3    3
#define PC4    4
#define PC5    5
#define PC6    6
#define PC7    7
#define PD0    8
#define PD1    9
#define PD2   10
#define PD3   11
#define PD4   12
#define PD5   13
#define PD6   14
#define PD7   15  // RST
#define PA1   16  // X1
#define PA2   17  // X0

// PWM Output Mode Definition
#define PWM_MODE_1   0
#define PWM_MODE_2   1

/**************************************************************************************/
void tauno_PIN_init(u8 pin, u8 mode);
void tauno_PIN_write(u8 pin, u8 value);
u8 tauno_PIN_read(u8 pin);

void tauno_PIN_PWM(u8 pin);

#endif /* TAUNO_GPIO_H */