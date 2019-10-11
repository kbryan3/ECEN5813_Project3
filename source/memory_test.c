 /********************************************************************
*
* @file memory_test.c
* @brief Contains functions for testing memory
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
#include "memory_test.h"
#include "pattern_generator.h"

uint32_t * allocate_words(size_t length)
{
	uint32_t* memory_ptr = (uint32_t*)malloc(length*sizeof(uint8_t));

	return memory_ptr;

}

void free_words(uint32_t * src)
{
	if(! src)
	{
		PRINTF("No memory allocated\n\r");
	}
	free(src);
}

uint8_t * display_memory(uint32_t * loc, size_t length)
{
	uint8_t * memory_ptr=(uint8_t*)malloc(length);
	memcpy(memory_ptr, loc, length);

	return memory_ptr;

}

mem_status write_memory(uint32_t * loc, uint8_t value)
{
	if(!loc)
	{
		return FAILED;
	}
	else
	{
		uint8_t * byteAddress_ptr = (uint8_t *)loc;
		*byteAddress_ptr = value;
		return SUCCESS;
	}
}

mem_status invert_block(uint32_t * loc, size_t length)
{
	if(!loc)
	{
		return FAILED;
	}
	else
	{
		uint8_t * byteAddress_ptr = (uint8_t *) loc;
		for(uint8_t i = 0; i < length; i++)
		{
			byteAddress_ptr[i] ^= 0b11111111;
		}
		return SUCCESS;
	}
}

mem_status write_pattern(uint32_t *loc, size_t length, int8_t seed)
{

	if(! loc)
	{
		return FAILED;
	}
	else
	{
		uint8_t * byteAddress_ptr = (uint8_t *) loc;
		gen_pattern(byteAddress_ptr, length, seed);
		return SUCCESS;
	}
}


