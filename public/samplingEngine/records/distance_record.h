#ifndef SAMPLING_ENGINE_DISTANCE_RECORD_H__
#define SAMPLING_ENGINE_DISTANCE_RECORD_H__

#include <stdint.h>

namespace samplingEngine
    {
    namespace records
        {
        // Distance-Domain Flags specified via a bitmap
        namespace distance_record_flags
            {
            enum distanceFlags
                {
                DISTANCE_FLAGS_CLEAR=0,                // No Flags are set
                DISTANCE_FLAGS_SIMULATION_MODE,        // Simulation Mode Enabled
                };
            };

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
        struct time_indexes       // associated time sample index range
            {
            uint64_t start_index; // earliest time sample used to generate the distance sample
            uint64_t end_index;   // latest time sample used to generate the distance sample
            };

        struct distance_record
            {
            uint32_t length;            // length of the entire record
            uint32_t id;                // record identifier
            uint64_t sample_index;      // distance sample index
            struct time_indexes index;  // associated time sample index range
            int64_t tachometer;         // distance movement sensor data
            uint64_t flags;             // flags
            uint8_t channels[1];        // array of channel data
            };
        }
    }

#endif //SAMPLING_ENGINE_DISTANCE_RECORD_H__
