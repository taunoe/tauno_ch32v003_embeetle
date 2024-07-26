/********************************** (C) COPYRIGHT *******************************
 * File Name          : tauno_gpio.c
 * Author             : Tauno Erik
 * Version            : V1.0.0
 * Date               : 16.07.2024
 * Description        : This file contains the GPIO functions
*******************************************************************************/
#include "tauno_gpio.h"


/*********************************************************************
 * @fn      tauno_PIN_init
 *
 * @brief   Initalize GPIO to input or output
 *
 * @param   pin - GPIO name
 *
 * @param   mode - INPUT ot OUTPUT
 *
 * @return  None
 */
void tauno_PIN_init(u8 pin, u8 mode)
{
  GPIO_InitTypeDef GPIO_InitStructure = {0}; // Variable used for the GPIO configuration
  
  switch (pin)
  {
    case PA1:  // X0
      RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);  // Enable the clock for Port
      GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1; // pin
      break;
    case PA2:  // X1
      RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);  // Enable the clock for Port
      GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2; // pin
      break;
    case PC0:
      RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);  // Enable the clock for Port
      GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0; // pin
      break;
    case PC1:
      RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);  // Enable the clock for Port
      GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1; // pin
      break;
    case PC2:
      RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);  // Enable the clock for Port
      GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2; // pin
      break;
    case PC3:
      RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);  // Enable the clock for Port
      GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3; // pin
      break;
    case PC4:
      RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);  // Enable the clock for Port
      GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4; // pin
      break;
    case PC5:
      RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);  // Enable the clock for Port
      GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5; // pin
      break;
    case PC6:
      RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);  // Enable the clock for Port
      GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6; // pin
      break;
    case PC7:
      RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);  // Enable the clock for Port
      GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7; // pin
      break;
    case PD0:
      RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);  // Enable the clock for Port
      GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0; // pin
      break;
    case PD1:
      RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);  // Enable the clock for Port
      GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1; // pin
      break;
    case PD2:
      RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);  // Enable the clock for Port
      GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2; // pin
      break;
    case PD3:
      RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);  // Enable the clock for Port
      GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3; // pin
      break;
    case PD4:
      RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);  // Enable the clock for Port
      GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4; // pin
      break;
    case PD5:
      RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);  // Enable the clock for Port
      GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5; // pin
      break;
    case PD6:
      RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);  // Enable the clock for Port
      GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6; // pin
      break;
    case PD7:  // RST
      RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);  // Enable the clock for Port
      GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7; // pin
      break;
    default:
      break;
  }
  
  if (mode == OUTPUT)
  {
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  // Push-pull output
  } 
  else
  {
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;  // Pull-up input
  }

  // Speed
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

  switch (pin)
  {
    case PA1:  // X0 pin
    case PA2:  // X1 pin
      GPIO_Init(GPIOA, &GPIO_InitStructure);
      break;
    case PC0:
    case PC1:
    case PC2:
    case PC3:
    case PC4:
    case PC5:
    case PC6:
    case PC7:
      GPIO_Init(GPIOC, &GPIO_InitStructure);
      break;
    case PD0:
    case PD1:
    case PD2:
    case PD3:
    case PD4:
    case PD5:
    case PD6:
    case PD7:  // RST pin
      GPIO_Init(GPIOD, &GPIO_InitStructure);
      break;
    default:
      break;
  }
}


/*********************************************************************
 * @fn      tauno_PIN_write
 *
 * @brief   Set Pin High or Low
 *
 * @param   pin - GPIO name
 *
 * @param   value - HIGH (1) or LOW (0)
 *
 * @return  None
 */
void tauno_PIN_write(u8 pin, u8 value)
{
  switch (pin)
  {
    case PC0:
      GPIO_WriteBit(GPIOC, GPIO_Pin_0, value);
      break;
    case PC1:
      GPIO_WriteBit(GPIOC, GPIO_Pin_1, value);
      break;
    case PC2:
      GPIO_WriteBit(GPIOC, GPIO_Pin_2, value);
      break;
    case PC3:
      GPIO_WriteBit(GPIOC, GPIO_Pin_3, value);
      break;
    case PC4:
      GPIO_WriteBit(GPIOC, GPIO_Pin_4, value);
      break;
    case PC5:
      GPIO_WriteBit(GPIOC, GPIO_Pin_5, value);
      break;
    case PC6:
      GPIO_WriteBit(GPIOC, GPIO_Pin_6, value);
      break;
    case PC7:
      GPIO_WriteBit(GPIOC, GPIO_Pin_7, value);
      break;
    case PD0:
      GPIO_WriteBit(GPIOD, GPIO_Pin_0, value);
      break;
    case PD1:
      GPIO_WriteBit(GPIOD, GPIO_Pin_1, value);
      break;
    case PD2:
      GPIO_WriteBit(GPIOD, GPIO_Pin_2, value);
      break;
    case PD3:
      GPIO_WriteBit(GPIOD, GPIO_Pin_3, value);
      break;
    case PD4:
      GPIO_WriteBit(GPIOD, GPIO_Pin_4, value);
      break;
    case PD5:
      GPIO_WriteBit(GPIOD, GPIO_Pin_5, value);
      break;
    case PD6:
      GPIO_WriteBit(GPIOD, GPIO_Pin_6, value);
      break;
    case PD7:  // RST pin
      GPIO_WriteBit(GPIOD, GPIO_Pin_7, value);
      break;
    case PA1:  // External crystal
      GPIO_WriteBit(GPIOA, GPIO_Pin_1, value);
      break;
    case PA2:  // External crystal
      GPIO_WriteBit(GPIOA, GPIO_Pin_2, value);
      break;
    default:
      break;
  }
}


/*********************************************************************
 * @fn      tauno_PIN_read
 *
 * @brief   Read Pin status: High or Low
 *
 * @param   pin - GPIO name
 *
 * @return  HIGH (1) or LOW (0)
 */
u8 tauno_PIN_read(u8 pin)
{
  u8 val = LOW;
  
  switch (pin)
  {
    case PA1:  // X0
      val = GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_1);
      break;
    case PA2:  // X1
      val = GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_2);
      break;
    case PC0:
      val = GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_0);
      break;
    case PC1:
      val = GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_1);
      break;
    case PC2:
      val = GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_2);
      break;
    case PC3:
      val = GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_3);
      break;
    case PC4:
      val = GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_4);
      break;
    case PC5:
      val = GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_5);
      break;
    case PC6:
      val = GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_6);
      break;
    case PC7:
      val = GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_7);
      break;
    case PD0:
      val = GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_0);
      break;
    case PD1:
      val = GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_1);
      break;
    case PD2:
      val = GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_2);
      break;
    case PD3:
      val = GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_3);
      break;
    case PD4:
      val = GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_4);
      break;
    case PD5:
      val = GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_5);
      break;
    case PD6:
      val = GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_6);
      break;
    case PD7:  // RST
      val = GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_7);
      break;
    default:
      break;
  }
  
  return val;
}

/*********************************************************************
 * @fn      tauno_PIN_PWM
 *
 * @brief   
 *
 * @param   pin - GPIO name
 *
 * @return  None
 */
void tauno_PIN_PWM(u8 pin) {
  
}