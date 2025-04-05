#include "stm32f4xx.h"

void init_led();
void init_button();
void init_interrupt();

int main() {
    init_led();
    init_button();
    init_interrupt();

    NVIC_EnableIRQ(EXTI15_10_IRQn); // Kích hoạt ngắt EXTI từ dòng 10 đến 15

    while (1) {
        // Nhấp nháy LED đỏ PC5
        GPIOC->ODR ^= (1 << 5);
        for (volatile int i = 0; i < 1000000; i++); // Delay đơn giản
    }
}

void init_led() {
    // Bật clock cho Port A và Port C
    RCC->AHB1ENR |= (1 << 0); // Bật clock cho Port A
    RCC->AHB1ENR |= (1 << 2); // Bật clock cho Port C

    // Cấu hình PA5 (LED xanh) làm output
    GPIOA->MODER |= (1 << 10);
    GPIOA->MODER &= ~(1 << 11);

    // Cấu hình PC5 (LED đỏ) làm output
    GPIOC->MODER |= (1 << 10);
    GPIOC->MODER &= ~(1 << 11);

    // Kéo lên điện trở cho PA5, PC5
    GPIOA->PUPDR |= (1 << 10);
    GPIOA->PUPDR &= ~(1 << 11);
    GPIOC->PUPDR |= (1 << 10);
    GPIOC->PUPDR &= ~(1 << 11);
}

void init_button() {
    // Bật clock cho Port C (đã bật ở init_led)

    // Cấu hình PC13 làm input
    GPIOC->MODER &= ~(1 << 26);
    GPIOC->MODER &= ~(1 << 27);
}

void init_interrupt() {
    // Bật clock cho SYSCFG (cần để cấu hình EXTI)
    RCC->APB2ENR |= (1 << 14);

    // Chọn PC13 làm nguồn cho EXTI13
    SYSCFG->EXTICR[3] &= ~(1 << 4);
    SYSCFG->EXTICR[3] |= (1 << 5);
    SYSCFG->EXTICR[3] &= ~(1 << 6);
    SYSCFG->EXTICR[3] &= ~(1 << 7);

    // Kích hoạt ngắt trên EXTI13 (không bị mask)
    EXTI->IMR |= (1 << 13);

    // Kích hoạt ngắt cạnh xuống (falling edge trigger) cho EXTI13
    EXTI->FTSR |= (1 << 13);
}

// **Hàm xử lý ngắt EXTI13**
void EXTI15_10_IRQHandler() {
    if (EXTI->PR & (1 << 13)) { // Kiểm tra nếu ngắt xảy ra ở EXTI13
        // Bật LED xanh PA5
        GPIOA->ODR |= (1 << 5);

        // Giữ LED xanh sáng trong một khoảng thời gian
        for (volatile int i = 0; i < 2000000; i++);

        // Tắt LED xanh PA5
        GPIOA->ODR &= ~(1 << 5);

        // Xóa cờ ngắt EXTI13
        EXTI->PR |= (1 << 13);
    }
}
