#ifndef ENGINE_TIME_RECORD_H__
#define ENGINE_TIME_RECORD_H__

#include <stdint.h>

struct time_record
{
    uint32_t length;      // length of the entire record
    uint32_t id;          // record identifier
    uint64_t index;       // time sample index
    int64_t tachometer;   // distance movement sensor data
    uint8_t channels[1];  // array of channel data
};

#endif //ENGINE_TIME_RECORD_H__
