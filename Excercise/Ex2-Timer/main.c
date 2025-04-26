#include "stm32f401xe.h"

void Timer1_Init(void);
void Timer2_Init(void);
void LED_Init(void);

int toggle_flag = 0;  // Cờ kiểm soát luân phiên

int main(void) {
    LED_Init();
    Timer1_Init();    // Khởi động với Timer1 (1s)

    while (1) {
        // Không cần xử lý gì trong vòng lặp
    }
}

void LED_Init(void) {
    RCC->AHB1ENR |= (1 << 0);      // Clock cho GPIOA
    GPIOA->MODER |= (1 << 16);     // PA8 Output
    GPIOA->MODER &= ~(1 << 17);
}

void Timer1_Init(void) {
    RCC->APB2ENR |= (1 << 0);      // Clock cho TIM1
    TIM1->PSC = 16000 - 1;         // 1 ms/tick
    TIM1->ARR = 1000 - 1;          // 1s
    TIM1->CR1 |= (1 << 4);         // Đếm xuống (DIR = 1)
    TIM1->DIER |= (1 << 0);        // Cho phép ngắt
    NVIC_EnableIRQ(TIM1_UP_TIM10_IRQn);
    TIM1->CNT = TIM1->ARR;
    TIM1->CR1 |= (1 << 0);         // Bật Timer1
}

void Timer2_Init(void) {
    RCC->APB1ENR |= (1 << 0);      // Clock cho TIM2
    TIM2->PSC = 16000 - 1;         // 1 ms/tick
    TIM2->ARR = 2000 - 1;          // 2s
    TIM2->CR1 |= (1 << 4);         // Đếm xuống
    TIM2->DIER |= (1 << 0);        // Cho phép ngắt
    NVIC_EnableIRQ(TIM2_IRQn);
    TIM2->CNT = TIM2->ARR;
    TIM2->CR1 |= (1 << 0);         // Bật Timer2
}

// ================== Ngắt Timer1: 1s ==================
void TIM1_UP_TIM10_IRQHandler(void) {
    if (TIM1->SR & 0x1) {
        TIM1->SR &= ~0x1;           // Xoá cờ
        GPIOA->ODR ^= (1 << 8);     // Toggle LED
        TIM1->CR1 &= ~(1 << 0);     // Tắt Timer1
        Timer2_Init();              // Bật Timer2
    }
}

// ================== Ngắt Timer2: 2s ==================
void TIM2_IRQHandler(void) {
    if (TIM2->SR & 0x1) {
        TIM2->SR &= ~0x1;
        GPIOA->ODR ^= (1 << 8);     // Toggle LED
        TIM2->CR1 &= ~(1 << 0);     // Tắt Timer2
        Timer1_Init();              // Bật lại Timer1
    }
}
