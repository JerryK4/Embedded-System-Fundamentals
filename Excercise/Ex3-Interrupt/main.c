#include "stm32f4xx.h"

void init_led();
void init_button();
void init_interrupt();

int main() {
    init_led();
    init_button();
    init_interrupt();

    // Kích hoạt ngắt EXTI từ dòng 10 đến 15
    NVIC_EnableIRQ(EXTI15_10_IRQn);

    // Kích hoạt ngắt EXTI từ dòng 5 đến 9
    NVIC_EnableIRQ(EXTI9_5_IRQn);

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

    // Cấu hình PC8 (LED vàng) làm output
    GPIOC->MODER |= (1 << 16);
    GPIOC->MODER &= ~(1 << 17);
}

void init_button() {
    // Cấu hình PC13 làm input
    GPIOC->MODER &= ~(1 << 26);
    GPIOC->MODER &= ~(1 << 27);

    // Cấu hình PA9 làm input
    GPIOA->MODER &= ~(1 << 18);
    GPIOA->MODER &= ~(1 << 19);
}

void init_interrupt() {
    // Bật clock cho SYSCFG (cần để cấu hình EXTI)
    RCC->APB2ENR |= (1 << 14);

    // Chọn PC13 làm nguồn cho EXTI13
    SYSCFG->EXTICR[3] &= ~(0xF << 4);  // Xóa 4 bit
    SYSCFG->EXTICR[3] |= (0x2 << 4);   // PC13 (giá trị 0010)

    // Kích hoạt ngắt trên EXTI13 (không bị mask)
    EXTI->IMR |= (1 << 13);

    // Kích hoạt ngắt cạnh xuống (falling edge trigger) cho EXTI13
    EXTI->FTSR |= (1 << 13);

    // Chọn PA9 làm nguồn cho EXTI9 (PA mặc định là 0000 nên không cần ghi thêm)
    SYSCFG->EXTICR[2] &= ~(0xF << 4);

    // Kích hoạt ngắt trên EXTI9 (không bị mask)
    EXTI->IMR |= (1 << 9);

    // Kích hoạt ngắt cạnh xuống (falling edge trigger) cho EXTI9
    EXTI->FTSR |= (1 << 9);

    // Bật ngắt trong NVIC
    NVIC_EnableIRQ(EXTI15_10_IRQn);
    NVIC_EnableIRQ(EXTI9_5_IRQn);

    // Đặt mức ưu tiên cho các ngắt
    NVIC_SetPriority(EXTI15_10_IRQn, 3);
    NVIC_SetPriority(EXTI9_5_IRQn, 2);
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

// **Hàm xử lý ngắt EXTI9**
void EXTI9_5_IRQHandler() {
    if (EXTI->PR & (1 << 9)) { // Kiểm tra nếu ngắt xảy ra ở EXTI9
        // Bật LED vàng PC8
        GPIOC->ODR |= (1 << 8);


        // Giữ LED vàng sáng trong một khoảng thời gian
        for (volatile int i = 0; i < 2000000; i++);

        // Tắt LED vàng PC8
        GPIOC->ODR &= ~(1 << 8);


        // Xóa cờ ngắt EXTI9
        EXTI->PR |= (1 << 9);
    }
}
