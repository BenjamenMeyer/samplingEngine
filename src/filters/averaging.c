#include <filters/averaging.h>
#include <samplingengine/error_codes.h>

#include<stdlib.h> 

static uint64_t calculate_index(uint64_t _current, uint64_t _length)
{
	return ((_current + 1) % _length);
}

int32_t averaging_filter_initialize(struct averaging_filter* _filter, uint16_t _filter_type, uint64_t _filter_length)
{
	int32_t returnValue = ENGINE_ERROR_SUCCESS;

	if (_filter->filter_length != 0 || _filter->filter_type != AVERAGING_FILTER_TYPE_NONE || _filter->filter_buffer != NULL || _filter->filter_rolling_sum != NULL)
        {
		returnValue = ENGINE_MAKE_ERROR_CODE(ENGINE_ERROR_ALREADY_INITIALIZED);
        }
	else if (_filter_length == 0)
	{
		returnValue = ENGINE_MAKE_ERROR_CODE(ENGINE_ERROR_BAD_PARAMETER);
	}
	else
	{
		size_t data_type_size = 0;
		switch((int16_t)_filter_type)
		{
			default:
				data_type_size = 0;
				returnValue = ENGINE_MAKE_ERROR_CODE(ENGINE_ERROR_BAD_PARAMETER);
				break;
			case AVERAGING_FILTER_TYPE_INT_8:
			case AVERAGING_FILTER_TYPE_UINT_8:
				data_type_size = sizeof(uint8_t);
				break;
			case AVERAGING_FILTER_TYPE_INT_16:
			case AVERAGING_FILTER_TYPE_UINT_16:
				data_type_size = sizeof(uint16_t);
				break;
			case AVERAGING_FILTER_TYPE_INT_32:
			case AVERAGING_FILTER_TYPE_UINT_32:
				data_type_size = sizeof(uint32_t);
				break;
			case AVERAGING_FILTER_TYPE_INT_64:
			case AVERAGING_FILTER_TYPE_UINT_64:
				data_type_size = sizeof(uint64_t);
				break;
		};
		if (data_type_size != 0)
		{
			_filter->filter_buffer = calloc(data_type_size, _filter_length);
			if (_filter->filter_buffer == NULL)
			{
				returnValue = ENGINE_MAKE_ERROR(ENGINE_ERROR_MEMORY_ALLOCATION);
			}
			else
			{
				_filter->filter_rolling_sum = calloc(data_type_size, 1);
				if (_filter->filter_rolling_sum == NULL)
				{
					returnValue = ENGINE_MAKE_ERROR(ENGINE_ERROR_MEMORY_ALLOCATION);
				}
				else
				{
					_filter->filter_type = _filter_type;
					_filter->filter_length = _filter_length;
					_filter->index.start = 0;
					_filter->index.end = 0;
					returnValue = ENGINE_ERROR_SUCCESS;
				}
			}
		}
	}

	return returnValue;
}

int32_t averaging_filter_destroy(struct averaging_filter* _filter)
{
	int32_t returnValue = ENGINE_ERROR_SUCCESS;
	if (_filter->filter_length == 0 || _filter->filter_type == AVERAGING_FILTER_TYPE_NONE || _filter->filter_buffer == NULL || _filter->filter_rolling_sum == NULL)
	{
		returnValue = ENGINE_MAKE_ERROR_CODE(ENGINE_ERROR_NOT_INITIALIZED);
	}
	else
	{
		switch ((int16_t)_filter->filter_type)
		{
			default:
				returnValue = ENGINE_MAKE_ERROR_CODE(ENGINE_ERROR_BAD_PARAMETER);
				break;
			case AVERAGING_FILTER_TYPE_INT_8:
			case AVERAGING_FILTER_TYPE_UINT_8:
			case AVERAGING_FILTER_TYPE_INT_16:
			case AVERAGING_FILTER_TYPE_UINT_16:
			case AVERAGING_FILTER_TYPE_INT_32:
			case AVERAGING_FILTER_TYPE_UINT_32:
			case AVERAGING_FILTER_TYPE_INT_64:
			case AVERAGING_FILTER_TYPE_UINT_64:
				free(_filter->filter_buffer);
				free(_filter->filter_rolling_sum);
				memset(_filter, 0, sizeof(struct averaging_filter));
				returnValue = ENGINE_ERROR_SUCCESS;
				break;
		};
	}
	return returnValue;
}

