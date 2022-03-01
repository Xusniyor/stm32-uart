#ifndef __UART_MASTER_H__
#define __UART_MASTER_H__

#include "uart_config.h"
#include "fifo.h"
#include "main.h"
#include "usart.h"

#if (_UART_RTOS == 0)
#define uart_delay(x)  HAL_Delay(x)
#else
#include "cmsis_os.h"
#define uart_delay(x)  osDelay(x)
#endif

typedef struct
{
  uint8_t dmarxbuf[_UART_RXSIZE];
  uint8_t dmatxbuf[_UART_TXSIZE];
  uint8_t rxBuffer[_UART_RXSIZE];
  uint8_t txBuffer[_UART_TXSIZE];
  uint32_t rxIndex;
  uint32_t txIndex;
  _fifo_t txfifo;
  UART_HandleTypeDef *usart;
  void (*callback)(uint8_t *buf, uint32_t len);
} uart_t;

extern uart_t myuart;

void     uart_init (uart_t *s_uart, UART_HandleTypeDef *huart, void *fun);
uint16_t uart_write(uart_t *s_uart, const uint8_t *buf, uint16_t size);
void     uart_loop (uart_t *s_uart);

#endif /* __UART_MASTER_H__ */