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
	return "UNKNOWN ERROR";
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