int32_t averaging_filter_apply_int8(struct averaging_filter* _filter, int8_t _value)
{
	int32_t returnValue = ENGINE_ERROR_SUCCESS;
	if (_filter->filter_type == AVERAGING_FILTER_TYPE_INT_8)
	{
		uint64_t next_index = calculate_index(_filter->index.start, _filter->filter_length);
		// subtract the last value off the
		if (next_index == _filter->index.end)
		{
			(*((int8_t*)_filter->filter_rolling_sum)) -= ((int8_t*)_filter->filter_buffer)[_filter->index.end];
		}

		((int8_t*)_filter->filter_buffer)[_filter->index.start] = _value;
		_filter->index.start = next_index;
	}
	else
	{
		returnValue = ENGINE_MAKE_ERROR_CODE(ENGINE_ERROR_FILTER_MISMATCH);
	}
	return returnValue;
}
int32_t averaging_filter_apply_uint8(struct averaging_filter* _filter, uint8_t _value)
{
	int32_t returnValue = ENGINE_ERROR_SUCCESS;
	if (_filter->filter_type == AVERAGING_FILTER_TYPE_INT_8)
	{
		uint64_t next_index = calculate_index(_filter->index.start, _filter->filter_length);
		// subtract the last value off the
		if (next_index == _filter->index.end)
		{
			(*((uint8_t*)_filter->filter_rolling_sum)) -= ((uint8_t*)_filter->filter_buffer)[_filter->index.end];
		}

		((uint8_t*)_filter->filter_buffer)[_filter->index.start] = _value;
		_filter->index.start = next_index;
	}
	else
	{
		returnValue = ENGINE_MAKE_ERROR_CODE(ENGINE_ERROR_FILTER_MISMATCH);
	}
	return returnValue;
}

int32_t averaging_filter_apply_int16(struct averaging_filter* _filter, int16_t _value)
{
	int32_t returnValue = ENGINE_ERROR_SUCCESS;
	if (_filter->filter_type == AVERAGING_FILTER_TYPE_INT_8)
	{
		uint64_t next_index = calculate_index(_filter->index.start, _filter->filter_length);
		// subtract the last value off the
		if (next_index == _filter->index.end)
		{
			(*((int16_t*)_filter->filter_rolling_sum)) -= ((int16_t*) _filter->filter_buffer)[_filter->index.end];
		}

		((int16_t*)_filter->filter_buffer)[_filter->index.start] = _value;
		_filter->index.start = next_index;
	}
	else
	{
		returnValue = ENGINE_MAKE_ERROR_CODE(ENGINE_ERROR_FILTER_MISMATCH);
	}
	return returnValue;
}
int32_t averaging_filter_apply_uint16(struct averaging_filter* _filter, uint16_t _value)
{
	int32_t returnValue = ENGINE_ERROR_SUCCESS;
	if (_filter->filter_type == AVERAGING_FILTER_TYPE_INT_8)
	{
		uint64_t next_index = calculate_index(_filter->index.start, _filter->filter_length);
		// subtract the last value off the
		if (next_index == _filter->index.end)
		{
			(*((uint16_t*)_filter->filter_rolling_sum)) -= ((uint16_t*) _filter->filter_buffer)[_filter->index.end];
		}

		((uint16_t*)_filter->filter_buffer)[_filter->index.start] = _value;
		_filter->index.start = next_index;
	}
	else
	{
		returnValue = ENGINE_MAKE_ERROR_CODE(ENGINE_ERROR_FILTER_MISMATCH);
	}
	return returnValue;
}

int32_t averaging_filter_apply_int32(struct averaging_filter* _filter, int32_t _value)
{
	int32_t returnValue = ENGINE_ERROR_SUCCESS;
	if (_filter->filter_type == AVERAGING_FILTER_TYPE_INT_8)
	{
		uint64_t next_index = calculate_index(_filter->index.start, _filter->filter_length);
		// subtract the last value off the
		if (next_index == _filter->index.end)
		{
			(*((int32_t*)_filter->filter_rolling_sum)) -= ((int32_t*) _filter->filter_buffer)[_filter->index.end];
		}

		((int32_t*)_filter->filter_buffer)[_filter->index.start] = _value;
		_filter->index.start = next_index;
	}
	else
	{
		returnValue = ENGINE_MAKE_ERROR_CODE(ENGINE_ERROR_FILTER_MISMATCH);
	}
	return returnValue;
}
int32_t averaging_filter_apply_uint32(struct averaging_filter* _filter, uint32_t _value)
{
	int32_t returnValue = ENGINE_ERROR_SUCCESS;
	if (_filter->filter_type == AVERAGING_FILTER_TYPE_INT_8)
	{
		uint64_t next_index = calculate_index(_filter->index.start, _filter->filter_length);
		// subtract the last value off the
		if (next_index == _filter->index.end)
		{
			(*((uint32_t*)_filter->filter_rolling_sum)) -= ((uint32_t*) _filter->filter_buffer)[_filter->index.end];
		}

		((uint32_t*)_filter->filter_buffer)[_filter->index.start] = _value;
		_filter->index.start = next_index;
	}
	else
	{
		returnValue = ENGINE_MAKE_ERROR_CODE(ENGINE_ERROR_FILTER_MISMATCH);
	}
	return returnValue;
}

