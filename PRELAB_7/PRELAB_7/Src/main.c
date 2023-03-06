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


typedef struct {
	volatile uint32_t MODER;
	volatile uint32_t OTYPER;
	volatile uint32_t OSPEEDR;
	volatile uint32_t PUPDR;
	volatile uint32_t IDR;
	volatile uint32_t ODR;
	volatile uint32_t BSRR;
	volatile uint32_t LCKR;
	volatile uint32_t AFR;
	volatile uint32_t BRR;
	uint32_t RESERVED;
	volatile uint32_t SECCFGR;
} GPIO_TypeDef;

typedef struct
{
  volatile uint32_t CR1;
  volatile uint32_t CR2;
  volatile uint32_t SMCR;
  volatile uint32_t DIER;
  volatile uint32_t SR;
  volatile uint32_t EGR;
  volatile uint32_t CCMR1;
  volatile uint32_t CCMR2;
  volatile uint32_t CCER;
  volatile uint32_t CNT;
  volatile uint32_t PSC;
  volatile uint32_t ARR;
  volatile uint32_t RCR;
  volatile uint32_t CCR1;
  volatile uint32_t CCR2;
  volatile uint32_t CCR3;
  volatile uint32_t CCR4;
  volatile uint32_t BDTR;
  volatile uint32_t DCR;
  volatile uint32_t DMAR;
  volatile uint32_t OR1;
  volatile uint32_t CCMR3;
  volatile uint32_t CCR5;
  volatile uint32_t CCR6;
  volatile uint32_t OR2;
  volatile uint32_t OR3;
} TIM_TypeDef;

#define TIM4  ((TIM_TypeDef *) 0x40000800)
#define TIM5  ((TIM_TypeDef *) 0x40000C00)
#define TIM6  ((TIM_TypeDef *) 0x40001000)
#define TIM7  ((TIM_TypeDef *) 0x40001400)

#define NVIC_ISER1  *((volatile uint32_t *) 0xE000E104)

#define NVIC_ICER1  *((volatile uint32_t *) 0xE000E184)

#define GPIOD ((GPIO_TypeDef *) 0x42020C00)

#define RCC_AHB2ENR   *((volatile uint32_t *) 0x4002104C)
#define RCC_APB1ENR   *((volatile uint32_t *) 0x40021058)

void TIM4_IRQHandler(void){
	TIM4->SR &= ~(0X01);

	static int cnt = 0;

	if(cnt %2 == 0){

		GPIOD->ODR |= (0X01); // KIRMIZI SÖNDÜR

	}else{

		GPIOD->ODR &= ~(0X01); // KIRMIZ YAK
	}
	cnt++;

}

void TIM5_IRQHandler(void){
	TIM5->SR &= ~(0X01);

	static int cnt1 = 0;

	if(cnt1 %2 == 0){

		GPIOD->ODR |= (0X01<<1); // YESIL SÖNDÜR
	}else{

		GPIOD->ODR &= ~(0X01<<1); // YESİL YAK
	}
	cnt1++;
}

void TIM6_IRQHandler(void){

	TIM6->SR &= ~(0X01);
	static int cnt2 = 0;

	if(cnt2 %2 == 0){

		GPIOD->ODR |= (0X01<<2); // MAVİ SÖNDÜR

	}else{

		GPIOD->ODR &= ~(0X01<<2); // MAVİ YAK
	}
	cnt2++;
}

void TIM7_IRQHandler(void){
	TIM7->SR &= ~(0X01);

	static int cnt3 = 0;

	if(cnt3%8==0){  // kırmızı, mavi, yeşil yanık
		TIM4->CR1 |= (0X01);
		GPIOD->ODR &= ~(0X01);

		TIM5->CR1 |= (0X01);
		GPIOD->ODR &= ~(0X01<<1);

		TIM6->CR1 |= (0X01);
		GPIOD->ODR &= ~(0X01<<2);


	}else if(cnt3%8==1){ // kırmızı sönük. mavi yeşil yanık

		TIM4->CR1 &= ~(0X01); // TIM4 COUNTER KAPALI
		GPIOD->ODR |= (0X01); // KIRMIZI SÖNÜK

		TIM5->CR1 |= (0X01);
		GPIOD->ODR &= ~(0X01<<1);

		TIM6->CR1 |= (0X01);
		GPIOD->ODR &= ~(0X01<<2);


	}else if(cnt3%8==2){ // kızmırı mavi yanık. yeşil sönük

		TIM4->CR1 |= (0X01); // TIM4 COUNTER KAPALI
		GPIOD->ODR &= ~(0X01); // KIRMIZI SÖNÜK

		TIM5->CR1 &= ~(0X01);
		GPIOD->ODR |= (0X01<<1);

		TIM6->CR1 |= (0X01);
		GPIOD->ODR &= ~(0X01<<2);


	}else if(cnt3%8==3){ // mavi yanık. yeşil kırmızı


		TIM4->CR1 &= ~(0X01); // TIM4 COUNTER KAPALI
		GPIOD->ODR |= (0X01); // KIRMIZI SÖNÜK

		TIM5->CR1 &= ~(0X01);
		GPIOD->ODR |= (0X01<<1);


		TIM6->CR1 |= (0X01);
		GPIOD->ODR &= ~(0X01<<2);

	}else if(cnt3%8==4){ // kırmızı yeşil yanık. mavi sönük

		TIM4->CR1 |= (0X01); // TIM4 COUNTER KAPALI
		GPIOD->ODR &= ~(0X01); // KIRMIZI SÖNÜK


		TIM5->CR1 |= (0X01);
		GPIOD->ODR &= ~(0X01<<1);

		TIM6->CR1 &= ~(0X01);
		GPIOD->ODR |= (0X01<<2);



	}else if(cnt3%8==5){ // yeşi yanık. kırmızı mavi sönük

		TIM4->CR1 &= ~(0X01); // TIM4 COUNTER KAPALI
		GPIOD->ODR |= (0X01); // KIRMIZI SÖNÜK



		TIM5->CR1 |= (0X01);
		GPIOD->ODR &= ~(0X01<<1);


		TIM6->CR1 &= ~(0X01);
		GPIOD->ODR |= (0X01<<2);

	}else if(cnt3%8==6){ // kırmızı yanık. yeşil mavi sönük


		TIM4->CR1 |= (0X01); // TIM4 COUNTER KAPALI
		GPIOD->ODR &= ~(0X01); // KIRMIZI SÖNÜK



		TIM5->CR1 &= ~(0X01);
		GPIOD->ODR |= (0X01<<1);

		TIM6->CR1 &= ~(0X01);
		GPIOD->ODR |= (0X01<<2);


	}else if(cnt3%8==7){ // kırmızı yeşil mavi sönük
		TIM4->CR1 &= ~(0X01); // TIM4 COUNTER KAPALI
		GPIOD->ODR |= (0X01); // KIRMIZI SÖNÜK

		TIM5->CR1 &= ~(0X01);
		GPIOD->ODR |= (0X01<<1);

		TIM6->CR1 &= ~(0X01);
		GPIOD->ODR |= (0X01<<2);
	}

	cnt3++;


}

