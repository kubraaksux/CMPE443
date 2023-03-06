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
	volatile uint32_t AFRL;
	volatile uint32_t AFRH;
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

typedef struct
{
  volatile uint32_t ISR;
  volatile uint32_t IER;
  volatile uint32_t CR;
  volatile uint32_t CFGR;
  volatile uint32_t CFGR2;
  volatile uint32_t SMPR1;
  volatile uint32_t SMPR2;
  volatile uint32_t REZ0;
  volatile uint32_t TR1;
  volatile uint32_t TR2;
  volatile uint32_t TR3;
  volatile uint32_t REZ1;
  volatile uint32_t SQR1;
  volatile uint32_t SQR2;
  volatile uint32_t SQR3;
  volatile uint32_t SQR4;
  volatile uint32_t DR;

} ADC_TypeDef;

#define GPIOA ((GPIO_TypeDef *) 0x42020000)
#define GPIOG ((GPIO_TypeDef *) 0x42021800)

#define ADC   ((ADC_TypeDef *)  0x42028000)

#define TIM7  ((TIM_TypeDef *) 0x40001400)

#define RCC_CCIPR1 *((volatile uint32_t *) (0x40021088))
#define RCC_APB1ENR1 *((volatile uint32_t *) (0x40021058))
#define RCC_APB1ENR2 *((volatile uint32_t *) (0x4002105C))
#define RCC_CR *((volatile uint32_t *) (0x40021000))
#define RCC_AHB2ENR *((volatile uint32_t *) (0x4002104C))

#define PWR_CR1 *((volatile uint32_t *) (0x40007000))
#define PWR_CR2 *((volatile uint32_t *) (0x40007004))


#define LPUART_CR1 *((volatile uint32_t *) (0x40008000))
#define LPUART_BRR *((volatile uint32_t *) (0x4000800C))
#define LPUART_TDR *((volatile uint32_t *) (0x40008028))
#define LPUART_ICR *((volatile uint32_t *) (0x40008020))

#define NVIC_ISER2 *((volatile uint32_t *) 0xE000E108)
#define NVIC_ISER1 *((volatile uint32_t *) 0xE000E104)


void LPUART1_IRQHandler() {
	LPUART_ICR |= (1<<6);
}

int ADC_val = 0;

void ADC1_2_IRQHandler() {

	ADC_val = ADC->DR;
	ADC->CR |= (1<<2);
}

void TIM7_IRQHandler(void){
	TIM7->SR &= ~(0X01);
	LPUART_TDR =(ADC_val/1000)%10 + '0';
	LPUART_TDR =(ADC_val/100)%10 + '0';
	LPUART_TDR =(ADC_val/10)%10 + '0';
	LPUART_TDR = ADC_val%10 + '0';


	LPUART_TDR = '\r';
	LPUART_TDR = '\n';


}



int main(void) {

	RCC_APB1ENR1 |= (1<<5);	// tim 7 clock active
	// tim7 initialize (1 second timer)
	NVIC_ISER1 |= (0x01<<18);
	TIM7->DIER |= 0x01;  	// update interrupt aç
	TIM7->EGR  |= 0x01; 	// interrupt yarat ve timer 0 la
	TIM7->PSC = 3999; 		// 4MHZ/(3999+1)= 1KHZ ->>>> HER COUNTER 1 MS
	TIM7->ARR = 499; 		// 999+1= 1 S . 1HZ --->> INTERRUPT EVERY S
	TIM7->CR1 |= 0x01;		// timer counterını başlat


	//Enable Clock for Power Interface
	RCC_APB1ENR1 |= (1<<28);

	//Change the regulator mode to Low-power mode
	PWR_CR1 |= (1<<14);
	//RCC_CR &= ~(1<<7);
	//RCC_CR |= 1<<6;
	//RCC_CR &= ~(1<<5);
	//RCC_CR |= 1<<4;

	//Make VDDIO2 valid
	PWR_CR2|= (1<<9);

	//Change the clock source of Low-power UART to SYSCLK
	RCC_CCIPR1 |= (1<<10);

	//Enable Clock for Low-power UART
	RCC_APB1ENR2 |= (1<<0);

	//Enable Clock for GPIO
	RCC_AHB2ENR |= (1<<6);

	//Change the functionality of the pin
	GPIOG->MODER |= 1<<15;
	GPIOG->MODER &= ~(1<<14);
	GPIOG->AFRL |=  (1<<31);
	//GPIOG->AFRL |=  ~(1<<30);
	//GPIOG->AFRL |=  ~(1<<29);
	//GPIOG->AFRL |=  ~(1<<28);


	//Change LPUART baud rate (BRR) for 9600 Baud rate
	LPUART_BRR = 106666;


	//Enable FIFO mode for UART
	LPUART_CR1 |= (1<<29);

	//Enable Transmitter and Receiver for UART
	LPUART_CR1 |= (1<<2);
	LPUART_CR1 |= (1<<3);

	//Enable Interrupt and LPUART
	NVIC_ISER2 |= 1<<2;
	LPUART_CR1 |= (1<<0);
	LPUART_CR1 |= 1<<6;

//Enable Clock for ADC
	RCC_AHB2ENR |= (1<<13);

	//Select ADC clock as System clock
	RCC_CCIPR1 |= (3<<28);

	//Change Pin Mode to Analog
	GPIOA->MODER |= 3;

	//Change Pin Pull/Down to no pull-up no pull-down
	GPIOA->PUPDR &= ~(0x03);

	//Change Regular channel sequence length to 1 conversion
	ADC->SQR1 &= ~(15);

	//Add to channel to first sequence
	ADC->SQR1 |= (0x05<<6);  ////sqr pa 0ın channeli 5
	//sqr

	//Enable ADC Voltage regulator
	ADC->CR &= ~(1<<29);

	//Disable Deep-power-down for ADC
	ADC->CR |= (1<<28);

	//Configure for Single conversion mode
	ADC->CFGR &= ~(1<<13);

	//Enable ADC
	ADC->CR |= 1;


	//Wait ADC is enabled
	while(!(ADC->ISR &1));

	//Enable interrupt for end of regular conversion
	ADC->IER |= (1<<2);
	NVIC_ISER1 |= (0x01<<5);// Enable IRQ for ADC

	//Start regular conversion of ADC
	ADC->CR |= (1<<2);


	while(1){

	}
}
