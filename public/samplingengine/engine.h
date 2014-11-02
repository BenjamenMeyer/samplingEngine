#ifndef ENGINE_ENGINE_H__
#define ENGINE_ENGINE_H__

#include <stdint.h>

#include "time_record.h"
#include "distance_record.h"
#include "configuration.h"

#ifdef __cplusplus
	extern "C" {
#endif

//
// engine_get_error_message()
//
// Purpose:
//	Provide a means to get a reliable human readable form of the error message
//
// Parameters:
//	_error_code - int32_t - error code provided by one of the engine functions
//
// Returns:
//	Human readable error message encoded as 8-bit UTF-8 ASCIIZ text
//
const char* engine_get_error_message(uint32_t _error_code);

//
// engine_initialize()
//
// Purpose:
//	Configure the engine and prepare for operational usage based on the configuration
//
// Parameters:
//	_configuration - pointer to a struct engine_configuration containing the configuration data
//
// Returns:
//	integer value specifying the error code
//
int32_t engine_initialize(struct engine_configuration* _configuration);

//
// engine_shutdown()
//
// Purpose:
//	Graceful shutdown of the engine allowing all data, valid or invalid, to be retrieved.
//	This performs an auto-simulation of the data until the buffers clear of any good derivative data
// 	to ensure that all distance records are properly generated.
//
// Parameters:
//	n/a
//
// Returns:
//	integer value containing either of the following:
//		if negative - error code
//              if zero or postive - number of records available to be retrieved 
//
int32_t engine_shutdown();

//
// engine_close()
//
// Purpose:
//	To terminate the engine, releasing all buffers, and destroying any remaining run-time data
//
// Parameters:
//	n/a
//
// Returns:
//	integer value specifying the error code
//
//	Note: Any data not retrieved from the processing engine will automatically be destroyed
//
int32_t engine_close(void);

//
// engine_process_record()
//
// Purpose:
//	To input new time data into the processing engine in order to generate new distance data
//
// Parameters:
//	_record - pointer to struct time_record containing a time sample to process
//
// Returns:
//	integer value containing either of the following:
//		if negative - error code
//              if zero or postive - number of records available to be retrieved 
//
int32_t engine_process_record(struct time_record* _record); 

//
// engine_get_record()
//
// Purpose:
//	To retrieve a generated record from the system
//
// Parameters:
//	_record_type - int32_t pointer - pointer to variable that will receive the record type
//	_record - pointer to a pointer - pointer to a pointer that will receive the record data
//		- value must be NULL going in
//
// Returns:
//	integer value containing the error
//	if no error, then the parameters may be relied on
//
//	Note: When data is passed out, it must be copied from the buffer. Memory is not necessarily allocated
//		to pass the record out of the processing engine. Memory that is allocated will be reclaimed when
//		the next record is processed by engine_process_record()
//
int32_t engine_get_record(int32_t* _record_type, void** _record);

#ifdef __cplusplus
	}
#endif

#endif //ENGINE_ENGINE_H__
