#include <samplingEngine/engine.h>
#include <samplingEngine/error_codes.h>

namespace samplingEngine {

/**************************************
 *** Object Contruction/Destruction ***
 **************************************/
samplingEngine::samplingEngine()
	{
	}
samplingEngine::~samplingEngine()
	{
	}

/*****************************
 *** Error message look-up ***
 *****************************/
/* static */ const std::string  samplingEngine::getErrorMessage(uint32_t _error_code)
	{
	std::string returnValue = "UNKNOWN ERROR";

	// if it's an error code that we returned, then convert it to a normal error code
	// that can be used for lookup. Otherwise, assume the caller already did the
	// conversion and try to just look it up
	uint32_t actual_error = SAMPLING_ENGINE_GET_ERROR_CODE(_error_code);
	if (SAMPLING_ENGINE_IS_ERROR_CODE(_error_code))
		{
		actual_error = SAMPLING_ENGINE_GET_ERROR_CODE(_error_code);
		}
	
	// lookup and make the conversion
	switch (actual_error)
		{
		default:
			//do nothing
			break;
		case SAMPLING_ENGINE_ERROR_SUCCESS:
			returnValue = "Operation Successful";
			break;
		case SAMPLING_ENGINE_ERROR_BAD_PARAMETER:
			returnValue = "Bad Parameter to function call";
			break;
		case SAMPLING_ENGINE_ERROR_NOT_INITIALIZED:
			returnValue = "Sampling Engine has not yet been initialized";
			break;
		case SAMPLING_ENGINE_ERROR_ALREADY_INITIALIZED:
			returnValue = "Sampling Engine has already been initialized";
			break;
		case SAMPLING_ENGINE_ERROR_FILTER_MISMATCH:
			returnValue = "Unable to find a matching filter";
			break;
		case SAMPLING_ENGINE_ERROR_MEMORY_ALLOCATION:
			returnValue = "Unable to allocate memory";
			break;
		case SAMPLING_ENGINE_ERROR_FILTER_NOT_PRIMED:
			returnValue = "Filter does not have enough data to be stable";
			break;
		};
	return returnValue;
	}


/**********************
 *** Initialization ***
 **********************/
int32_t samplingEngine::initialize(const struct config::engineConfiguration& _configuration)
	{
	int32_t returnValue = 0;
	returnValue = SAMPLING_ENGINE_MAKE_ERROR_CODE(SAMPLING_ENGINE_ERROR_NOT_INITIALIZED);
	return returnValue;
	}

/*************************
 *** Graceful Shutdown ***
 *************************/
int32_t samplingEngine::shutdown()
	{
	int32_t returnValue = 0;
	returnValue = SAMPLING_ENGINE_MAKE_ERROR_CODE(SAMPLING_ENGINE_ERROR_NOT_INITIALIZED);
	return returnValue;
	}

/*******************
 *** Destruction ***
 *******************/
int32_t samplingEngine::close(void)
	{
	int32_t returnValue = 0;
	returnValue = SAMPLING_ENGINE_MAKE_ERROR_CODE(SAMPLING_ENGINE_ERROR_NOT_INITIALIZED);
	return returnValue;
	}

/********************
 *** Record Input ***
 ********************/
int32_t samplingEngine::processRecord(const struct records::time_record*& _record)
	{
	int32_t returnValue = 0;
	returnValue = SAMPLING_ENGINE_MAKE_ERROR_CODE(SAMPLING_ENGINE_ERROR_NOT_INITIALIZED);
	return returnValue;
	}

/**************************
 *** Output Record Type ***
 **************************/
records::recordType samplingEngine::getRecordType() const
	{
	records::recordType returnValue = records::INVALID_RECORD_TYPE;
	return returnValue;
	}

/**********************
 *** Output Records ***
 **********************/
int32_t samplingEngine::getDataRecord(struct records::distance_record*& _record)
	{
	int32_t returnValue = 0;
	returnValue = SAMPLING_ENGINE_MAKE_ERROR_CODE(SAMPLING_ENGINE_ERROR_NOT_INITIALIZED);
	return returnValue;
	}

int32_t samplingEngine::getStatusRecord(struct records::status_record*& _record)
	{
	int32_t returnValue = 0;
	returnValue = SAMPLING_ENGINE_MAKE_ERROR_CODE(SAMPLING_ENGINE_ERROR_NOT_INITIALIZED);
	return returnValue;
	}

int32_t samplingEngine::getTimeRecord(struct records::time_record*& _record)
	{
	int32_t returnValue = 0;
	returnValue = SAMPLING_ENGINE_MAKE_ERROR_CODE(SAMPLING_ENGINE_ERROR_NOT_INITIALIZED);
	return returnValue;
	}

}
