/********************************** (C) COPYRIGHT *******************************
 * File Name          : main.c
 * Date               : 15.07.2024
 * Autor              : Tauno Erik
 * Description        : GPIO Input/Output
*********************************************************************************/

#include "debug.h"

/* Global define */
#define HIGH   1
#define LOW    0

#define INPUT  0
#define OUTPUT 1

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
uint32_t get_chip_type( void )
{
  return( *( uint32_t * )0x1FFFF7C4 );
}

uint16_t get_MCU_flash_size( void )
{
  return( *( uint16_t * )0x1FFFF7E0 );
}

uint32_t get_MCU_uid_1( void )
{
  return( *( uint32_t * )0x1FFFF7E8 );
}

uint32_t get_MCU_uid_2( void )
{
  return( *( uint32_t * )0x1FFFF7EC );
}

uint32_t get_MCU_uid_3( void )
{
    return( *( uint32_t * )0x1FFFF7F0 );
}

/*****************************************************************************************
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

/*****************************************************************************************
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

/*****************************************************************************************
*/
void tauno_pin_init(u8 pin, u8 mode)
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
    case PA1:  // X0
    case PA2:  // X1
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
    case PD7:  // RST
      GPIO_Init(GPIOD, &GPIO_InitStructure);
      break;
    default:
      break;
  }
}

/*****************************************************************************************
*/
int main(void) {
  u8 write_status = LOW;
  u8 read_status = LOW;

  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
  Delay_Init();
  USART_Printf_Init(115200);
  Delay_Ms(3000);  // Give serial monitor time to open

  printf("Flash size: \t%d\r\n", (unsigned)get_MCU_flash_size);
  printf("SystemClk: \t%d\r\n", (unsigned)SystemCoreClock);
  printf("Device ID: \t%08x\r\n", (unsigned)DBGMCU_GetDEVID());
  printf("Revision ID: \t%08x\r\n", (unsigned)DBGMCU_GetREVID());
  printf("Chip type: \t%08x\r\n", (unsigned)get_chip_type());
  printf("UID 1: \t\t%d\r\n", (unsigned)get_MCU_uid_1);
  printf("UID 2: \t\t%d\r\n", (unsigned)get_MCU_uid_2);
  printf("UID 3: \t\t%d\r\n", (unsigned)get_MCU_uid_3);

  printf("GPIO Toggle\r\n");
  
  tauno_pin_init(PD0, OUTPUT);
  tauno_pin_init(PC3, INPUT);

  while(1)
  {
    Delay_Ms(100);
    read_status = tauno_PIN_read(PC3);
    
    if (read_status == LOW)  // Button bressed
    {
      write_status = HIGH;
      // printf("1\r\n");
      printf("BUTTON\r\n");
    }
    else
    {
      write_status = LOW;
      // printf("0\r\n");
    }

    tauno_PIN_write(PD0, write_status);
  }
}
