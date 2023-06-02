

#include <stdio.h>
#include <stdint.h>
#include "stm32f4xx.h"
#include "stm32f411xe.h"

#include "fpu.c"






uint16_t compute_baud_rate_div(uint32_t periph_clk,uint32_t baudrate);
void set_baudrate_div(uint32_t periph_clk,uint32_t baudrate);
void uart_write(int ch);

int __io_putchar(int ch){
	uart_write(ch);
	return ch;
}

/*
 * Printf with  USART2  with GPIO PA2 pin for transmit (AF7)
 */


int main(void){
 	SCB->CPACR |=(1<<20);    /* setup floating point */
 	SCB->CPACR |=(1<<21);    /* CPACR is Coprocessor Access Control Register */
 	SCB->CPACR |=(1<<22);    /* pg 4-48 page 4-52  Cortex M4 User Guide */
 	SCB->CPACR |=(1<<23);    /*  SCB macro found in core_cm4.h file */



		RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN; /* Enable clock access for GPIOA */


//		GPIOA->MODER |= (1U<<5);    /* set high bit as "1" */
//		GPIOA->MODER &=~ (1U<<4);   /* &=~ is disable operator sets low bit to 0 */
		GPIOA->MODER |=  GPIO_MODER_MODER2_1;   /* set high bit as "1" */
		GPIOA->MODER &=~  GPIO_MODER_MODER2_0;    /* set low bit to "0"  10 is AF mode*/

		/* set alternate function type to AF7 */
		GPIOA->AFR[0] |=(1U<<8);
		GPIOA->AFR[0] |=(1U<<9);
		GPIOA->AFR[0] |=(1U<<10);
		GPIOA->AFR[0] &=~(1U<<11);

	  /* enable clock access to uart2 module */
	   RCC->APB1ENR |= RCC_APB1ENR_USART2EN;

	   /* config UART2 baud rate */

	   set_baudrate_div(16000000 , 57600);



	  /* configure transfer direction */

	  USART2->CR1 =  0UL;   /* ? reset - should I do this or just stop TX ?*/
	  USART2->CR2 =  0UL;   /* ?reset should I do this or just stop TX */




      /*8-N-1  8 data bits, 1 start bit , 1 stop , no parity */
      /* hint: hover over macro, also these macros are in CMSIS drivers */
	  USART2->CR1 |=~  USART_CR1_M ;    /* set 1 Start bit, 8 Data bits pg550 */
      USART2->CR1 |=~  USART_CR1_PCE;   /* disable parity pg pg 551 */
      USART2->CR2 |=~  USART_CR2_STOP;  /* set 1 Stop Bit  pg 553*/

      USART2->CR1 |= USART_CR1_UE;        /* enable USART    */
      USART2->CR1 |= USART_CR1_TE;        /* ENABLE transmit */



		 while(1){
			 printf("Frank4 says Hello from Stm32\n\r");
		 }

	}


void uart_write(int ch){
	 while(!(USART2->SR & USART_SR_TXE)){} /* loop here until data transmit reg empty */
	 USART2->DR = (ch & 0xFF); /* ?? */
	}

uint16_t compute_baud_rate_div(uint32_t periph_clk,uint32_t baudrate){
	return     (   (   periph_clk + (baudrate/2U)  )/baudrate);  /*   ???? */
}

void set_baudrate_div(uint32_t periph_clk,uint32_t baudrate){
  	 USART2->BRR = compute_baud_rate_div(periph_clk,baudrate);
}


