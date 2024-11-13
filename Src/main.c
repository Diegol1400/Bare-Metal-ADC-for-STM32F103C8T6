#include <stdio.h>
#include "stm32f103xb.h"
#include "adc.h"

#include <stdint.h>
#include "uart.h"

#define GPIOCEN 			(1U<<4)  //0000 0000 0000 0000 0000 0000 0001 0000 Máscara para habilitar el reloj de GPIOC (Bit 4 en el registro RCC)

#define PIN_13				(1U<<13) // Máscara para el pin 13 de GPIOC (Bit 13)
#define LED_PIN				PIN_13


uint32_t sensor_value;

int main(void){

	//Habilitar el reloj para GPIOC

	RCC->APB2ENR |= GPIOCEN;

	// Configurar el pin 13 de GPIOC como salida (modo general de salida)

	GPIOC->CRH   |= (1U<<21);


	//pa1_adc_init();
	//start_converstion();

	while(1){

		pa1_adc_init();
		start_converstion();
		sensor_value = adc_read();

		if (sensor_value > 2000) {
			GPIOC->ODR &=~ LED_PIN;
		}else {
			GPIOC->ODR |= LED_PIN;
		}

	}
}

