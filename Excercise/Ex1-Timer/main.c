#include "stm32f401xe.h"

void Timer1_Init(void);
void LED_Init(void);

volatile int toggle_flag = 0;

int main(void) {
    LED_Init();
    Timer1_Init();

    while (1) {
        // Xử lý trong ngắt
    }
}

void LED_Init(void) {
    // Bật clock cho GPIOC
    RCC->AHB1ENR |= (1 << 2);

    // Cấu hình PC8 làm output
    GPIOC->MODER |= (1 << 16);
    GPIOC->MODER &= ~(1 << 17);
}

void Timer1_Init(void) {
    // Bật clock cho Timer 1
    RCC->APB2ENR |= (1 << 0);

    // Đặt prescaler để tạo tần số 1kHz (16 MHz / 16000 = 1 kHz)
    TIM1->PSC = 16000 - 1;

    // Đặt giá trị auto-reload để đạt 1s (1000ms) hoặc 2s (2000ms)
    TIM1->ARR = 1000 - 1; // 1 giây

    // Cho phép ngắt update event
    TIM1->DIER |= (1 << 0);

    // Bật bộ đếm
    TIM1->CR1 |= (1 << 0);

    // Kích hoạt ngắt Timer 1 trong NVIC
    NVIC_EnableIRQ(TIM1_UP_TIM10_IRQn);
}

// Hàm xử lý ngắt Timer 1
void TIM1_UP_TIM10_IRQHandler(void) {
    if (TIM1->SR & 0x1) { // Kiểm tra cờ ngắt
        TIM1->SR &= ~0x1; // Xóa cờ ngắt

        // Đổi trạng thái LED mỗi chu kỳ
        if (toggle_flag == 0) {
            TIM1->ARR = 2000 - 1; // Chuyển sang 2s
            toggle_flag = 1;
        } else {
            TIM1->ARR = 1000 - 1; // Chuyển lại 1s
            toggle_flag = 0;
        }

        GPIOC->ODR ^= (1 << 8); // Toggle LED PC8
    }
}
