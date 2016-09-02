/**
  ******************************************************************************
  * @file    main.c
  * @author  Ac6
  * @version V1.0
  * @date    01-December-2013
  * @brief   Default main function.
  ******************************************************************************
*/

#include "stm32f4_discovery.h"
#include "bsp/bsp.h"

void APP_GetData(uint8_t dato);

int main(void)
{

	BSP_Init();

	BSP_LED_Init(LED3);
	BSP_LED_Init(LED4);
	BSP_LED_Init(LED5);
	BSP_LED_Init(LED6);

	while(1){

	}
}

void APP_GetData(uint8_t dato){

}
