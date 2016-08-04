#ifndef SAMPLING_ENGINE_TIME_RECORD_H__
#define SAMPLING_ENGINE_TIME_RECORD_H__

#include <stdint.h>

namespace samplingEngine
    {
    namespace records
        {

        // Time-Domain Flags specified via a bitmap
        namespace time_record_flags
            {
            enum timeFlags
                {
                TIME_FLAGS_CLEAR=0,                // No flags are set
                TIME_FLAGS_SIMULATION_MODE,        // Simulation Mode Enabled
                };
            };

        struct time_record
            {
            uint32_t length;      // length of the entire record
            uint32_t id;          // record identifier
            uint64_t index;       // time sample index
            int64_t tachometer;   // distance movement sensor data
            uint64_t flags;       // time record flags
            uint8_t channels[1];  // array of channel data
            };
        }
    }

#endif //SAMPLING_ENGINE_TIME_RECORD_H__
