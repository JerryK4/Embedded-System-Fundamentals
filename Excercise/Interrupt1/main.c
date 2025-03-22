#include "stm32f4xx_hal.h"

void main()
{
    init_led();
    init_button();
    init_interrupt();

    NVIC_EnableIRQ(EXTI15_10_IRQn); //Enable interrupt for EXTI Line from 10 to 15

    while(1);
}

void init_led()
{
    //Enable clock to port A
	RCC->AHB1ENR |= 1 << 0;
    //Configure PA5 as output
	GPIOA->MODER |= 1 << 10;
	GPIOA->MODER &= ~(1 << 11);
    //Configure pull up register for PA5
	GPIOA->PUPDR |= 1 << 10;
	GPIOA->PUPDR &= ~(1 << 11);
}
void init_button()
{
           //Enable clock to port C
	RCC->AHB1ENR |= 1<<2;
          //Configure PC13 as input
	GPIOC->MODER &= ~(1 << 26);
	GPIOC->MODER &= ~(1 << 27);

}

void init_interrupt()
{
        //Enable System configuration controller clock (using RCC_APB2ENR register)
	RCC->APB2ENR |= 1 << 14;
       /*Choose PC13 for EXTI13 line interrupt (using SYSCFG->EXTICR[3] register, equivalent to
          SYSCFG_EXTICR4 in reference manual)*/
	SYSCFG->EXTICR[3] &= ~(1 << 4);
	SYSCFG->EXTICR[3] |= (1 << 5);
	SYSCFG->EXTICR[3] &= ~(1 << 6);
	SYSCFG->EXTICR[3] &= ~(1 << 7);
        //Interrupt request from line 13 is not masked (using EXTI_IMR register)
	EXTI->IMR |= 1 << 13;
       //Falling edge trigger enable for line 13 (using EXTI_FTSR register)
	EXTI->FTSR |= 1<<13;
}
void EXTI15_10_IRQHandler()
{

    uint32_t previous_state = (GPIOA->ODR >> 5) & 0x1; // Read previous of green led on PA5
   if (previous_state == 0)
   {
            // Turn on led
	   GPIOA->ODR |= (1 << 5);
   }
  else
   {
           // Turn off led
	  GPIOA->ODR &= ~(1 << 5);
   }
           // Clear pending bit for EXTI13 (using EXTI_PR register)
   EXTI->PR |= (1<<13);

}
