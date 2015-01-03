#ifndef ENGINE_CONFIGURATION_H__
#define ENGINE_CONFIGURATION_H__

#include <cstdint>

#include <samplingengine/time_channels.h>
#include <samplingengine/distance_channels.h>
#include <samplingengine/channel.h>

namespace samplingEngine
    {
    namespace config
        {
        struct tachometerConfiguration
            {
            // Tachometer Pulses (counts) Per Meter
            uint64_t pulses_per_meter;
            };

        struct sampleConfiguration
            {
            // Time Sample Rate in HZ (e.g 100 HZ, 240 HZ, 400 HZ, 1000 HZ)
            uint16_t time_sample_rate_hz;

            // Distance Sample Rate in Millimeters
            uint16_t distance_sample_rate_mm;
            };

        struct sensorConfiguration
            {
            struct samplingEngine::config::tachometerConfiguration tachometer;
            };

        struct engineConfiguration
            {
            // Sample Configuration
            struct samplingEngine::config::sampleConfiguration samples;

            // Sensors
            struct samplingEngine::config::sensorConfiguration sensors;

            // Input Channels
            samplingEngine::channels::channelList time_channels;

            // Output Channels
            samplingEngine::channels::channelList distance_channels;
            };
        }
    }

#endif //ENGINE_CONFIGURATION_H__
