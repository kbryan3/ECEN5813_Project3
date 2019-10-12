/*
 * Copyright 2016-2019 NXP
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of NXP Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
 
/**
 * @file    project3.c
 * @brief   Application entry point.
 */
#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL25Z4.h"
#include "fsl_debug_console.h"

#include "led_control.h"
#include "pattern_generator.h"
#include "memory_test.h"
/* TODO: insert other include files here. */

/* TODO: insert other definitions and declarations here. */
const uint8_t RED = 0;
const uint8_t GREEN = 1;
const uint8_t BLUE = 2;
const uint8_t OFF = 3;
const size_t LENGTH = 16;
const uint8_t SEED = 29;

mem_status result = SUCCESS;
mem_status test = SUCCESS;

uint8_t passCount = 0;

void delay(volatile int32_t number)
{
	while(number !=0)
	{
		__asm volatile("nop");
		number--;
	}
}
/*
 * @brief   Application entry point.
 */
int main(void) {

  	/* Init board hardware. */
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();
  	/* Init FSL debug console. */
    BOARD_InitDebugConsole();
    initializeLEDs();
    toggleLED(OFF);


    /* Force the counter to be placed into memory. */
    volatile static int i = 0 ;
    /* Enter an infinite loop*/
    while(1) {
    	//pointer to values of failed addresses during memory test
    	uint32_t * addressFailed_ptr = allocate_words(LENGTH);
    	uint8_t * memDisplay = allocate_words(LENGTH);
    	//start memory test, turn LED Blue
    	toggleLED(BLUE);

    	//Allocate 16 bytes of memory
    	uint32_t * pattern_ptr = allocate_words(LENGTH);

    	//Write a memory pattern to the 16 byte region
    	result = write_pattern(pattern_ptr, LENGTH, SEED);
    	if(result == FAILED)
    	{
    		test = FAILED;
    		//do something with logger
    	}
    	//Display region's memory pattern
        memDisplay = display_memory(pattern_ptr, LENGTH);
        if(result == FAILED)
        {
        	test = FAILED;
        	//do something with logger
        }
        else
        {
        	//this will be log_data function
        	for(uint8_t i = 0; i<LENGTH; i++)
        	{
        		PRINTF("%X", memDisplay[i]);
        	}
        	PRINTF("/n/r");
        }
        //Verify region's memory pattern
        addressFailed_ptr = verify_pattern(pattern_ptr, LENGTH, seed);
        for(uint8 i = 0; i<LENGTH; i++)
        {
        	if(*addressFailed_ptr != 0)
        	{
        		test = FAILED;
        		PRINTF("Failure at location: 0x%X\n\r", *addressFailed_ptr);
        	}
        }


        //Write 0xFFEE to a position within that region
        result = write_memory((pattern_ptr+2), 0xFF);
        if(result == FAILED)
        {
        	//print something
        }
        else
        {
        	//this will be log_data function
        	for(uint8_t i = 0; i<LENGTH; i++)
        	{
        		PRINTF("%X", memDisplay[i]);
        	}
        	PRINTF("/n/r");
        }

        //Verify pattern again
        addressFailed_ptr = verify_pattern(pattern_ptr, LENGTH, seed);
        for(uint8 i = 0; i<LENGTH; i++)
        {
        	if(*addressFailed_ptr != 0)
            {
        		passCount++;
            }
        }
        if(passCount == 0)
        {
        	test = FAILED;
            //this will be log_data function
            for(uint8_t i = 0; i<LENGTH; i++)
            {
               	PRINTF("%X", memDisplay[i]);
            }
            PRINTF("/n/r");
        }
        else
        {
        	passCount = 0;
        }


        //write memory pattern to region using same seed and display it
        result = write_pattern(pattern_ptr, LENGTH, SEED);
        if(result == FAILED)
      	{
        	test = FAILED;
        	//do something with logger
        }
        //Display region's memory pattern
        memDisplay = display_memory(pattern_ptr, LENGTH);
        if(result == FAILED)
        {
        	test = FAILED;
            //do something with logger
        }
        else
        {
        	//this will be log_data function
            for(uint8_t i = 0; i<LENGTH; i++)
            {
            	PRINTF("%X", memDisplay[i]);
            }
               	PRINTF("/n/r");
        }
        //Verify pattern again
        addressFailed_ptr = verify_pattern(pattern_ptr, LENGTH, seed);
        for(uint8 i = 0; i<LENGTH; i++)
        {
        	if(*addressFailed_ptr != 0)
        	{
        		test = FAILED;
        		PRINTF("Failure at location: 0x%X\n\r", *addressFailed_ptr);
        	}
        }

        //Invert 4 bytes in the region
        result = invert_block((address_ptr+1), 3);



        /* 'Dummy' NOP to allow source level single stepping of
            tight while() loop */
        __asm volatile ("nop");
    }
    return 0 ;
}
