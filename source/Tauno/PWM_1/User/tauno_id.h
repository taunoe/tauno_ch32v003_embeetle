/********************************** (C) COPYRIGHT *******************************
 * File Name          : tauno_id.h
 * Author             : Tauno Erik
 * Version            : V1.0.0
 * Date               : 16.07.2024
 * Description        : This file contains the headers of the MCU id functions
*******************************************************************************/

#ifndef TAUNO_ID_H
#define TAUNO_ID_H

#include <ch32v00x.h>
#include <stdio.h>

uint32_t get_chip_type(void);
uint16_t get_MCU_flash_size(void);
uint32_t get_MCU_uid_1(void);
uint32_t get_MCU_uid_2(void);
uint32_t get_MCU_uid_3(void);

#endif /* TAUNO_ID_H */