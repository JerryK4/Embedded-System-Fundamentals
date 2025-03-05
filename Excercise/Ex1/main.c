#include "stm32f4xx_hal.h"

int main(void)
{
	RCC->AHB1ENR |= 1 << 0; // 1. Enable clock to IO Port A (Using RCC AHB1ENR register)
	 // 2. Configure I/O direction mode on PA5 to general output mode (Using GPIOx_MODER register)
	GPIOA->MODER |= 1<<10;
	GPIOA->MODER &= ~(1<<11);
	// 3. Configure pull-up register on PA5 (Using GPIOx_PUPDR register)
	GPIOA->PUPDR |= 1<<10;
	GPIOA->PUPDR &= ~(1<<11);
	while(1)
	{
	//4. Write 1 to pin PA5 (Using GPIOx_ODR register or GPIOx_BSRR register to turn led on)
	GPIOA->ODR |= 1<<(5);
	for (int i = 0; i < 3000000; i++);
	// 5. Write 0 to pin PA5 (Using GPIOx_ODR register or GPIOx_BSRR register to turn led off
	GPIOA->ODR &= ~(1<<(5));
	for (int i = 0; i < 3000000; i++);
	}
}





#include "stm32f4xx_hal.h"

int main(void)
{
	RCC->AHB1ENR |= 1 << 0; // 1. Enable clock to IO Port A (Using RCC AHB1ENR register)
	 // 2. Configure I/O direction mode on PA5 to general output mode (Using GPIOx_MODER register)
	GPIOA->MODER |= 1<<10;
	GPIOA->MODER &= ~(1<<11);
	// 3. Configure pull-up register on PA5 (Using GPIOx_PUPDR register)
	//GPIOA->PUPDR &= ~(3<<(5*2));
	GPIOA->PUPDR |= 1<<10;
	GPIOA->PUPDR &= ~(1<<11);
	while(1)
	{
	//4. Write 1 to pin PA5 (Using GPIOx_ODR register or GPIOx_BSRR register to turn led on)
	//GPIOA->ODR |= 1<<(5);
	GPIOA->BSRR |= 1<<(5);
	for (int i = 0; i < 3000000; i++);
	// 5. Write 0 to pin PA5 (Using GPIOx_ODR register or GPIOx_BSRR register to turn led off
	//GPIOA->ODR &= ~(1<<(5));
	GPIOA->BSRR |= 1<<(5+16);
	for (int i = 0; i < 3000000; i++);
	}
}
