#include <samplingEngine/engine.h>
#include <samplingEngine/error_codes.h>

// #include <internal/logging/log.h>

#include <map>
#include <pair>
#include <string>

namespace samplingEngine {

static samplingEngineLogger* local_logger = NULL;

void send_to_log(LOG_LEVELS _level, const char* _message)
	{
	if (local_logger != NULL)
		{
		switch (_level)
			{
			default:					local_logger->debug(_message);		break;
			case LOG_LEVEL_EMERGENCY:	local_logger->emergency(_message);	break;
			case LOG_LEVEL_ALERT:		local_logger->alert(_message);		break;
			case LOG_LEVEL_CRITICAL:	local_logger->critical(_message);	break;
			case LOG_LEVEL_ERROR:		local_logger->error(_message);		break;
			case LOG_LEVEL_WARN:		local_logger->warn(_message);		break;
			case LOG_LEVEL_NOTICE:		local_logger->notice(_message);		break;
			case LOG_LEVEL_INFO:		local_logger->info(_message);		break;
			case LOG_LEVEL_DEBUG:		local_logger->debug(_message);		break;
			};
		}
	}

/**************************************
 *** Object Contruction/Destruction ***
 **************************************/
samplingEngine::samplingEngine(samplingEngineLogger* _logger) :coreEngine(NULL)
	{
	local_logger = _logger;
	send_to_log(LOG_LEVEL_DEBUG, "Constructing Sampling Engine Interface");
	configuration = config::engineConfiguration();
	setState(SAMPLE_ENGINE_NOT_INITIALIZED);

	// TODO: Create the core engine

	send_to_log(LOG_LEVEL_DEBUG, "Sampling Engine Interface Fully Constructed");
	}
samplingEngine::~samplingEngine()
	{
	send_to_log(LOG_LEVEL_DEBUG, "Deconstructing Sampling Engine Interface");
	if (coreEngine != NULL)
		{
		delete coreEngine;
		coreEngine = NULL;
		}
	configuration = config::engineConfiguration();
	setState(SAMPLE_ENGINE_DESTRUCTION);

	send_to_log(LOG_LEVEL_DEBUG, "Sampling Engine Interface Fully Deconstructed");
	// finally reset the logger
	local_logger = NULL;
	}

/***************
 *** Logging ***
 ***************/
samplingEngineLogger* samplingEngine::setLogger(samplingEngineLogger* _logger)
	{
	samplingEngineLogger* returnValue = local_logger;
	send_to_log(LOG_LEVEL_INFO, "Switching to new log system");

	local_logger = _logger;
	send_to_log(LOG_LEVEL_INFO, "Logging on new log system");

	return returnValue;
	}

/*****************************
 *** Error message look-up ***
 *****************************/
/* static */ const std::string  samplingEngine::getErrorMessage(uint32_t _error_code)
	{
	// if we use an if or switch structure we could eventually run out of branching
	// capabilities; so we use a simple map lookup instead. if it's in the map then
	// we have a message to hand back; otherwise we just use a default message
	typedef std::map<uint32_t, std::string> errorMessageMap;
	typedef std::pair<uint32_t, std::string> errorMessageData;

	static bool initialized = false;
	static errorMessageMap messageData;

	if (initialized == false)
		{
		#define ADD_ERROR_MESSAGE(container, code, message)		\
			{													\
			errorMessageData data(uint32_t(code), message);		\
			container.insert(data);								\
			}

		ADD_ERROR_MESSAGE(messageData, SAMPLING_ENGINE_ERROR_SUCCESS, "Operation Successful");
		ADD_ERROR_MESSAGE(messageData, SAMPLING_ENGINE_ERROR_BAD_PARAMETER, "Bad Parameter to function call");
		ADD_ERROR_MESSAGE(messageData, SAMPLING_ENGINE_ERROR_NOT_INITIALIZED, "Sampling Engine has not yet been initialized");
		ADD_ERROR_MESSAGE(messageData, SAMPLING_ENGINE_ERROR_ALREADY_INITIALIZED, "Sampling Engine has already been initialized");
		ADD_ERROR_MESSAGE(messageData, SAMPLING_ENGINE_ERROR_FILTER_MISMATCH, "Unable to find a matching filter");
		ADD_ERROR_MESSAGE(messageData, SAMPLING_ENGINE_ERROR_MEMORY_ALLOCATION, "Unable to allocate memory");
		ADD_ERROR_MESSAGE(messageData, SAMPLING_ENGINE_ERROR_FILTER_NOT_PRIMED, "Filter does not have enough data to be stable");
		ADD_ERROR_MESSAGE(messageData, SAMPLING_ENGINE_ERROR_INVALID_POINTER, "Invalid Pointer");

		initialized = true;
		}

	// if it's an error code that we returned, then convert it to a normal error code
	// that can be used for lookup. Otherwise, assume the caller already did the
	// conversion and try to just look it up
	uint32_t actual_error = SAMPLING_ENGINE_GET_ERROR_CODE(_error_code);
	if (SAMPLING_ENGINE_IS_ERROR_CODE(_error_code))
		{
		actual_error = SAMPLING_ENGINE_GET_ERROR_CODE(_error_code);
		}
	
	// default error message text
	std::string returnValue = "UNKNOWN ERROR";

	// if the error code is in the message map, update the returned value
	errorMessageMap::iterator msg = messageData.find(actual_error);
	if (msg != messageData.end())
		{
		msg = (*msg);
		}

	// provide the meaning back to the caller
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

	send_to_log(LOG_LEVEL_INFO, "Attempting to initialize sampling engine...");
	if (!isStateSet(SAMPLE_ENGINE_INITIALIZED))
		{
		configuration = _configuration;
		enableState(SAMPLE_ENGINE_INITIALIZED);

		// TODO: create the actual engine

		// Ready for Startup
		enableState(SAMPLE_ENGINE_OPERATIONAL_STARTUP);
		send_to_log(LOG_LEVEL_INFO, "Entering Sampling Engine Start-up Mode");

		// Engine State
		switch (configuration.operationalState)
			{
			default:
				send_to_log(LOG_LEVEL_ERROR, "Unknown Operational State. Terminating");
				close();
				returnValue = SAMPLING_ENGINE_MAKE_ERROR_CODE(SAMPLING_ENGINE_ERROR_BAD_PARAMETER);
				break;

			case config::ENGINE_NORMAL_OPERATION:
				enableState(SAMPLE_ENGINE_OPERATION_MODE);
				send_to_log(LOG_LEVEL_INFO, "Entering Normal Operations Mode");
				returnValue = SAMPLING_ENGINE_MAKE_ERROR_CODE(SAMPLING_ENGINE_ERROR_SUCCESS);
				break;

			case config::ENGINE_DIAGNOSTIC_OPERATION:
				enableState(SAMPLE_ENGINE_DIAGNOSTIC_MODE);
				send_to_log(LOG_LEVEL_INFO, "Entering Diagnostic Operations Mode");
				returnValue = SAMPLING_ENGINE_MAKE_ERROR_CODE(SAMPLING_ENGINE_ERROR_SUCCESS);
				break;

			case config::ENGINE_CALIBRATION_OPERATION:
				enableState(SAMPLE_ENGINE_CALIBRATION_MODE);
				send_to_log(LOG_LEVEL_INFO, "Entering Calibration Operations Mode");
				returnValue = SAMPLING_ENGINE_MAKE_ERROR_CODE(SAMPLING_ENGINE_ERROR_SUCCESS);
				break;
			};
		}
	else
		{
		send_to_log(LOG_LEVEL_INFO, "Failed to initialize sampling engine because it was already initialized");
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

	send_to_log(LOG_LEVEL_INFO, "Attempting to start operational shutdown of sampling engine...");
	if (isStateSet(SAMPLE_ENGINE_INITIALIZED))
		{
		send_to_log(LOG_LEVEL_INFO, "Switching from Operation Mode to Shutdown Mode");
		disableState(SAMPLE_ENGINE_OPERATIONAL_STARTUP);
		disableState(SAMPLE_ENGINE_OPERATIONAL_READY);
		enableState(SAMPLE_ENGINE_OPERATIONAL_SHUTDOWN);

		send_to_log(LOG_LEVEL_INFO, "Processing last time record until buffers are cleared");
		// TODO: See 2.2 above
		send_to_log(LOG_LEVEL_INFO, "Buffers clear. Shutdown complete");

		disableState(SAMPLE_ENGINE_OPERATIONAL_SHUTDOWN);
		disableState(SAMPLE_ENGINE_DIAGNOSTIC_MODE);
		disableState(SAMPLE_ENGINE_CALIBRATION_MODE);
		disableState(SAMPLE_ENGINE_OPERATION_MODE);

		send_to_log(LOG_LEVEL_INFO, "Returning to initialized state");
		setState(SAMPLE_ENGINE_INITIALIZED);
		returnValue = SAMPLING_ENGINE_MAKE_ERROR_CODE(SAMPLING_ENGINE_ERROR_SUCCESS);
		}
	else
		{
		send_to_log(LOG_LEVEL_ERROR, "Failed to start operational shutdown because sampling engine not initialized");
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

	send_to_log(LOG_LEVEL_INFO, "Attempting to close the sampling engine")
	if (isStateSet(SAMPLE_ENGINE_INITIALIZED))
		{
		send_to_log(LOG_LEVEL_INFO, "Resetting all component");

		// TODO: Reset core engine

		send_to_log(LOG_LEVEL_INFO, "Returning to uninitialized state");
		setState(SAMPLE_ENGINE_NOT_INITIALIZED);
		returnValue = SAMPLING_ENGINE_MAKE_ERROR_CODE(SAMPLING_ENGINE_ERROR_SUCCESS);
		}
	else
		{
		send_to_log(LOG_LEVEL_ERROR, "Failed to close because sampling engine not initialized");
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
