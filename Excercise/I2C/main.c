#include "stm32f4xx.h"
#include <stdint.h>

// ===== Font 5x7: H, I, space, M, A, N =====
const uint8_t Font5x7[][5] = {
    {0x7F, 0x08, 0x08, 0x08, 0x7F}, // H - 0
    {0x00, 0x41, 0x7F, 0x41, 0x00}, // I - 1
    {0x00, 0x00, 0x00, 0x00, 0x00}, // SPACE - 2
    {0x7F, 0x06, 0x18, 0x06, 0x7F}, // M - 3
    {0x7E, 0x11, 0x11, 0x11, 0x7E}, // A - 4
    {0x7F, 0x04, 0x08, 0x10, 0x7F}  // N - 5
};

void I2C1_Init(void) {
    // 1. Enable clock for GPIOB and I2C1
    RCC->AHB1ENR |= (1 << 1);   // Enable GPIOBEN = bit 1
    RCC->APB1ENR |= (1 << 21);  // Enable I2C1EN  = bit 21

    // 2. Configure PB8 and PB9 as Alternate Function
    GPIOB->MODER &= ~((3 << 16) | (3 << 18));  // Clear mode bits for PB8, PB9
    GPIOB->MODER |=  (2 << 16) | (2 << 18);    // Set alternate function mode (10)

    GPIOB->OTYPER |= (1 << 8) | (1 << 9);      // Open-drain output

    GPIOB->OSPEEDR |= (3 << 16) | (3 << 18);   // High speed

    GPIOB->PUPDR &= ~((3 << 16) | (3 << 18));  // Clear pull-up/pull-down
    GPIOB->PUPDR |=  (1 << 16) | (1 << 18);    // Enable pull-up (01)

    GPIOB->AFR[1] &= ~((15 << 0) | (15 << 4)); // Clear AF for PB8, PB9 (each 4-bit field)
    GPIOB->AFR[1] |=  (4 << 0) | (4 << 4);     // AF4 for I2C1 (AF=0100)

    // 3. Reset I2C1
    I2C1->CR1 = (1 << 15);  // SWRST = bit 15
    I2C1->CR1 = 0;

    // 4. Set frequency = 42MHz (PCLK1)
    I2C1->CR2 = 42;

    // 5. Set clock control register for 100kHz I2C: CCR = PCLK1 / (2 * Freq)
    I2C1->CCR = 210;        // 42MHz / (2 * 100kHz)

    // 6. Set TRISE = PCLK1 + 1
    I2C1->TRISE = 43;

    // 7. Enable I2C
    I2C1->CR1 |= 1;  // PE bit = 1
}

#define SSD1306_ADDR 0x78  // Địa chỉ I2C

void SSD1306_Send(uint8_t control, uint8_t *data, uint16_t size) {
    I2C1->CR1 |= 1 << 8;  // START bit (bit 8)
    while (!(I2C1->SR1 & (1 << 0)));  // SB bit

    I2C1->DR = SSD1306_ADDR;  // Send address
    while (!(I2C1->SR1 & (1 << 1)));  // ADDR bit
    (void)I2C1->SR2;  // Clear ADDR by reading SR2

    while (!(I2C1->SR1 & (1 << 7)));  // TXE
    I2C1->DR = control;

    for (int i = 0; i < size; i++) {
        while (!(I2C1->SR1 & (1 << 7)));  // TXE
        I2C1->DR = data[i];
    }

    while (!(I2C1->SR1 & (1 << 2)));  // BTF
    I2C1->CR1 |= 1 << 9;  // STOP bit
}

void SSD1306_Init(void) {
    uint8_t cmds[] = {
        0xAE, 0x20, 0x00, 0xB0, 0xC8,
        0x00, 0x10, 0x40, 0x81, 0x7F,
        0xA1, 0xA6, 0xA8, 0x3F, 0xA4,
        0xD3, 0x00, 0xD5, 0xF0, 0xD9,
        0x22, 0xDA, 0x12, 0xDB, 0x20,
        0x8D, 0x14, 0xAF
    };
    SSD1306_Send(0x00, cmds, sizeof(cmds));
}

void SSD1306_Clear(void) {
    uint8_t zero[128] = {0};
    for (uint8_t page = 0; page < 8; page++) {
        uint8_t cmd[] = {0x21, 0, 127, 0x22, page, page};
        SSD1306_Send(0x00, cmd, sizeof(cmd));
        SSD1306_Send(0x40, zero, 128);
    }
}

void SSD1306_DrawChar(uint8_t col, uint8_t page, const uint8_t *bitmap) {
    uint8_t cmd[] = {
        0x21, col, col + 4,
        0x22, page, page
    };
    SSD1306_Send(0x00, cmd, sizeof(cmd));
    SSD1306_Send(0x40, (uint8_t*)bitmap, 5);
}

void delay_ms(uint32_t ms) {
    for (uint32_t i = 0; i < ms * 4000; i++) {
        __NOP();
    }
}

int main(void) {
    I2C1_Init();
    delay_ms(100);
    SSD1306_Init();
    delay_ms(100);
    SSD1306_Clear();

    // Chuỗi: H I SPACE M A N H
    const uint8_t *hi_manh[] = {
        Font5x7[0], // H
        Font5x7[1], // I
        Font5x7[2], // SPACE
        Font5x7[3], // M
        Font5x7[4], // A
        Font5x7[5], // N
        Font5x7[0]  // H
    };

    uint8_t col = 0;
    for (int i = 0; i < 7; i++) {
        SSD1306_DrawChar(col, 0, hi_manh[i]);
        col += 6;
    }

    while (1);
}
