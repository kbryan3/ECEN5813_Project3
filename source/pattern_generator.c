 /********************************************************************
*
* @file pattern_generator.h
* @brief Generates a random byte array
*
* Contains a gen_pattern function that generates a byte array based
*  on a given seed value.
*
*
* @author Kyle Bryan
* @date October 2019
* version 1.0
*
***********************************************************************/

#include "pattern_generator.h"

void gen_pattern(uint8_t *pattern, size_t length, uint8_t seed)
{
	for(uint8_t i = 0; i<length; i++)
		{
	        //arbitrary calculation of each byte based on a given seed value
			pattern[i] = (uint8_t)(seed*i+0x23);
		}
}
