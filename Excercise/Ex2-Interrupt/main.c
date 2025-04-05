#include "stm32f4xx.h"

void init_led();
void init_input();
void init_interrupt();

void main() {
    //HAL_Init();
    init_led();
    init_input();
    init_interrupt();

    while (1) {
        GPIOC->ODR |= (1 << 5);
        delay(200000); // LED chính nhấp nháy
        GPIOC->ODR &= ~(1 << 5);
        delay(200000);
    }
}

void init_led() {
    RCC->AHB1ENR |= (1 << 2); // CLOCK ENABLE PORT C
    GPIOC->MODER |= (1 << (8 * 2)); // OUTPUT LED PC8 (LED ngắt)
    GPIOC->MODER |= (1 << (5 * 2)); // OUTPUT LED PC5 (LED chính)
}

void init_input() {
    RCC->AHB1ENR |= (1 << 2); // CLOCK ENABLE PORT C
    GPIOC->MODER &= ~(3 << (6 * 2)); // PC6 là input (IR sensor)
}

void init_interrupt() {
    RCC->APB2ENR |= (1 << 14); // ENABLE SYSCFG

    // Cấu hình ngắt cho PC6
    SYSCFG->EXTICR[1] &= ~(0xF << 8); // Xóa cấu hình cũ của EXTI6
    SYSCFG->EXTICR[1] |= (2 << 8); // Chọn PC6 làm nguồn ngắt EXTI6 (0b0010)

    EXTI->IMR |= (1 << 6); // Cho phép ngắt từ PC6 (EXTI6)
    EXTI->FTSR |= (1 << 6); // Kích hoạt ngắt khi có cạnh xuống (falling)
    EXTI->RTSR |= (1 << 6); // Kích hoạt ngắt khi có cạnh lên (rising)

    NVIC_EnableIRQ(EXTI9_5_IRQn); // Kích hoạt ngắt EXTI6
}

void EXTI9_5_IRQHandler() {
    if (EXTI->PR & (1 << 6)) { // Kiểm tra có ngắt từ PC6 không
        while ((GPIOC->IDR & (1 << 6)) == 0) { // Nếu PC6 vẫn là 0, giữ LED sáng
            GPIOC->ODR |= (1 << 8);
        }
        GPIOC->ODR &= ~(1 << 8); // Khi PC6 trở lại 1, tắt LED

        EXTI->PR = (1 << 6); // Xóa cờ pending bit
    }
}
void delay(uint32_t time) {
    for (volatile uint32_t i = 0; i < time; i++);
}
