# stm32-uart
STM32 DMA FIFO

* file main.c   
```
#include "uart_master.h"

void read_data(uint8_t *data, uint32_t len)
{
	uart_write(&myuart, data, len);
}

int main()
{
	MX_DMA_Init();
	MX_USART2_UART_Init();
	uart_init(&myuart, &huart2, read_data);
	uart_write(&myuart, (uint8_t *)"Salom Dunyo 0\r\n", 15);
	uart_write(&myuart, (uint8_t *)"Salom Dunyo 1\r\n", 15);
	uart_write(&myuart, (uint8_t *)"Salom Dunyo 2\r\n", 15);
	uart_write(&myuart, (uint8_t *)"Salom Dunyo 3\r\n", 15);
	uart_write(&myuart, (uint8_t *)"Salom Dunyo 4\r\n", 15);
	uart_write(&myuart, (uint8_t *)"Salom Dunyo 5\r\n", 15);
	uart_write(&myuart, (uint8_t *)"Salom Dunyo 6\r\n", 15);
	uart_write(&myuart, (uint8_t *)"Salom Dunyo 7\r\n", 15);
	uart_write(&myuart, (uint8_t *)"Salom Dunyo 8\r\n", 15);
	uart_write(&myuart, (uint8_t *)"Salom Dunyo 9\r\n", 15);
	while (1)
	{
		uart_loop(&myuart);
	}  
}
```

