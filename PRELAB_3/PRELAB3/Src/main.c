/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Auto-generated by STM32CubeIDE
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2022 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */

#include <stdint.h>

uint32_t wait_millisecond = 1000;
uint32_t wait_counter = 0;

#define RCC_AHB2EN  *((uint32_t*)( 0X40021000 + 0x04C))
#define GPIOA_MODER *((uint32_t*)( 0x42020000 + 0x00))
#define GPIOA_OUT 	*((uint32_t*)( 0x42020000 + 0x14 ))


int main(void) {

	RCC_AHB2EN |= 0x01;
	GPIOA_MODER &= ~(0x01 << 19);



	while(1) {
		volatile int index;

		GPIOA_OUT |= (0x01 << 9);

		for(index=0;index<wait_millisecond*333;index++);
		wait_counter = wait_counter + 1;

		GPIOA_OUT &= ~(0x01 << 9);

		for(index=0;index<wait_millisecond*333;index++);
		wait_counter = wait_counter + 1;
	}
}
