/********************************** (C) COPYRIGHT *******************************
 * File Name          : tauno_id.c
 * Author             : Tauno Erik
 * Version            : V1.0.0
 * Date               : 16.07.2024
 * Description        : This file contains the MCU id functions
*******************************************************************************/

#include "tauno_id.h"

/*********************************************************************
 * @fn      get_chip_type
 *
 * @brief   Returns the CHIP identifier.
 *
 * @return Device identifier.
 *    ChipID List-
 *      CH32V003F4P6-0x003005x0
 *      CH32V003F4U6-0x003105x0
 *      CH32V003A4M6-0x003205x0
 *      J4M6-0x003305x0
 */
uint32_t get_chip_type(void)
{
  return( *( uint32_t * )0x1FFFF7C4 );
}

uint16_t get_MCU_flash_size(void)
{
  return( *( uint16_t * )0x1FFFF7E0 );
}

uint32_t get_MCU_uid_1(void)
{
  return( *( uint32_t * )0x1FFFF7E8 );
}

uint32_t get_MCU_uid_2(void)
{
  return( *( uint32_t * )0x1FFFF7EC );
}

uint32_t get_MCU_uid_3(void)
{
    return( *( uint32_t * )0x1FFFF7F0 );
}
