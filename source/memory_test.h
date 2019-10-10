 /********************************************************************
*
* @file memory_test.h
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
#ifndef __MEMORY_TEST_H__
#define __MEMORY_TEST_H__

#include <stdint.h>
#include <stdlib.h>

#include "fsl_debug_console.h"

typedef enum mem_status
{
	SUCCESS = 0, //no error
	FAILED       //failure case

}mem_status;


uint32_t * allocate_words(size_t length);
void free_words(uint32_t *src);
uint8_t * display_memory(uint32_t *loc, size_t length);
mem_status write_memory(uint32_t *loc, uint8_t value);
mem_status invert_block(uint32_t * loc, size_t length);

#endif /* __MEMORY_TEST_H__ */
