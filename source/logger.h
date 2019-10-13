 /********************************************************************
*
* @file logger.h
* @brief Contains multiple functions to log/print debug info and data
*
*
*
*
* @author Kyle Bryan
* @date October 2019
* version 1.0
*
***********************************************************************/
#ifndef __LOGGER_H__
#define __LOGGER_H__


#include <stdint.h>
#include <stdlib.h>

typedef enum logger_status
{
	DISABLED,    //logger is off
	ENABLED      //logger is on

}logger_status;

extern logger_status log;


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
void log_enable();
void log_disable();
_Bool log_status();
void log_data();
void log_string(uint8_t * string);
void log_integer(uint32_t * integer);



#endif /* __LOGGER_H__ */

