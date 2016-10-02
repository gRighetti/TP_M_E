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
#include "bsp\bsp.h"

void APP_GetData(uint8_t dato);

uint8_t txBuffer[200];
uint8_t rxDato;
uint8_t Estado;
uint8_t Error = 0;
uint8_t tx = 0;
uint8_t bloqueo = 1;
uint16_t Pote;
int size;

enum {
	MENU_INT = 0, MENU_ADC = 1, MENU_LED = 2, MENU_SW = 3,

};

int main(void) {

	BSP_Init();

	BSP_LED_Init(LED3);
	BSP_LED_Init(LED4);
	BSP_LED_Init(LED5);
	BSP_LED_Init(LED6);
	Estado = MENU_INT;

	while (1) {

		switch (Estado) {
		case MENU_INT:
			if (bloqueo) {
				bloqueo = 0;
				size =
						sprintf(txBuffer,
								"Menu inicial: \r\n 1 Obtener valor ADC \r\n 2 Leds \r\n3 Estado SW\r\n ");
				TransmitData(txBuffer, size);
			}
			if (tx) {
				tx = 0;
				if (Error) {
					Error = 0;
					size = sprintf(txBuffer, "Error:Opcion Incorrecta\r\n");
					TransmitData(txBuffer, size);
					bloqueo = 1;

				} else {
					if (rxDato == '0') {
						bloqueo = 1;
					}
					if (rxDato == '1') {
						bloqueo = 1;
						Estado = MENU_ADC;
					}
					if (rxDato == '2') {
						bloqueo = 1;
						Estado = MENU_LED;

					}
					if (rxDato == '3') {
						bloqueo = 1;
						Estado = MENU_SW;

					}

				}

			}
			break;
		case MENU_ADC:
			if (bloqueo) {
				bloqueo = 0;
				size =
						sprintf(txBuffer,
								"Menu ADC: \r\n 1 ADC binario \r\n 2 ADC decimal \r\n 3 ADC volt \r\n 0 Menu_Inicial\r\n");
				TransmitData(txBuffer, size);
			}
			if (tx) {
				tx = 0;
				if (Error) {
					Error = 0;
					size = sprintf(txBuffer, " Error:Opcion Incorrecta \r\n");
					TransmitData(txBuffer, size);
					bloqueo = 1;

				} else {
					if (rxDato == '0') {
						bloqueo = 1;
						Estado = MENU_INT;
					}
					if (rxDato == '1') {
						bloqueo = 1;
						Pote = BSP_ADC_GetValue();
						size = sprintf(txBuffer, "ADC Binario:");
						TransmitData(txBuffer, size);
						get_Binario(Pote);

					}
					if (rxDato == '2') {
						bloqueo = 1;
						Pote = BSP_ADC_GetValue();
						size = sprintf(txBuffer, "ADC Decimal:%d \r\n",(int)Pote);
						TransmitData(txBuffer, size);

					}
					if (rxDato == '3') {
						bloqueo = 1;
						Pote = BSP_ADC_GetValue();
						get_Voltio(Pote);

					}

				}

			}

			break;
		case MENU_LED:
			if (bloqueo) {
				bloqueo = 0;
				size =
						sprintf(txBuffer,
								"Menu LED: \r\n 1 Toggle led Naranja \r\n 2 Toggle led Amarillo \r\n 3 Toggle led Rojo \r\n 4 Toggle led Azul \r\n 0 Menu_Inicial\r\n");
				TransmitData(txBuffer, size);
			}
			if (tx) {
				tx = 0;
				if (Error) {
					Error = 0;
					size = sprintf(txBuffer, "Error:Opcion Incorrecta \r\n");
					TransmitData(txBuffer, size);
					bloqueo = 1;

				} else {
					if (rxDato == '0') {
						bloqueo = 1;
						Estado = MENU_INT;
					}
					if (rxDato == '1') {
						bloqueo = 1;
						size = sprintf(txBuffer, "Toggle Led Naranja: \r\n");
						TransmitData(txBuffer, size);
						BSP_LED_Toggle(LED3);

					}
					if (rxDato == '2') {
						bloqueo = 1;
						size = sprintf(txBuffer, "Toggle Led Amarillo: \r\n");
						TransmitData(txBuffer, size);
						BSP_LED_Toggle(LED4);

					}
					if (rxDato == '3') {
						bloqueo = 1;
						size = sprintf(txBuffer, "Toggle Led Rojo: \r\n");
						TransmitData(txBuffer, size);
						BSP_LED_Toggle(LED5);

					}
					if (rxDato == '4') {
						bloqueo = 1;
						size = sprintf(txBuffer, "Toggle Led Azul: \r\n");
						TransmitData(txBuffer, size);
						BSP_LED_Toggle(LED6);

					}

				}

			}

			break;
		case MENU_SW:
			if (bloqueo) {
				bloqueo = 0;
				size =
						sprintf(txBuffer,
								"Menu SW: \r\n 1 Estado SW_UP \r\n 2 Estado SW_DOWM \r\n 3 Estado SW_LEFT \r\n 4 Estado SW_RIGHT \r\n 0 Menu_Inicial\r\n");
				TransmitData(txBuffer, size);
			}
			if (tx) {
				tx = 0;
				if (Error) {
					Error = 0;
					size = sprintf(txBuffer, "Error:Opcion Incorrecta \r\n");
					TransmitData(txBuffer, size);
					bloqueo = 1;

				} else {
					if (rxDato == '0') {
						bloqueo = 1;
						Estado = MENU_INT;
					}
					if (rxDato == '1') {
						bloqueo = 1;
						uint32_t Swicht = BSP_SW_GetState(SW_UP);
						if (Swicht) {
							size = sprintf(txBuffer,
									"ESTADO SW_UP: Suelto \r\n");
						} else {
							size = sprintf(txBuffer,
									"ESTADO SW_UP: Apretado \r\n");
						}
						TransmitData(txBuffer, size);
					}
					if (rxDato == '2') {
						bloqueo = 1;
						uint32_t Swicht = BSP_SW_GetState(SW_DOWN);
						if (Swicht) {
							size = sprintf(txBuffer,
									"ESTADO SW_DOWN: Suelto \r\n");
						} else {
							size = sprintf(txBuffer,
									"ESTADO SW_DOWN: Apretado \r\n");
						}
						TransmitData(txBuffer, size);
					}
					if (rxDato == '3') {
						bloqueo = 1;
						uint32_t Swicht = BSP_SW_GetState(SW_LEFT);
						if (Swicht) {
							size = sprintf(txBuffer,
									"ESTADO SW_LEFT: Suelto \r\n");
						} else {
							size = sprintf(txBuffer,
									"ESTADO SW_LEFT: Apretado \r\n");
						}
						TransmitData(txBuffer, size);
					}
					if (rxDato == '4') {
						bloqueo = 1;
						uint32_t Swicht = BSP_SW_GetState(SW_RIGHT);
						if (Swicht) {
							size = sprintf(txBuffer,
									"ESTADO SW_RIGHT: Suelto \r\n");
						} else {
							size = sprintf(txBuffer,
									"ESTADO SW_RIGHT: Apretado \r\n");
						}
						TransmitData(txBuffer, size);
					}
				}
			}

			break;
		default:
			break;
		}
	}
}

void APP_GetData(uint8_t dato) {
	tx = 1;
	if (dato >= '0' && dato <= '4') {
		rxDato = dato;
	} else {
		Error = 1;
	}

}
void APP_1ms() {
}

void get_Binario(uint16_t Potenciometro) {
	uint16_t comp = 4096;
	for (int i = 12; i > 0; i--) {
		if (Potenciometro & comp) {
			size = sprintf(txBuffer, "1");
			TransmitData(txBuffer, size);

		} else {
			size = sprintf(txBuffer, "0");
			TransmitData(txBuffer, size);

		}
		comp /= 2;
	}
	size = sprintf(txBuffer, "\r\n");
	TransmitData(txBuffer, size);

}

void get_Voltio(uint16_t Potenciometro){
	Potenciometro=(Potenciometro*3300)/4095;
	uint16_t decimal=Potenciometro%1000;
	uint16_t entera=Potenciometro/1000;
	size = sprintf(txBuffer, "Voltios: %d.%02d \r\n",entera,decimal);
		TransmitData(txBuffer, size);


}

