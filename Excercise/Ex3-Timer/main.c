#include "stm32f4xx.h"

void Timer2_Init(void);
void Led_Init(void);

volatile uint32_t counter = 0;

int main(void) {
    // Khởi tạo LED
    Led_Init();

    // Khởi tạo Timer2
    Timer2_Init();

    while (1) {
        // Chờ cờ update event (UIF) của Timer
        if (TIM2->SR & 0x1) {
            // Xóa cờ update event
            TIM2->SR &= ~(1 << 0);
            counter++;

            // Toggle PB0 mỗi 1 giây
            if (counter % 1 == 0) {
                GPIOB->ODR ^= (1 << 0);
            }

            // Toggle PB1 mỗi 2 giây
            if (counter % 2 == 0) {
                GPIOB->ODR ^= (1 << 1);
            }

            // Toggle PC13 mỗi 4 giây
            if (counter % 4 == 0) {
                GPIOC->ODR ^= (1 << 13);
            }
        }
    }
}

void Timer2_Init(void) {
    // Bật clock cho Timer 2
    RCC->APB1ENR |= (1 << 0);

    // Chia prescaler để được tick 1ms (16 MHz / 16000 = 1kHz)
    TIM2->PSC = 16000 - 1;

    // Auto-reload mỗi 1000ms (1 giây)
    TIM2->ARR = 1000 - 1;

    // Bắt đầu Timer (CEN = 1)
    TIM2->CR1 = 1 << 0;
}

void Led_Init(void) {
    // Bật clock cho GPIOB và GPIOC
    RCC->AHB1ENR |= (1 << 1); // GPIOB
    RCC->AHB1ENR |= (1 << 2); // GPIOC

    // PB0 output
    GPIOB->MODER |= (1 << 0);
    GPIOB->MODER &= ~(1 << 1);

    // PB1 output
    GPIOB->MODER |= (1 << 2);
    GPIOB->MODER &= ~(1 << 3);

    // PC13 output
    GPIOC->MODER |= (1 << 26);
    GPIOC->MODER &= ~(1 << 27);
}
