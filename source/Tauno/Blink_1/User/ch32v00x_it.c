/********************************** (C) COPYRIGHT *******************************
 * File Name          : ch32v00x_it.c
 * Author             : WCH
 * Version            : V1.0.0
 * Date               : 2022/08/08
 * Description        : Main Interrupt Service Routines.
*********************************************************************************
* Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
* Attention: This software (modified or not) and binary are used for 
* microcontroller manufactured by Nanjing Qinheng Microelectronics.
*******************************************************************************/
#include <ch32v00x_it.h>

void NMI_Handler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
void HardFault_Handler(void) __attribute__((interrupt("WCH-Interrupt-fast")));

/*********************************************************************
 * @fn      NMI_Handler
 *
 * @brief   This function handles NMI exception.
 *
 * @return  none
 */
 /**
 * @brief Handler for non-maskable interrupts (nmi)
 * 
 * Non-maskable interrupts (nmi) are interrupts that the mcu cannot ignore and that 
 * need to be attended to immediately. In our mini blinky example, the nmi
 * handler will just do nothing. Who really cares if we crash and burn.
 */
void NMI_Handler(void)
{
}

/*********************************************************************
 * @fn      HardFault_Handler
 *
 * @brief   This function handles Hard Fault exception.
 *
 * @return  none
 */
/**
 * @brief Fault handler
 * 
 * Faults are errors that occure during runtime. An example would be a NULL
 * pointer derefference. This handler for our blinky example will just enter
 * and infinite loop, effectively thorwing the system to non action in ever
 * lasting limbo.
 */
void HardFault_Handler(void)
{
  while (1)
  {
  }
}


