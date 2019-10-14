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

extern _Bool log_a;


/**
* @brief Enables logger
*
* When called the logger is enabled
*
*@return void
*/
void log_enable();

/**
* @brief Disables logger
*
* When called the logger is disabled
*
*@return void
*/
void log_disable();

/**
* @brief Gives logger status
*
* When called the status(Enabled/Disabled) is returned
*
*@return _Bool Whether the logger is enabled(TRUE) or disabled(FALSE)
*/
_Bool log_status();

/**
* @brief Prints data in memory_ptr
*
* Given a base address and number of bytes the memory region is printed
*
* @param uint32_t * loc base address for region to display
* @param size_t length number of bytes to display
* @return void
*/
void log_data(uint32_t * loc, size_t length);

/**
* @brief Prints a given String
*
* @param uint8_t * pointer to an address that is same value as string
* 
* @return void
*/
void log_string(uint8_t * str);

/**
* @brief Prints a given number
*
* @param uint32_t* pointer to an address that is same value as integer
*
* @return void
*/
void log_integer(uint32_t * integer);



#endif /* __LOGGER_H__ */
