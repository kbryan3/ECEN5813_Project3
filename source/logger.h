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

typedef enum log_status
{
	OFF = 0,    //logger is off
	ON = 1      //logger is on

}log_status;

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
_BOOL log_status();
void log_data();



#endif /* __LOGGER_H__ */

