/********************************** (C) COPYRIGHT *******************************
 * File Name          : main.c
 * Date               : 16.07.2024
 * Autor              : Tauno Erik
 * Description        : PWM
*********************************************************************************/

#include "main.h"

/* PWM Output Mode Selection */
//#define PWM_MODE PWM_MODE_1
#define PWM_MODE PWM_MODE_2


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
  
  tauno_PIN_init(PD0, OUTPUT);
  tauno_PIN_init(PC3, INPUT);

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
