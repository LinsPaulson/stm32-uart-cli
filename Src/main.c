#include "uart.h"
#include <string.h>
#include <stdlib.h>

#define MAX_CMD_LED 64

static uint32_t sampling_freq = 1;

int main(void)
{
	uint8_t cmd_buffer[MAX_CMD_LED];
	uint8_t index = 0;

	uart_init();
	uart_print("Serial Command Interface ready!\r\n");

	while(1)
	{
		// Read one character from UART
		uint8_t ch = uart_read();

		if (ch == '\n' || ch == '\r')
		{
			// Null-terminate the received command
			cmd_buffer[index] = '\0';

			// Handle *SET_FREQ <value>" command
			if (strncmp((const char *)cmd_buffer, "SET_FREQ ", 9) == 0)
			{
				// Parse frequency value
				int freq = atoi((const char *)&cmd_buffer[9]);
				if (freq > 0)
				{
					// Update sampling frequency
					sampling_freq = freq;
					uart_print("OK: Frequency set to ");
					char num[10];
					itoa(sampling_freq, num, 10);
					uart_print(num);
					uart_print(" Hz\n\r");
				}
				else
				{
					uart_print("ERROR: Invalid frequency\n\r");
				}
			}
			// Handle "GET STATUS" command
			else if (strcmp((const char *)cmd_buffer, "GET_STATUS") == 0)
			{
				uart_print("STATUS OK, FREQ=");
				char num[10];
				itoa(sampling_freq, num, 10);
				uart_print(num);
				uart_print("\n\r");
			}
			// Unknown command
			else
			{
				uart_print("ERROR: Unknown command\n\r");
			}
			// Reset buffer index after processing
			index = 0;
		}
		else if (index < MAX_CMD_LED - 1)
		{
			// Append character to command buffer
			cmd_buffer[index++] = ch;
		}
		else
		{
			// Reset on overflow
			index = 0;
			uart_print("ERROR: Command too log\n\r");
		}
	}
}
