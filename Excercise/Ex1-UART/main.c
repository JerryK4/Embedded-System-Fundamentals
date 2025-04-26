#include "stm32f4xx.h"

void USART2_Init(void) {
    // Step 1: Enable clocks
    RCC->AHB1ENR |= (1 << 0);    // Enable GPIOA clock
    RCC->APB1ENR |= (1 << 17);   // Enable USART2 clock

    // Step 2: Configure PA2 (TX) as Alternate Function
    GPIOA->MODER &= ~(3 << 4);         // Clear bits for PA2
    GPIOA->MODER |= (2 << 4);          // Set PA2 to Alternate Function (10)
    GPIOA->AFR[0] &= ~(0xF << 8);      // Clear AF bits for PA2
    GPIOA->AFR[0] |= (7 << 8);         // Set AF7 (USART2_TX) for PA2

    // Step 3: Configure USART2
    USART2->BRR = 0x0683;              // Baud rate 9600 for 16MHz clock
    USART2->CR1 |= (1 << 3);           // Enable transmitter (TE)
    USART2->CR1 |= (1 << 13);          // Enable USART2 (UE)
}

void USART2_SendChar(char c) {
    while (!(USART2->SR & (1 << 7)));  // Wait until TXE is set
    USART2->DR = c;                    // Write data to send
}

void USART2_SendString(const char *str) {
    while (*str) {
        USART2_SendChar(*str++);      // Send each character
    }
}

int main(void) {
    USART2_Init();                      // Initialize USART2
    USART2_SendString("Hello Stm32\r\n"); // Transmit a string
    while (1);
}
