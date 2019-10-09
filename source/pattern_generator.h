 /********************************************************************
*
* @file pattern_generator.c
* @brief Generates a random byte array
*
* Contains a gen_patter function that generates a byte array based
*  on a given seed value.
*
*
* @author Kyle Bryan
* @date October 2019
* version 1.0
*
***********************************************************************/



#include <stdint.h>
#include <stdlib.h>

/**
* @brief Generates a pattern of bytes based off a given seed value
*
* This function creates an array of bytes whose value is based on a given
* seed value and whose length is based on a given length in bytes
*
* @param uint8_t *pattern a pointer to a byte array where a pattern is
*                           written
* @param size_t length	number of bytes the pattern should be
* @param uint8_t seed    value used to randomize the pattern
*
*@return void
*/
void gen_pattern(uint8_t *pattern, size_t length, uint8_t seed);

