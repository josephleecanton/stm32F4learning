

#include <stdio.h>
#include <stdint.h>
#include "stm32f4xx.h"
#include "stm32f411xe.h"

#include "fpu.c"
#include "uart.h"






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

 	uart_init();


		 while(1){
			 printf("Frank5 says Hello from Stm32\n\r");
		 }

	}