int32_t averaging_filter_apply_int64(struct averaging_filter* _filter, int64_t _value)
{
	int32_t returnValue = ENGINE_ERROR_SUCCESS;
	if (_filter->filter_type == AVERAGING_FILTER_TYPE_INT_8)
	{
		uint64_t next_index = calculate_index(_filter->index.start, _filter->filter_length);
		// subtract the last value off the
		if (next_index == _filter->index.end)
		{
			(*((int64_t*)_filter->filter_rolling_sum)) -= ((int64_t*) _filter->filter_buffer)[_filter->index.end];
		}

		((int64_t*)_filter->filter_buffer)[_filter->index.start] = _value;
		_filter->index.start = next_index;
	}
	else
	{
		returnValue = ENGINE_MAKE_ERROR_CODE(ENGINE_ERROR_FILTER_MISMATCH);
	}
	return returnValue;
}
int32_t averaging_filter_apply_uint64(struct averaging_filter* _filter, uint64_t _value)
{
	int32_t returnValue = ENGINE_ERROR_SUCCESS;
	if (_filter->filter_type == AVERAGING_FILTER_TYPE_INT_8)
	{
		uint64_t next_index = calculate_index(_filter->index.start, _filter->filter_length);
		// subtract the last value off the
		if (next_index == _filter->index.end)
		{
			(*((uint64_t*)_filter->filter_rolling_sum)) -= ((uint64_t*) _filter->filter_buffer)[_filter->index.end];
		}

		((uint64_t*)_filter->filter_buffer)[_filter->index.start] = _value;
		_filter->index.start = next_index;
	}
	else
	{
		returnValue = ENGINE_MAKE_ERROR_CODE(ENGINE_ERROR_FILTER_MISMATCH);
	}
	return returnValue;
}

int32_t averaging_filter_get_value_int8(struct averaging_filter* _filter, int8_t* _value)
{
	int32_t returnValue = ENGINE_ERROR_SUCCESS;
	if (_filter->filter_type == AVERAGING_FILTER_TYPE_INT_8)
	{
		uint64_t next_index = calculate_index(_filter->index.start, _filter->filter_length);
		// subtract the last value off the
		if (next_index == _filter->index.end)
		{
			(*_value) = ((*((int8_t*)_filter->filter_rolling_sum)) / _filter->filter_length);
			returnValue = ENGINE_ERROR_SUCCESS;
		}
		else
		{
			returnValue = ENGINE_MAKE_ERROR_CODE(ENGINE_ERROR_FILTER_NOT_PRIMED);
		}
	}
	else
	{
		returnValue = ENGINE_MAKE_ERROR_CODE(ENGINE_ERROR_FILTER_MISMATCH);
	}
	return returnValue;
}
int32_t averaging_filter_get_value_uint8(struct averaging_filter* _filter, uint8_t* _value)
{
	int32_t returnValue = ENGINE_ERROR_SUCCESS;
	if (_filter->filter_type == AVERAGING_FILTER_TYPE_INT_8)
	{
		uint64_t next_index = calculate_index(_filter->index.start, _filter->filter_length);
		// subtract the last value off the
		if (next_index == _filter->index.end)
		{
			(*_value) = ((*((uint8_t*)_filter->filter_rolling_sum)) / _filter->filter_length);
			returnValue = ENGINE_ERROR_SUCCESS;
		}
		else
		{
			returnValue = ENGINE_MAKE_ERROR_CODE(ENGINE_ERROR_FILTER_NOT_PRIMED);
		}
	}
	else
	{
		returnValue = ENGINE_MAKE_ERROR_CODE(ENGINE_ERROR_FILTER_MISMATCH);
	}
	return returnValue;
}

