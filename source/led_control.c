 /********************************************************************
*
* @file led.c
* @brief Has functions to initialize LEDs as well as turn them on and off
*
* This module has functions that can be called to initialize and toggle LEDs
*
*
* @author Kyle Bryan
* @date October 2019
* version 1.0
*
***********************************************************************/
#include <stdint.h>
#ifndef PC
#include "led_control.h"
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL25Z4.h"
#include "fsl_debug_console.h"
#endif





void initializeLEDs()
{
	LED_BLUE_INIT(1);
	LED_RED_INIT(1);
	LED_GREEN_INIT(1);
}

//toggles LED: 0 red, 1 green, 2 blue
void toggleLED(uint8_t ledColor)
{
	if(ledColor == 0)
	{
		LED_GREEN_OFF();
		LED_BLUE_OFF();
		LED_RED_ON();
	}
	else if(ledColor == 1)
	{
		LED_RED_OFF();
		LED_BLUE_OFF();
		LED_GREEN_ON();
	}
	else if(ledColor == 2)
	{
		LED_GREEN_OFF();
		LED_RED_OFF();
		LED_BLUE_ON();
	}
	else
	{
		LED_GREEN_OFF();
		LED_BLUE_OFF();
		LED_RED_OFF();
	}

}
