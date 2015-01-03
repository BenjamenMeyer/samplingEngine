#include <samplingEngine/engine.h>
#include <samplingEngine/error_codes.h>

// #include <string.h>

namespace samplingEngine {

/**************************************
 *** Object Contruction/Destruction ***
 **************************************/
samplingEngine::samplingEngine()
	{
	// memset(&configuration, 0, sizeof(struct config::engineConfiguration));
	configuration = config::engineConfiguration();
	setState(SAMPLE_ENGINE_NOT_INITIALIZED);
	}
samplingEngine::~samplingEngine()
	{
	configuration = config::engineConfiguration();
	setState(SAMPLE_ENGINE_DESTRUCTION);
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

/********************
 *** State Access ***
 ********************/
void samplingEngine::setState(sampleEngineState _state)
	{
	state = _state;
	}
uint32_t samplingEngine::getState() const
	{
	return state;
	}

/*********************************
 *** Enable/Disable State Bits ***
 *********************************/
void samplingEngine::enableState(samplingEngine::sampleEngineState _state_bit)
	{
	state |= _state_bit;
	}
void samplingEngine::disableState(samplingEngine::sampleEngineState _state_bit)
	{
	uint32_t inverse_bit = ~uint32_t(_state_bit);
	state &= inverse_bit;
	}
bool samplingEngine::isStateSet(samplingEngine::sampleEngineState _state_bit) const
	{
	return (state & _state_bit);
	}

/**********************
 *** Initialization ***
 **********************/
int32_t samplingEngine::initialize(const struct config::engineConfiguration& _configuration)
	{
	int32_t returnValue = 0;
	returnValue = SAMPLING_ENGINE_MAKE_ERROR_CODE(SAMPLING_ENGINE_ERROR_NOT_INITIALIZED);

	if (!isStateSet(SAMPLE_ENGINE_INITIALIZED))
		{
		configuration = _configuration;
		enableState(SAMPLE_ENGINE_INITIALIZED);

		// TODO: Initialize Filters

		// Ready for Startup
		enableState(SAMPLE_ENGINE_OPERATIONAL_STARTUP);

		// Engine State
		switch (configuration.operationalState)
			{
			default:
				returnValue = SAMPLING_ENGINE_MAKE_ERROR_CODE(SAMPLING_ENGINE_ERROR_BAD_PARAMETER);
				break;

			case config::ENGINE_NORMAL_OPERATION:
				// TODO: Any special calibration configurations
				enableState(SAMPLE_ENGINE_OPERATION_MODE);
				returnValue = SAMPLING_ENGINE_MAKE_ERROR_CODE(SAMPLING_ENGINE_ERROR_SUCCESS);
				break;

			case config::ENGINE_DIAGNOSTIC_OPERATION:
				// TODO: Any special diagnostic configurations
				enableState(SAMPLE_ENGINE_DIAGNOSTIC_MODE);
				returnValue = SAMPLING_ENGINE_MAKE_ERROR_CODE(SAMPLING_ENGINE_ERROR_SUCCESS);
				break;

			case config::ENGINE_CALIBRATION_OPERATION:
				enableState(SAMPLE_ENGINE_CALIBRATION_MODE);
				returnValue = SAMPLING_ENGINE_MAKE_ERROR_CODE(SAMPLING_ENGINE_ERROR_SUCCESS);
				break;
			};
		}
	else
		{
		returnValue = SAMPLING_ENGINE_MAKE_ERROR_CODE(SAMPLING_ENGINE_ERROR_ALREADY_INITIALIZED);
		}
	return returnValue;
	}

/*************************
 *** Graceful Shutdown ***
 *************************/
int32_t samplingEngine::shutdown()
	{
	int32_t returnValue = 0;
	returnValue = SAMPLING_ENGINE_MAKE_ERROR_CODE(SAMPLING_ENGINE_ERROR_NOT_INITIALIZED);

	// 1. If not initialized, return the error as such
	// 2. If initialized...
	// 2.1 set the shutdown state bit
	// 2.2 repeat the last time-sample until the buffer has been completely overwritten with it
	// 2.2.1 continue generating output samples throughout this process
	// 2.3 clear any operational mode bits - resetting to simply initialized
	// 2.4 return success so that the caller can retrieve the generated records

	if (isStateSet(SAMPLE_ENGINE_INITIALIZED))
		{
		disableState(SAMPLE_ENGINE_OPERATIONAL_STARTUP);
		disableState(SAMPLE_ENGINE_OPERATIONAL_READY);
		enableState(SAMPLE_ENGINE_OPERATIONAL_SHUTDOWN);

		// TODO: See 2.2 above 

		disableState(SAMPLE_ENGINE_OPERATIONAL_SHUTDOWN);
		disableState(SAMPLE_ENGINE_DIAGNOSTIC_MODE);
		disableState(SAMPLE_ENGINE_CALIBRATION_MODE);
		disableState(SAMPLE_ENGINE_OPERATION_MODE);
		setState(SAMPLE_ENGINE_INITIALIZED);
		returnValue = SAMPLING_ENGINE_MAKE_ERROR_CODE(SAMPLING_ENGINE_ERROR_SUCCESS);
		}
	else
		{
		returnValue = SAMPLING_ENGINE_MAKE_ERROR_CODE(SAMPLING_ENGINE_ERROR_NOT_INITIALIZED);
		}
	return returnValue;
	}

/*******************
 *** Destruction ***
 *******************/
int32_t samplingEngine::close(void)
	{
	int32_t returnValue = 0;
	returnValue = SAMPLING_ENGINE_MAKE_ERROR_CODE(SAMPLING_ENGINE_ERROR_NOT_INITIALIZED);

	// 1. If not initialized, return the error as such
	// 2. If initialized...
	// 2.1 clear the filters of all data, etc; releasing all memory
	// 2.2 set state back to simply not initialized
	// 2.3 return success

	if (isStateSet(SAMPLE_ENGINE_INITIALIZED))
		{
		// TODO: Clear filters
		setState(SAMPLE_ENGINE_NOT_INITIALIZED);
		returnValue = SAMPLING_ENGINE_MAKE_ERROR_CODE(SAMPLING_ENGINE_ERROR_SUCCESS);
		}
	else
		{
		returnValue = SAMPLING_ENGINE_MAKE_ERROR_CODE(SAMPLING_ENGINE_ERROR_NOT_INITIALIZED);
		}
	return returnValue;
	}

/********************
 *** Record Input ***
 ********************/
int32_t samplingEngine::processRecord(const struct records::time_record*& _record)
	{
	int32_t returnValue = 0;
	returnValue = SAMPLING_ENGINE_MAKE_ERROR_CODE(SAMPLING_ENGINE_ERROR_NOT_INITIALIZED);

	if (isStateSet(SAMPLE_ENGINE_INITIALIZED))
		{
		}
	else
		{
		returnValue = SAMPLING_ENGINE_MAKE_ERROR_CODE(SAMPLING_ENGINE_ERROR_NOT_INITIALIZED);
		}
	return returnValue;
	}

/**************************
 *** Output Record Type ***
 **************************/
records::recordType samplingEngine::getTimeRecordType() const
	{
	records::recordType returnValue = records::INVALID_RECORD_TYPE;

	if (isStateSet(SAMPLE_ENGINE_INITIALIZED))
		{
		}
	return returnValue;
	}
records::recordType samplingEngine::getDistanceRecordType() const
	{
	records::recordType returnValue = records::INVALID_RECORD_TYPE;

	if (isStateSet(SAMPLE_ENGINE_INITIALIZED))
		{
		}
	return returnValue;
	}

/**********************
 *** Output Records ***
 **********************/
int32_t samplingEngine::getDataRecord(struct records::distance_record*& _record)
	{
	int32_t returnValue = 0;
	returnValue = SAMPLING_ENGINE_MAKE_ERROR_CODE(SAMPLING_ENGINE_ERROR_NOT_INITIALIZED);

	if (isStateSet(SAMPLE_ENGINE_INITIALIZED))
		{
		}
	else
		{
		returnValue = SAMPLING_ENGINE_MAKE_ERROR_CODE(SAMPLING_ENGINE_ERROR_NOT_INITIALIZED);
		}
	return returnValue;
	}

int32_t samplingEngine::getStatusRecord(struct records::status_record*& _record)
	{
	int32_t returnValue = 0;
	returnValue = SAMPLING_ENGINE_MAKE_ERROR_CODE(SAMPLING_ENGINE_ERROR_NOT_INITIALIZED);

	if (isStateSet(SAMPLE_ENGINE_INITIALIZED))
		{
		}
	else
		{
		returnValue = SAMPLING_ENGINE_MAKE_ERROR_CODE(SAMPLING_ENGINE_ERROR_NOT_INITIALIZED);
		}
	return returnValue;
	}

int32_t samplingEngine::getTimeRecord(struct records::time_record*& _record)
	{
	int32_t returnValue = 0;
	returnValue = SAMPLING_ENGINE_MAKE_ERROR_CODE(SAMPLING_ENGINE_ERROR_NOT_INITIALIZED);

	if (isStateSet(SAMPLE_ENGINE_INITIALIZED))
		{
		}
	else
		{
		returnValue = SAMPLING_ENGINE_MAKE_ERROR_CODE(SAMPLING_ENGINE_ERROR_NOT_INITIALIZED);
		}
	return returnValue;
	}
}
