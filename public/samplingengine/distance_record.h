#ifndef ENGINE_DISTANCE_RECORD_H__
#define ENGINE_DISTANCE_RECORD_H__

#include <cstdint>

namespace samplingEngine
    {
    namespace records
        {
        // the system has a maximum time sample rate that determines
        // the maximum velocity for capturing data. As the velocity
        // reaches that maximum velocity value then the start/end
        // indexes will shrink together and ultimately reach the same
        // value at the maximum velocity
        // For example, 400 HZ time collection yields a maximum
        // velocity of 360 KPH. When the vehicle stands still, no
        // distance data will be able to be generated since it is not
        // moving and thus the maximum number of possible time sample
        // data records will be used for generating the distance sample
        // that eventually comes out. As the system goes from 0 KPH (zero)
        // to 360 KPH fewer time sample records will be used for each
        // distance record. When the system reaches 360 KPH then there will
        // be 1 time record for each distance record (start = end).
        // It is not wise to surpass the maximum velocity (start > end) as
        // data will then be unreliable.
        struct time_indexes      // associated time sample index range
            {
            uint64_t start_index; // earliest time sample used to generate the distance sample
            uint64_t end_index;   // latest time sample used to generate the distance sample
            };

        struct distance_record
            {
            // length of the entire record
            uint32_t length;
            // record identifier
            uint32_t id;
            // distance sample index 
            uint64_t sample_index;
            // associated time sample index range
            struct time_indexes index;
            // distance movement sensor data
            int64_t tachometer;
            // array of channel data
            uint8_t channels[1];
            };
        }
    }

#endif //ENGINE_DISTANCE_RECORD_H__
