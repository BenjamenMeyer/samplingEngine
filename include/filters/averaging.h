#ifndef ENGINE_FILTERS_AVERAGING_H__
#define ENGINE_FILTERS_AVERAGING_H__

#include <stdint.h>

#define AVERAGING_FILTER_TYPE_NONE		0x00000000
#define AVERAGING_FILTER_TYPE_INT_8		0x00000001
#define AVERAGING_FILTER_TYPE_INT_16	0x00000002
#define AVERAGING_FILTER_TYPE_INT_32	0x00000004
#define AVERAGING_FILTER_TYPE_INT_64	0x00000008

#define AVERAGING_FILTER_TYPE_UNSIGNED_MASK	0x80000000

#define AVERAGING_FILTER_TYPE_UINT_8	(AVERAGING_FILTER_TYPE_UNSIGNED_MASK|AVERAGING_FILTER_TYPE_INT_8)
#define AVERAGING_FILTER_TYPE_UINT_16	(AVERAGING_FILTER_TYPE_UNSIGNED_MASK|AVERAGING_FILTER_TYPE_INT_16)
#define AVERAGING_FILTER_TYPE_UINT_32	(AVERAGING_FILTER_TYPE_UNSIGNED_MASK|AVERAGING_FILTER_TYPE_INT_32)
#define AVERAGING_FILTER_TYPE_UINT_64	(AVERAGING_FILTER_TYPE_UNSIGNED_MASK|AVERAGING_FILTER_TYPE_INT_64)

struct averaging_filter
{
	uint64_t filter_length;		// length of the data buffer
	uint16_t filter_type;		// type of data buffer
	void* filter_buffer;		// data buffer
	void* filter_rolling_sum;	// rolling summation of the data
	struct indexes
	{
		uint64_t start;		// starting index
		uint64_t end;		// ending index
	} index;				// round-robin index in the buffer
};


//
// averaging_filter_initialize()
//
// Parameters:
//	_filter - pointer to struct averaging filter - filter to be initialized
//	_filter_type - type of filter to initialize, see AVERAGING_FILTER_TYPE_* for acceptable values
//
// Return Value:
//	if negative, error value
//	if zero, success
//
int32_t averaging_filter_initialize(struct averaging_filter* _filter, uint16_t _filter_type, uint64_t _filter_length);

//
// averaging_filter_destroy()
//
// Parameters:
//	_filter - pointer to struct averaging filter - filter to be destroyed
//
// Return Value:
//	if negaive, error value
//	if zero, success
//
int32_t averaging_filter_destroy(struct averaging_filter* _filter);

//
// averaging_filter_apply()
//
// Parameters:
//	_filter - pointer to struct averaging_filter to apply the value to
//	_value - value to apply
//
// Return Value:
//	if negative, error value
//	if zero, success
//
//
int32_t averaging_filter_apply_int8(struct averaging_filter* _filter, int8_t _value);
int32_t averaging_filter_apply_in16(struct averaging_filter* _filter, int16_t _value);
int32_t averaging_filter_apply_int32(struct averaging_filter* _filter, int32_t _value);
int32_t averaging_filter_apply_int64(struct averaging_filter* _filter, int64_t _value);
int32_t averaging_filter_apply_uint8(struct averaging_filter* _filter, uint8_t _value);
int32_t averaging_filter_apply_uint16(struct averaging_filter* _filter, uint16_t _value);
int32_t averaging_filter_apply_uint32(struct averaging_filter* _filter, uint32_t _value);
int32_t averaging_filter_apply_uint64(struct averaging_filter* _filter, uint64_t _value);

//
// averaging_filter_get_value()
//
// Parameters:
//	_filter - pointer to struct averaging_filter to apply the value to
//	_value - pointer where to store the value
//
// Return Value:
//	if negative, error value
//	if zero, success
//
//
int32_t averaging_filter_get_value_int8(struct averaging_filter* _filter, int8_t* _value);
int32_t averaging_filter_get_value_int16(struct averaging_filter* _filter, int16_t* _value);
int32_t averaging_filter_get_value_int32(struct averaging_filter* _filter, int32_t* _value);
int32_t averaging_filter_get_value_int64(struct averaging_filter* _filter, int64_t* _value);
int32_t averaging_filter_get_value_uint8(struct averaging_filter* _filter, uint8_t* _value);
int32_t averaging_filter_get_value_uint16(struct averaging_filter* _filter, uint16_t* _value);
int32_t averaging_filter_get_value_uint32(struct averaging_filter* _filter, uint32_t* _value);
int32_t averaging_filter_get_value_uint64(struct averaging_filter* _filter, uint64_t* _value);

#endif //ENGINE_FILTERS_AVERAGING_H__
