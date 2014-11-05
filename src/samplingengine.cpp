#include <samplingengine/engine.h>
#include <samplingengine/error_codes.h>

const char* engine_get_error_message(uint32_t _error_code)
{
	return "UNKNOWN ERROR";
}

int32_t engine_initialization(struct engine_configuration* _configuration)
{
	int32_t returnValue = 0;
	returnValue = ENGINE_MAKE_ERROR_CODE(ENGINE_ERROR_NOT_INITIALIZED);
	return returnValue;
}

int32_t engine_shutdown()
{
	int32_t returnValue = 0;
	returnValue = ENGINE_MAKE_ERROR_CODE(ENGINE_ERROR_NOT_INITIALIZED);
	return returnValue;
}

int32_t engine_close(void)
{
	int32_t returnValue = 0;
	returnValue = ENGINE_MAKE_ERROR_CODE(ENGINE_ERROR_NOT_INITIALIZED);
	return returnValue;
}

int32_t engine_process_record(struct time_record* _record)
{
	int32_t returnValue = 0;
	returnValue = ENGINE_MAKE_ERROR_CODE(ENGINE_ERROR_NOT_INITIALIZED);
	return returnValue;
}

int32_t engine_get_record(int32_t* _record_type, void** _record)
{
	int32_t returnValue = 0;
	returnValue = ENGINE_MAKE_ERROR_CODE(ENGINE_ERROR_NOT_INITIALIZED);
	return returnValue;
}
