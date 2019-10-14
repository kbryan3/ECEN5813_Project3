 /********************************************************************
*
* @file memory_test.h
* @brief Contains functions for testing memory
*
* Contains fucntions for allocating, clearing, reading, modifying,
*  and testing memory
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
#include <string.h>

#ifndef PC
#include "fsl_debug_console.h"
#endif

typedef enum mem_status
{
	SUCCESS = 0, //no error
	FAILED       //failure case

}mem_status;

/**
* @brief Allocates memory
*
* Allocates a block of memory based on a given number of bytes
*
* @param size_t length	number of bytes the pattern should be
*
*@return uint32_t * a pointer to the beginning of the memory block
*/
uint32_t * allocate_words(size_t length);

/**
* @brief Frees memory space
*
* Frees block of memory that has been allocated previously
*
* @param uint32_t * pointer to beginning of block of memory
*
*@return void
*/
void free_words(uint32_t *src);

/**
* @brief Returns a pointer to a block of memory
*
* Returns a pointer to a portion of allocated memory
*
* @param uint32_t* loc pointer to beginning of block of memory
* @param size_t length number of bytes from the base pointer address
*
* @return uint8_t * pointer to the bytes chosen by the caller of function
*/
uint8_t * display_memory(uint32_t *loc, size_t length);

/**
* @brief Writes a specified byte to memory
*
* Given a location and an 8 bit value, this funciton writes the byte to the
* specified memory address
*
* @param uint32_t* loc pointer to memory location
* @param uint8_t value value to write to memory location
*
* @return mem_status whether the function SUCCESS/FAILED
*/
mem_status write_memory(uint32_t *loc, uint8_t value);

/**
* @brief Inverts a block of memory
*
* Given a starting location and number of bytes this function inverts then
* specified number of bytes
*
* @param uint32_t* loc pointer to memory location
* @param size_t length number of bytes to invert
*
* @return mem_status whether the function SUCCESS/FAILED
*/
mem_status invert_block(uint32_t * loc, size_t length);

/**
* @brief Writes a specified pattern to memory
*
* Fucntion writes a pattern based on seed valuethat is of size(num bytes)
* length to a specified base address
*
* @param uint32_t* loc pointer to memory location
* @param size_t length length of pattern in bytes
* @param uint8_t seed seed value for pattern generator
*
* @return mem_status whether the function SUCCESS/FAILED
*/
mem_status write_pattern(uint32_t * loc, size_t length, uint8_t seed);

/**
* @brief Verifies a memory pattern is correct
*
* Fucntion verifies memory contains the correct pattern based on seed value
* that is of size(num bytes) length to a specified base address
*
* @param uint32_t* loc pointer to memory location
* @param size_t length length of pattern in bytes
* @param uint8_t seed seed value for pattern generator
*
* @return uint32_t * list of addresses where the pattern has failed
*/
uint32_t * verify_pattern(uint32_t * loc, size_t length, uint8_t seed);

#endif /* __MEMORY_TEST_H__ */
