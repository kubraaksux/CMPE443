

#include <stdint.h>

typedef struct {
	volatile uint16_t MODER[2];
	volatile uint16_t OTYPER[2];
	volatile uint16_t OSPEEDR[2];
	volatile uint16_t PUPDR[2];
	volatile uint16_t IDR[2];
	volatile uint16_t ODR[2];
	volatile uint16_t BSRR[2];
	volatile uint16_t LCKR[2];
	volatile uint16_t AFR[4];
	volatile uint16_t BRR[2];
	uint16_t RESERVED[2];
	volatile uint16_t SECCFGR[2];
} GPIO_TypeDef;

uint32_t wait_milisecond = 1000;
uint32_t wait_counter = 0;

#define RCC_AHB2ENR *((volatile uint32_t *) (0x40021000 + 0x4C))

#define GPIOA	((GPIO_TypeDef *) 0x42020000)
#define GPIOB	((GPIO_TypeDef *) 0x42020400)
#define GPIOC	((GPIO_TypeDef *) 0x42020800)
#define GPIOE	((GPIO_TypeDef *) 0x42021000)


int main(void) {
	RCC_AHB2ENR |= 0x01 << 0;
	RCC_AHB2ENR |= 0x01 << 1;
	RCC_AHB2ENR |= 0x01 << 2;
	RCC_AHB2ENR |= 0x01 << 4;

	GPIOA->MODER[1] &= ~(1<<3);
	GPIOB->MODER[0] &= ~(1<<15);
	GPIOC->MODER[0] &= ~(1<<15);
	GPIOE->MODER[0] &= ~(3<<0);
	GPIOE_PUPDR[1] |= 1 << 12;
	GPIOE_PUPDR[1] &= ~(1 << 13);

	while(1) {
		int index;
		int counter;

		while (GPIOE_IDR[0] & (1<<15)){
		
		
		GPIOA->ODR[0] |= (0x01 << 9);
		GPIOB->ODR[0] |= (0x01 << 7);
		GPIOC->ODR[0] |= (0x01 << 7);

		GPIOA->ODR[0] |= (1 << 9);
		GPIOC->ODR[0] &= ~(1 << 7);
		GPIOB->ODR[0] &= ~(1 << 7);

		GPIOB->ODR[0] |= (1 << 7);
		GPIOA->ODR[0] &= ~(1 << 9);
		GPIOC->ODR[0] &= ~(1 << 7);

		GPIOC->ODR[0] |= (1 << 7);
		GPIOA->ODR[0] &= ~(1 << 9);
		GPIOB->ODR[0] &= ~(1 << 7);
		} 

		for(index=0;index<wait_milisecond*333;index++);

		__asm volatile("MOV R12, %0" : :"r"(wait_counter));
		__asm volatile("ADDS R12, #0x01");
		__asm volatile("MOV %0, R12" : "=r"(wait_counter));
	}
}
