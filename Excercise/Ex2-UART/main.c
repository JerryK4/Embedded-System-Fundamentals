#include "stm32f4xx.h"

// ======== USART2 Initialization (TX on PA2) =========
void USART2_Init(void) {
    // Bật clock cho GPIOA và USART2
    RCC->AHB1ENR |= (1 << 0);    // GPIOA
    RCC->APB1ENR |= (1 << 17);   // USART2

    // PA2 là Alternate Function
    GPIOA->MODER &= ~(3 << (2 * 2));   // Clear
    GPIOA->MODER |=  (2 << (2 * 2));   // AF mode
    GPIOA->AFR[0] &= ~(0xF << (4 * 2)); // Clear
    GPIOA->AFR[0] |=  (7 << (4 * 2));   // AF7 (USART2)

    // Cấu hình baudrate 9600 (giả sử clock 16MHz)
    USART2->BRR = 0x0683;

    // Bật truyền dữ liệu và USART2
    USART2->CR1 |= (1 << 3);  // TE
    USART2->CR1 |= (1 << 13); // UE
}

// ======== Gửi 1 ký tự =========
void USART2_SendChar(char c) {
    while (!(USART2->SR & (1 << 7))); // TXE
    USART2->DR = c;
}

// ======== Gửi chuỗi =========
void USART2_SendString(const char *str) {
    while (*str) {
        USART2_SendChar(*str++);
    }
}

// ======== Cấu hình PC1 làm input =========
void IR_Sensor_Init(void) {
    RCC->AHB1ENR |= (1 << 2);    // Enable GPIOC
    GPIOC->MODER &= ~(3 << (2 * 1)); // PC1 input (00)
}

int main(void) {
    USART2_Init();       // Khởi tạo UART2
    IR_Sensor_Init();    // Khởi tạo chân cảm biến IR (PC1)

    while (1) {
        if ((GPIOC->IDR & (1 << 1)) == 0) {
            USART2_SendString("IR Sensor: Object detected\r\n");
        } else {
            USART2_SendString("IR Sensor: No object\r\n");
        }

        for (volatile int i = 0; i < 2000000; i++); // Delay thô
    }
}
