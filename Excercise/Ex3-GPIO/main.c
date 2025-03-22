#include "stm32f4xx_hal.h"

#define button_pressed 0
#define button1 8

int main(void)
{
     init_led();    //Initialize led
     init_button(); //Initialize button

    //Reading status of button and turn on/off led based on status of button
    uint32_t read_button1, read_button2, read_button3;
    while (1)
    {
        read_button1 = (GPIOC->IDR >> button1) & 0x1;       // using GPIOx_IDR register
        if (read_button1 == button_pressed)
        {
            //Turn on red led
        	GPIOA->ODR |= 1<<(15);
        }
        else
        {
            //Turn off red led
        	GPIOA->ODR &= ~(1<<(15));
        }


    }
}
void init_led()
{
    // 1. Enable clock to IO Port A (Using RCC AHB1ENR register)
	RCC->AHB1ENR |= 1 << 0;
    // 2. Configure I/O direction mode on PA15 to general output mode (Using GPIOx_MODER register)
	GPIOA->MODER |= 1<<30;
	GPIOA->MODER &= ~(1<<31);
    // 3. Configure pull-up register on PA15 (Using GPIOx_PUPDR register)
	GPIOA->PUPDR |= 1<<30;
	GPIOA->PUPDR &= ~(1<<31);
}

void init_button()
{
		//4. Enable clock to IO Port C (Using RCC AHB1ENR register)
	RCC->AHB1ENR |= 1 << 2;
		// 5. Configure I/O direction mode on PC8 to input mode (Using GPIOx_MODER register)
	GPIOC->MODER &= ~(1<<16);
	GPIOC->MODER &= ~(1<<17);

	GPIOC->PUPDR |= 1<<16;
	GPIOC->PUPDR &= ~(1<<17);
}
