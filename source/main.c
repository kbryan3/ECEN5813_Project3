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
 * @file    main.c
 * @brief   Application entry point.
 */
#include <stdio.h>
#include <stdlib.h>

#ifndef PC
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL25Z4.h"
#include "fsl_debug_console.h"
#include "led_control.h"
#endif


#include "pattern_generator.h"
#include "memory_test.h"
#include "logger.h"
/* TODO: insert other include files here. */

/* TODO: insert other definitions and declarations here. */
const uint8_t RED = 0;
const uint8_t GREEN = 1;
const uint8_t BLUE = 2;
const uint8_t OFF = 3;
const uint8_t LENGTH = 16;
const uint8_t SEED = 29;

mem_status result = SUCCESS;
mem_status test = SUCCESS;
_Bool log_a;


uint8_t passCount = 0;

/*
 * @brief   Application entry point.
 */
int main(void) {

#ifndef PC
  	/* Init board hardware. */
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();
  	/* Init FSL debug console. */
    BOARD_InitDebugConsole();
    initializeLEDs();
    toggleLED(OFF);
#endif
    log_a = 0;



    /* Force the counter to be placed into memory. */
//    volatile static int i = 0 ;
    /* Enter an infinite loop*/
    while(1) {
    	//pointer to values of failed addresses during memory test
    	uint32_t * addressFailed_ptr = allocate_words(LENGTH);
    	uint8_t * memDisplay = (uint8_t *)allocate_words(LENGTH);
    	//start memory test, turn LED Blue
#ifndef PC
    	toggleLED(BLUE);
#endif
#ifdef DEBUG
    	log_enable();
      printf("Log Enable\n");
#else
      printf("Log Disabled\n");
#endif
//      log_string((uint8_t*)"hello world");

    	volatile static uint32_t k = 0;

    	//Allocate 16 bytes of memory
    	uint32_t * pattern_ptr = allocate_words(LENGTH);

//Write a memory pattern to the 16 byte region
    	result = write_pattern(pattern_ptr, LENGTH, SEED);
    	if(result == FAILED)
    	{
    		test = FAILED;
    	}

    	//Display region's memory pattern
        memDisplay = display_memory(pattern_ptr, LENGTH);
        if(!memDisplay)
        {
        	test = FAILED;

        	//do something with logger
        }
        else
        {
       	  log_string((uint8_t*)"Memory Region:");
        	log_data(pattern_ptr, LENGTH);


          printf("\n");

        }
        //Verify region's memory pattern
        addressFailed_ptr = verify_pattern(pattern_ptr, LENGTH, SEED);
        for(uint8_t i = 0; i<LENGTH; i++)
        {
        	if(addressFailed_ptr[i] != 0)
        	{
        		test = FAILED;
//        		PRINTF("Failure at location: 0x%X\n\r", addressFailed_ptr[i]);

        	}
        }

        printf("0xFFEE\n");
//Write 0xFFEE to a position within that region
        result = write_memory((pattern_ptr+2), 0xFF);
        if(result == FAILED)
        {
        	//print something
        }

        memDisplay = display_memory(pattern_ptr, LENGTH);
        if(!memDisplay)
        {
        	test = FAILED;
        }
        else
        {
//        	log_data(pattern_ptr, LENGTH);
        }

        //Verify pattern again
        addressFailed_ptr = verify_pattern(pattern_ptr, LENGTH, SEED);
        for(uint8_t i = 0; i<LENGTH; i++)
        {
        	if(addressFailed_ptr[i] != 0)
            {
        		passCount++;
            }
        }
        if(passCount == 0)
        {
        	test = FAILED;
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
        if(!memDisplay)
        {
        	test = FAILED;
            //do something with logger
        }
        else
        {
        	//this will be log_data function
//        	log_data(pattern_ptr, LENGTH);
        }
        //Verify pattern again
        addressFailed_ptr = verify_pattern(pattern_ptr, LENGTH, SEED);
        for(uint8_t i = 0; i<LENGTH; i++)
        {
        	if(addressFailed_ptr[i] != 0)
        	{
        		test = FAILED;
//        		PRINTF("Failure at location: 0x%X\n\r", addressFailed_ptr[i]);
        	}
        }

        printf("0xFFEE\n");
//Invert 4 bytes in the region
       result = invert_block((pattern_ptr+1), 4);
       if(result == FAILED)
       {
    	   test = FAILED;
    	   //do something with logger
       }
       //display memory in the region
       memDisplay = display_memory(pattern_ptr, LENGTH);
       if(!memDisplay)
       {
       	test = FAILED;
           //do something with logger
       }
       else
       {
//    	   log_data(pattern_ptr, LENGTH);
       }
       //Verify pattern again
       addressFailed_ptr = verify_pattern(pattern_ptr, LENGTH, SEED);
       for(uint8_t i = 0; i<LENGTH; i++)
       {
       	if(addressFailed_ptr[i] != 0)
           {
       		passCount++;
           }
       }
       if(passCount == 0)
       {
       	test = FAILED;
       }
       else
       {
       	passCount = 0;
       }

       printf("0xFFEE\n");
 //Invert those 4 bytes again in the LMA region
       result = invert_block((pattern_ptr+1), 4);
       if(result == FAILED)
       {
    	   test = FAILED;
    	   //do something with logger
       }
       //display memory in the region
       memDisplay = display_memory(pattern_ptr, LENGTH);
       if(!memDisplay)
       {
       	test = FAILED;
           //do something with logger
       }
       else
       {
       	//this will be log_data function
//    	   log_data(pattern_ptr, LENGTH);
       }
       //Verify pattern again
       addressFailed_ptr = verify_pattern(pattern_ptr, LENGTH, SEED);
       for(uint8_t i = 0; i<LENGTH; i++)
       {
    	   if(addressFailed_ptr[i] != 0)
    	   {
    		   test = FAILED;
//    		   PRINTF("Failure at location: 0x%X\n\r", addressFailed_ptr[i]);
    	   }
       }

//Free the 16 byte allocated region
       printf("0xFFEE\n");
       free_words(pattern_ptr);
       printf("0xFFEE\n");


//toggle LED to Green(pass) or Red(Fail) based on result of memory test
#ifndef PC
        if(!test)
        {
        	toggleLED(GREEN);
       	}
        else
       	{
       		toggleLED(RED);
       	}
#endif
        while(1)
        {
        	k++;

            /* 'Dummy' NOP to allow source level single stepping of
                tight while() loop */
            __asm volatile ("nop");
        }



    }
    return 0 ;
}
