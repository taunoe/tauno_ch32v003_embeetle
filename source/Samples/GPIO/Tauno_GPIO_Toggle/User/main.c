/********************************** (C) COPYRIGHT *******************************
 * File Name          : main.c
 * Date               : 15.07.2024
 * Description        : GPIO Input/Output
*********************************************************************************/

#include "debug.h"

/* Global define */
#define HIGH 1
#define LOW  0

#define PC0  0
#define PC1  1
#define PC2  2
#define PC3  3
#define PC4  4
#define PC5  5
#define PC6  6
#define PC7  7
#define PD0  8
#define PD1  9
#define PD2 10
#define PD3 11
#define PD4 12
#define PD5 13
#define PD6 14
#define PD7 15  // RST
#define PA1 16  // X1
#define PA2 17  // X0

/* Global Variable */

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

/*********************************************************************
 * @fn      GPIO_Toggle_INIT
 *
 * @brief   Initializes GPIO
 *
 * @return  none
 */
void tauno_GPIO_init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure = {0}; // Variable used for the GPIO configuration

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);  // Enable the clock for Port
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0; // pin
    
    // There are two different output modes:
    //   - Open drain output ( GPIO_Mode_Out_OD ) and
    //   - push pull output (GPIO_Mode_Out_PP).
    // There are four different input modes:
    //   - Floating input (GPIO_Mode_IN_FLOATING),
    //   - pull-up input (GPIO_Mode_IPU),
    //   - pull-down input (GPIO_Mode_IPD) and
    //   - analog input (GPIO_Mode_AIN).
    // The GPIO can also be configured as "alternate function".
    // used for a specific hardware function like for example
    // pulse width modulation (PWM) or serial peripheral interface (SPI).
    // The modes for alternate functions can be
    //   - open drain (GPIO_Mode_AF_OD) or
    //   - push-pull (GPIO_Mode_AF_PP).
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;

    // There are three speed options:
    // GPIO_Speed_2MHz
    // GPIO_Speed_10MHz
    // GPIO_Speed_50MHz
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    
    GPIO_Init(GPIOD, &GPIO_InitStructure);  //
}

/*********************************************************************
 * @fn      main
 *
 * @brief   Main program.
 *
 * @return  none
 */
int main(void) {
  u8 status = 0;

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
  
  tauno_GPIO_init();

  while(1) {
    Delay_Ms(250);
    
    if (status == LOW) {
      status = HIGH;
      printf("1\r\n");
    } else {
      status = LOW;
      printf("0\r\n");
    }

    GPIO_WriteBit(GPIOD, GPIO_Pin_0, status);
  }
}
