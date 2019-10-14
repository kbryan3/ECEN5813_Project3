 /********************************************************************
*
* @file logger.c
* @brief Contains functions to log and print data
*
*
*
*
* @author Kyle Bryan
* @date October 2019
* version 1.0
*
***********************************************************************/
#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL25Z4.h"
#include "fsl_debug_console.h"
#include "logger.h"


void log_enable()
{
	log_a = 1;
}

void log_disable()
{
	log_a = 0;
}


_Bool log_status()
{
	if(log_a)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}


void log_data(uint32_t * loc, size_t length)
{
	if(log_a)
	{
		uint8_t * bytes_ptr = (uint8_t *)loc;

		for(uint8_t i = 0; i<length; i++)
		{
			PRINTF("Address: 0x%X    Data: 0x%02X\n\r", bytes_ptr+i, bytes_ptr[i]);
		}

		PRINTF("\n\r");
	}

}

void log_string(uint8_t * str)
{
	if(log_a)
	{
		PRINTF("%s", str);
	}
}

void log_int(uint32_t * integer)
{
	if(log_a)
	{
		PRINTF("%d", integer);
		PRINTF("\n\r");
	}

}

