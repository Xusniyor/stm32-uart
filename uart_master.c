#include "uart_master.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "fifo.h"

uart_t myuart;

int _lastindex, _newindex, _uartsize;

uint16_t uart_write(uart_t *s_uart, const uint8_t *buf, uint16_t size)
{
    return fifo_write(&s_uart->txfifo, buf, size);
}

void uart_init(uart_t *s_uart, UART_HandleTypeDef *huart, void *fun)
{
    memset(s_uart, 0, sizeof(uart_t));
    s_uart->callback = fun;
    s_uart->usart = huart;
    HAL_UART_Receive_DMA(s_uart->usart, s_uart->dmarxbuf, sizeof(s_uart->dmarxbuf));
    fifo_register(&s_uart->txfifo, &s_uart->txBuffer[0], sizeof(s_uart->txBuffer), NULL, NULL);
}

void uart_loop(uart_t *s_uart)
{
    _lastindex = _newindex = sizeof(s_uart->dmarxbuf) - __HAL_DMA_GET_COUNTER(s_uart->usart->hdmarx);
    if (_newindex > 0)
    {
        uart_delay(2);
        _newindex = sizeof(s_uart->dmarxbuf) - __HAL_DMA_GET_COUNTER(s_uart->usart->hdmarx);
        if (_lastindex == _newindex)
        {
            s_uart->rxIndex = _newindex;
            memset(s_uart->rxBuffer, 0, sizeof(s_uart->rxBuffer));
            HAL_UART_AbortReceive(s_uart->usart);
            memcpy(s_uart->rxBuffer, s_uart->dmarxbuf, s_uart->rxIndex);
            HAL_UART_Receive_DMA(s_uart->usart, s_uart->dmarxbuf, sizeof(s_uart->dmarxbuf));
            if (s_uart->callback != NULL)
            {
                s_uart->callback(s_uart->rxBuffer, s_uart->rxIndex);
            }
        }
    }
    if (HAL_UART_GetState(s_uart->usart) != HAL_UART_STATE_BUSY_TX)
    {
        s_uart->txIndex = fifo_read(&s_uart->txfifo, s_uart->dmatxbuf, sizeof(s_uart->dmatxbuf));
        if (s_uart->txIndex > 0)
        {
            HAL_UART_Transmit_DMA(s_uart->usart, s_uart->dmatxbuf, s_uart->txIndex);
        }
    }
}