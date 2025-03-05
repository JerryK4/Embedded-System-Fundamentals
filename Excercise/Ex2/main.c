#include "stm32f4xx_hal.h"

#define button_pressed 0
int main(void)
{
     init_led();    //Initialize led
     init_button(); //Initialize button

    //Reading status of button and turn on/off led based on status of button
    uint32_t read_status;
    while (1)
    {
        read_status =  GPIOC->IDR & (1<<13);      // using GPIOx_IDR register
        if (read_status == button_pressed)
        {
            //Turn on green led
        	GPIOA->ODR |= 1<<(5);
        }
        else
        {
            //Turn off green led
        	GPIOA->ODR &= ~(1<<(5));
        }
    }
}

void init_led()
{
                  // 1. Enable clock to IO Port A (Using RCC AHB1ENR register)
	RCC->AHB1ENR |= 1 << 0;
                  // 2. Configure I/O direction mode on PA5 to general output mode (Using GPIOx_MODER register)
	GPIOA->MODER |= 1<<10;
	GPIOA->MODER &= ~(1<<11);
                 // 3. Configure pull-up register on PA5 (Using GPIOx_PUPDR register)
	GPIOA->PUPDR |= 1<<10;
	GPIOA->PUPDR &= ~(1<<11);
}

void init_button()
{
                //4. Enable clock to IO Port C (Using RCC AHB1ENR register)
	RCC->AHB1ENR |= 1 << 2;
                // 5. Configure I/O direction mode on PC13 to input mode (Using GPIOx_MODER register)
	GPIOC->MODER &= ~(1<<26);
	GPIOC->MODER &= ~(1<<27);

	GPIOC->PUPDR |= 1<<26;
	GPIOC->PUPDR &= ~(1<<27);

}