int32_t averaging_filter_get_value_int16(struct averaging_filter* _filter, int16_t* _value)
{
	int32_t returnValue = ENGINE_ERROR_SUCCESS;
	if (_filter->filter_type == AVERAGING_FILTER_TYPE_INT_8)
	{
		uint64_t next_index = calculate_index(_filter->index.start, _filter->filter_length);
		// subtract the last value off the
		if (next_index == _filter->index.end)
		{
			(*_value) = ((*((int16_t*)_filter->filter_rolling_sum)) / _filter->filter_length);
			returnValue = ENGINE_ERROR_SUCCESS;
		}
		else
		{
			returnValue = ENGINE_MAKE_ERROR_CODE(ENGINE_ERROR_FILTER_NOT_PRIMED);
		}
	}
	else
	{
		returnValue = ENGINE_MAKE_ERROR_CODE(ENGINE_ERROR_FILTER_MISMATCH);
	}
	return returnValue;
}
int32_t averaging_filter_get_value_uint16(struct averaging_filter* _filter, uint16_t* _value)
{
	int32_t returnValue = ENGINE_ERROR_SUCCESS;
	if (_filter->filter_type == AVERAGING_FILTER_TYPE_INT_8)
	{
		uint64_t next_index = calculate_index(_filter->index.start, _filter->filter_length);
		// subtract the last value off the
		if (next_index == _filter->index.end)
		{
			(*_value) = ((*((uint16_t*)_filter->filter_rolling_sum)) / _filter->filter_length);
			returnValue = ENGINE_ERROR_SUCCESS;
		}
		else
		{
			returnValue = ENGINE_MAKE_ERROR_CODE(ENGINE_ERROR_FILTER_NOT_PRIMED);
		}
	}
	else
	{
		returnValue = ENGINE_MAKE_ERROR_CODE(ENGINE_ERROR_FILTER_MISMATCH);
	}
	return returnValue;
}

int32_t averaging_filter_get_value_int32(struct averaging_filter* _filter, int32_t* _value)
{
	int32_t returnValue = ENGINE_ERROR_SUCCESS;
	if (_filter->filter_type == AVERAGING_FILTER_TYPE_INT_8)
	{
		uint64_t next_index = calculate_index(_filter->index.start, _filter->filter_length);
		// subtract the last value off the
		if (next_index == _filter->index.end)
		{
			(*_value) = ((*((int32_t*)_filter->filter_rolling_sum)) / _filter->filter_length);
			returnValue = ENGINE_ERROR_SUCCESS;
		}
		else
		{
			returnValue = ENGINE_MAKE_ERROR_CODE(ENGINE_ERROR_FILTER_NOT_PRIMED);
		}
	}
	else
	{
		returnValue = ENGINE_MAKE_ERROR_CODE(ENGINE_ERROR_FILTER_MISMATCH);
	}
	return returnValue;
}
int32_t averaging_filter_get_value_uint32(struct averaging_filter* _filter, uint32_t* _value)
{
	int32_t returnValue = ENGINE_ERROR_SUCCESS;
	if (_filter->filter_type == AVERAGING_FILTER_TYPE_INT_8)
	{
		uint64_t next_index = calculate_index(_filter->index.start, _filter->filter_length);
		// subtract the last value off the
		if (next_index == _filter->index.end)
		{
			(*_value) = ((*((uint32_t*)_filter->filter_rolling_sum)) / _filter->filter_length);
			returnValue = ENGINE_ERROR_SUCCESS;
		}
		else
		{
			returnValue = ENGINE_MAKE_ERROR_CODE(ENGINE_ERROR_FILTER_NOT_PRIMED);
		}
	}
	else
	{
		returnValue = ENGINE_MAKE_ERROR_CODE(ENGINE_ERROR_FILTER_MISMATCH);
	}
	return returnValue;
}

int32_t averaging_filter_get_value_int64(struct averaging_filter* _filter, int64_t* _value)
{
	int32_t returnValue = ENGINE_ERROR_SUCCESS;
	if (_filter->filter_type == AVERAGING_FILTER_TYPE_INT_8)
	{
		uint64_t next_index = calculate_index(_filter->index.start, _filter->filter_length);
		// subtract the last value off the
		if (next_index == _filter->index.end)
		{
			(*_value) = ((*((int64_t*)_filter->filter_rolling_sum)) / _filter->filter_length);
			returnValue = ENGINE_ERROR_SUCCESS;
		}
		else
		{
			returnValue = ENGINE_MAKE_ERROR_CODE(ENGINE_ERROR_FILTER_NOT_PRIMED);
		}
	}
	else
	{
		returnValue = ENGINE_MAKE_ERROR_CODE(ENGINE_ERROR_FILTER_MISMATCH);
	}
	return returnValue;
}
int32_t averaging_filter_get_value_uint64(struct averaging_filter* _filter, uint64_t* _value)
{
	int32_t returnValue = ENGINE_ERROR_SUCCESS;
	if (_filter->filter_type == AVERAGING_FILTER_TYPE_INT_8)
	{
		uint64_t next_index = calculate_index(_filter->index.start, _filter->filter_length);
		// subtract the last value off the
		if (next_index == _filter->index.end)
		{
			(*_value) = ((*((uint64_t*)_filter->filter_rolling_sum)) / _filter->filter_length);
			returnValue = ENGINE_ERROR_SUCCESS;
		}
		else
		{
			returnValue = ENGINE_MAKE_ERROR_CODE(ENGINE_ERROR_FILTER_NOT_PRIMED);
		}
	}
	else
	{
		returnValue = ENGINE_MAKE_ERROR_CODE(ENGINE_ERROR_FILTER_MISMATCH);
	}
	return returnValue;
}
