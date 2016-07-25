#ifndef SAMPLING_ENGINE_CONFIGURATION_H__
#define SAMPLING_ENGINE_CONFIGURATION_H__

#include <stdint.h>

#include <samplingEngine/time_channels.h>
#include <samplingEngine/distance_channels.h>
#include <samplingEngine/channel.h>

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

        enum engineConfigurationState
            {
            ENGINE_NORMAL_OPERATION=0,
            ENGINE_DIAGNOSTIC_OPERATION,
            ENGINE_CALIBRATION_OPERATION
            };

        struct engineConfiguration
            {
            // engine configuration state
            engineConfigurationState operationalState;

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

#endif //SAMPLING_ENGINE_CONFIGURATION_H__
