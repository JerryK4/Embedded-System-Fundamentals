#include "stm32f401xe.h"

void GPIO_Init(void);
void TIM2_PWM_Init(void);
void delay_ms(uint32_t ms);

int main(void) {
    GPIO_Init();         // Initialize GPIO for PA5
    TIM2_PWM_Init();     // Initialize Timer 2 for PWM

    while (1) {
        // Fade in
        for (int dutyCycle = 0; dutyCycle <= 1000; dutyCycle += 10) {
            TIM2->CCR1 = dutyCycle;     // Set duty cycle (compare value)
            delay_ms(10);               // Delay for visible fading effect
        }

        // Fade out
        for (int dutyCycle = 1000; dutyCycle >= 0; dutyCycle -= 10) {
            TIM2->CCR1 = dutyCycle;
            delay_ms(10);
        }
    }
}

void GPIO_Init(void) {
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;           // Enable GPIOA clock
    GPIOA->MODER &= ~(3 << (5 * 2));               // Clear mode bits for PA5
    GPIOA->MODER |=  (2 << (5 * 2));               // Set PA5 to alternate function mode
    GPIOA->AFR[0] &= ~(0xF << (5 * 4));            // Clear alternate function bits
    GPIOA->AFR[0] |=  (1 << (5 * 4));              // Set AF1 (TIM2_CH1) for PA5
}

void TIM2_PWM_Init(void) {
    RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;            // Enable Timer 2 clock
    TIM2->PSC = 16 - 1;                            // Prescaler to get 1 MHz timer clock (16 MHz / 16)
    TIM2->ARR = 1000 - 1;                          // Auto-reload value for 1 kHz PWM frequency
    TIM2->CCR1 = 0;                                // Initial duty cycle 0%
    TIM2->CCMR1 &= ~(TIM_CCMR1_OC1M);              // Clear output compare mode bits
    TIM2->CCMR1 |= (6 << 4);                       // Set PWM mode 1 (110)
    TIM2->CCMR1 |= TIM_CCMR1_OC1PE;                // Enable preload
    TIM2->CCER |= TIM_CCER_CC1E;                   // Enable output on CH1
    TIM2->CR1 |= TIM_CR1_ARPE;                     // Enable auto-reload preload
    TIM2->EGR |= TIM_EGR_UG;                       // Generate an update event to load registers
    TIM2->CR1 |= TIM_CR1_CEN;                      // Enable TIM2 counter
}

void delay_ms(uint32_t ms) {
    RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;            // Enable Timer 3 clock
    TIM3->PSC = 16000 - 1;                         // Prescaler to get 1 kHz (1ms tick)
    TIM3->ARR = ms;                                // Auto-reload value for 'ms' delay
    TIM3->EGR |= TIM_EGR_UG;                       // Generate an update event
    TIM3->SR &= ~TIM_SR_UIF;                       // Clear update flag
    TIM3->CR1 |= TIM_CR1_CEN;                      // Enable TIM3

    while (!(TIM3->SR & TIM_SR_UIF));              // Wait until update event flag is set
    TIM3->SR &= ~TIM_SR_UIF;                       // Clear update flag
    TIM3->CR1 &= ~TIM_CR1_CEN;                     // Stop TIM3 to reset for next use
}
