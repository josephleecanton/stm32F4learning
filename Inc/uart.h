/*
 * uart.h
 *
 *  Created on: May 31, 2023
 *      Author: josep
 */

#ifndef UART_H_
#define UART_H_



#endif /* UART_H_ */

static uint16_t compute_baud_rate(uint32_t periph_clk,uint32_t baudrate);
static void set_baudrate(uint32_t periph_clk,uint32_t baudrate);
static void uart_write(int ch);
