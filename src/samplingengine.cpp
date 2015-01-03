#include <samplingengine/engine.h>
#include <samplingengine/error_codes.h>

/**************************************
 *** Object Contruction/Destruction ***
 **************************************/
samplingEngine::samplingEngine::samplingEngine()
	{
	}
samplingEngine::samplingEngine::~samplingEngine()
	{
	}

/*****************************
 *** Error message look-up ***
 *****************************/
/* static */ const std::string  samplingEngine::samplingEngine::getErrorMessage(uint32_t _error_code)
	{
	return "UNKNOWN ERROR";
	}


/**********************
 *** Initialization ***
 **********************/
int32_t samplingEngine::samplingEngine::initialization(const struct samplingEngine::config::engineConfiguration& _configuration)
	{
	int32_t returnValue = 0;
	returnValue = ENGINE_MAKE_ERROR_CODE(ENGINE_ERROR_NOT_INITIALIZED);
	return returnValue;
	}

/*************************
 *** Graceful Shutdown ***
 *************************/
int32_t samplingEngine::samplingEngine::shutdown()
	{
	int32_t returnValue = 0;
	returnValue = ENGINE_MAKE_ERROR_CODE(ENGINE_ERROR_NOT_INITIALIZED);
	return returnValue;
	}

/*******************
 *** Destruction ***
 *******************/
int32_t samplingEngine::samplingEngine::close(void)
	{
	int32_t returnValue = 0;
	returnValue = ENGINE_MAKE_ERROR_CODE(ENGINE_ERROR_NOT_INITIALIZED);
	return returnValue;
	}

/********************
 *** Record Input ***
 ********************/
int32_t samplingEngine::processRecord(struct time_record* _record)
	{
	int32_t returnValue = 0;
	returnValue = ENGINE_MAKE_ERROR_CODE(ENGINE_ERROR_NOT_INITIALIZED);
	return returnValue;
	}

/**************************
 *** Output Record Type ***
 **************************/
records::recordType samplingEngine::getRecordType() const
	{
	int32_t returnValue = 0;
	returnValue = ENGINE_MAKE_ERROR_CODE(ENGINE_ERROR_NOT_INITIALIZED);
	return returnValue;
	}

/**********************
 *** Output Records ***
 **********************/
int32_t samplingEngine::getDataRecord(struct records::distance_record*& _record)
	{
	int32_t returnValue = 0;
	returnValue = ENGINE_MAKE_ERROR_CODE(ENGINE_ERROR_NOT_INITIALIZED);
	return returnValue;
	}

int32_t samplingEngine::getStatusRecord(struct records::status_record*& _record)
	{
	int32_t returnValue = 0;
	returnValue = ENGINE_MAKE_ERROR_CODE(ENGINE_ERROR_NOT_INITIALIZED);
	return returnValue;
	}

int32_t samplingEngine::getTimeRecord(struct records::time_record*& _record)
	{
	int32_t returnValue = 0;
	returnValue = ENGINE_MAKE_ERROR_CODE(ENGINE_ERROR_NOT_INITIALIZED);
	return returnValue;
	}
