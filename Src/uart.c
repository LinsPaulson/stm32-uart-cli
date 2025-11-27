#include "uart.h"
#include "stm32f0xx.h"

#define UART2_BAUDRATE		9600
#define SYS_FREQ			8000000
#define APB1_CLK			SYS_FREQ

void uart_init(void)
{
	// Enable clock access to GPIOA
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN;

	// Set the mode of PA2 and PA3 to alternate function mode
	GPIOA->MODER |= (1U << 7);
	GPIOA->MODER &= ~(1U << 6);
	GPIOA->MODER |= (1U << 5);
	GPIOA->MODER &= ~(1U << 4);

	// Set alternate function type to AF1(UART2_RX)
	GPIOA->AFR[0] &= ~(1U << 15);
	GPIOA->AFR[0] &= ~(1U << 14);
	GPIOA->AFR[0] &= ~(1U << 13);
	GPIOA->AFR[0] |= (1U << 12);

	// Set alternate function type to AF1(UART2_TX)
	GPIOA->AFR[0] &= ~(1U << 11);
	GPIOA->AFR[0] &= ~(1U << 10);
	GPIOA->AFR[0] &= ~(1U << 9);
	GPIOA->AFR[0] |= (1U << 8);

	// Enable clock access to UART2
	RCC->APB1ENR |= RCC_APB1ENR_USART2EN;

	// Configure UART baudrate
	uint32_t tmp = (APB1_CLK * 100) / (16U * UART2_BAUDRATE); // 5208
	uint32_t mantissa = tmp / 100U; // 52
	uint32_t fractional = ((tmp - (mantissa * 100U)) * 16U) / 100U; // ((5208 - 5200) * 16) / 100 = 1
	USART2->BRR = (mantissa << 4) | (fractional & 0x0F); //

	// Configure transfer direction
	USART2->CR1 |= USART_CR1_TE;
	USART2->CR1 |= USART_CR1_RE;

	// Enable UART Module
	USART2->CR1 |= USART_CR1_UE;
}

void uart_write(uint8_t ch)
{
	// Make sure transmit data register is empty
	while (!(USART2->ISR & USART_ISR_TXE ));

	// Write to transmit data register
	USART2->TDR = ch;
}

uint8_t uart_read(void)
{
	// wait until data is received
	while (!(USART2->ISR & USART_ISR_RXNE));

	// Read from receive data register
	return (uint8_t)(USART2->RDR & 0xFF);
}

void uart_print(const char *str)
{
	while (*str) uart_write((uint8_t)*str++);
}