int main(void) {
	//Enable Clock for GPIO
	RCC_AHB2ENR |= (1 << 3); // gpiod clock active
	RCC_APB1ENR |= (1<<2);  // tim 4 clock active
	RCC_APB1ENR |= (1<<3);	// tim 5 clock active
	RCC_APB1ENR |= (1<<4);	// tim 6 clock active
	RCC_APB1ENR |= (1<<5);	// tim 7 clock active


	//Configure Pin as General purpose output mode
	GPIOD->MODER |= (1 << 0); 	// pd0 output mode
	GPIOD->MODER &= ~(1 << 1);
	GPIOD->MODER |= (1 << 2);	// pd1 output mode
	GPIOD->MODER &= ~(1 << 3);
	GPIOD->MODER |= (1 << 4);	// pd2 output mode
	GPIOD->MODER &= ~(1 << 5);



	// tim4 initialize (red)
	NVIC_ISER1 |= (0x01<<15);
	TIM4->DIER |= 0x01;  	// update interrupt aç
	TIM4->EGR  |= 0x01; 	// interrupt yarat ve timer 0 la
	TIM4->PSC = 3999; 		// 4MHZ/(3999+1)= 1KHZ ->>>> HER COUNTER 1 MS
	TIM4->ARR = 9; 			// 9+1= 10 MS . 100HZ --->> INTERRUPT EVERY 10MS
	TIM4->CR1 |= 0x01;		// timer counterını başlat

	// tim5 initialize (green)
	NVIC_ISER1 |= (0x01<<16);

	TIM5->DIER |= 0x01;  	// update interrupt aç
	TIM5->EGR  |= 0x01; 	// interrupt yarat ve timer 0 la
	TIM5->PSC = 3999; 		// 4MHZ/(3999+1)= 1KHZ ->>>> HER COUNTER 1 MS
	TIM5->ARR = 4; 			// 4+1= 5 MS . 200HZ --->> INTERRUPT EVERY 5MS
	TIM5->CR1 |= 0x01;		// timer counterını başlat

	// tim6 initialize (blue)
	NVIC_ISER1 |= (0x01<<17);

	TIM6->DIER |= 0x01;  	// update interrupt aç
	TIM6->EGR  |= 0x01; 	// interrupt yarat ve timer 0 la
	TIM6->PSC = 3999; 		// 4MHZ/(3999+1)= 1KHZ ->>>> HER COUNTER 1 MS
	TIM6->ARR = 2; 			// 2+1= 3 MS . 400HZ --->> INTERRUPT EVERY 3MS
	TIM6->CR1 |= 0x01;		// timer counterını başlat

	// tim7 initialize (1 second timer)
	NVIC_ISER1 |= (0x01<<18);

	TIM7->DIER |= 0x01;  	// update interrupt aç
	TIM7->EGR  |= 0x01; 	// interrupt yarat ve timer 0 la
	TIM7->PSC = 3999; 		// 4MHZ/(3999+1)= 1KHZ ->>>> HER COUNTER 1 MS
	TIM7->ARR = 999; 		// 999+1= 1 S . 1HZ --->> INTERRUPT EVERY S
	TIM7->CR1 |= 0x01;		// timer counterını başlat



	__asm volatile( //enable all interrupts that are configured
	 "mov r0, #0 \n\t"
	 "msr primask, r0 \n\t"
	 );

	GPIOD->ODR &= ~(0X01);

	GPIOD->ODR &= ~(0X01<<1);

	GPIOD->ODR &= ~(0X01<<2);




























}
