/*
 * fpu.c
 *
 *  Created on: May 31, 2023
 *      Author: josep
 */

#include <stdio.h>
#include <stdint.h>
#include "stm32f4xx.h"
#include "stm32f411xe.h"
void fpu_enable(void);       /* also in fpu.h */


void fpu_enable(){
	SCB->CPACR |=(1<<20);    /* setup floating point */
	SCB->CPACR |=(1<<21);    /* CPACR is Coprocessor Access Control Register */
	SCB->CPACR |=(1<<22);    /* pg 4-48 page 4-52  Cortex M4 User Guide */
	SCB->CPACR |=(1<<23);    /*  SCB macro found in core_cm4.h file */
}
