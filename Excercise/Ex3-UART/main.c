#include "stm32f4xx.h"
#include <stdio.h>

void USART2_Init(void) {
    RCC->AHB1ENR |= (1 << 0);    // Enable GPIOA
    RCC->APB1ENR |= (1 << 17);   // Enable USART2

    GPIOA->MODER &= ~(3 << (2 * 2));
    GPIOA->MODER |=  (2 << (2 * 2));   // PA2: Alternate Function
    GPIOA->AFR[0] &= ~(0xF << (4 * 2));
    GPIOA->AFR[0] |=  (7 << (4 * 2));  // AF7 for USART2

    USART2->BRR = 0x0683;   // 9600 baud @16MHz
    USART2->CR1 |= (1 << 3);   // Enable transmitter
    USART2->CR1 |= (1 << 13);  // Enable USART
}

void USART2_SendChar(char c) {
    while (!(USART2->SR & (1 << 7)));
    USART2->DR = c;
}

void USART2_SendString(const char *str) {
    while (*str) {
        USART2_SendChar(*str++);
    }
}

// === Đổi sang PA1 (Channel 1) ===
void ADC1_Init(void) {
    RCC->AHB1ENR |= (1 << 0);    // Enable GPIOA
    GPIOA->MODER |= (3 << (1 * 2)); // PA1 as Analog mode (11)

    RCC->APB2ENR |= (1 << 8);    // Enable ADC1 clock

    ADC1->SQR3 = 1;   // Channel 1 (PA1)
    ADC1->SMPR2 |= (7 << 3); // Sampling time for channel 1 = 480 cycles
    ADC1->CR2 |= (1 << 0);   // Enable ADC1
}

uint16_t ADC1_Read(void) {
    ADC1->CR2 |= (1 << 30);               // Start conversion
    while (!(ADC1->SR & (1 << 1)));       // Wait until EOC
    return (uint16_t)(ADC1->DR);
}

char buffer[50];

int main(void) {
    USART2_Init();
    ADC1_Init();

    while (1) {
        uint16_t adc_value = ADC1_Read();

        sprintf(buffer, "ADC: %d\r\n", adc_value);
        USART2_SendString(buffer);

        for (volatile int i = 0; i < 300000; i++);
    }
}
