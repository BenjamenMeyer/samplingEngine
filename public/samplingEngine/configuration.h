#ifndef SAMPLING_ENGINE_CONFIGURATION_H__
#define SAMPLING_ENGINE_CONFIGURATION_H__

#include <stdint.h>

#include <samplingEngine/channels/time_channels.h>
#include <samplingEngine/channels/distance_channels.h>
#include <samplingEngine/channels/channel.h>

namespace samplingEngine
    {
    namespace config
        {
        //! Tachometer Sensor Configuration
        /*!
         Configuration data for the tachometer sensor
         */
        struct tachometerConfiguration
            {
            //! Tachometer Pulses (counts) Per Meter
            /*!
             Calibration of the tachometer sensor data used to determine
             how much linear movement has occurred between any two samples.
             */
            uint64_t pulses_per_meter;
            };

        //! Sample Configuration
        /*!
         The sample configuration determines the capabilities of the system, especially
         that related to the distance domain sample generation. The time rate (HZ) and
         distance specification (mm) are combined to specify the maximum velocity the
         system will support.

         The following table provides some examples:

            HZ      Distance        Maximum Speed (KPH/MPH)
            ====    ===========     =======================
            60      250             54      /   33.75
            60      275             59.4    /   37.125
            60      300             64.8    /   40.5
            60      325             70.2    /   43.875
            60      350             75.6    /   47.25
            60      375             81      /   50.625
            60      400             86.4    /   54
            120     250             108     /   67.5
            120     275             118.8   /   74.25
            120     300             129.6   /   81
            120     325             140.4   /   87.75
            120     350             151.2   /   94.5
            120     375             162     /   101.25
            120     400             172.8   /   108
            240     250             216     /   135
            240     275             237.6   /   148.5
            240     300             259.2   /   162
            240     325             280.8   /   175.5
            240     350             302.4   /   189
            240     375             324     /   202.5
            240     400             345.6   /   216
            400     250             360     /   225
            400     275             396     /   247.5
            400     300             432     /   270
            400     325             468     /   292.5
            400     350             504     /   315
            400     375             540     /   337.5
            400     400             576     /   360
            1000    250             900     /   562.5
            1000    275             990     /   618.75
            1000    300             1080    /   675
            1000    325             1170    /   731.25
            1000    350             1260    /   787.5
            1000    375             1350    /   843.75
            1000    400             1440    /   900
            10000   250             9000    /   5625
            10000   275             9900    /   6187.5
            10000   300             10800   /   6750
            10000   325             11700   /   7312.5
            10000   350             12600   /   7875
            10000   375             13500   /   8437.5
            10000   400             14400   /   9000

         */
        struct sampleConfiguration
            {
            //! Time Sample Rate in HZ
            /*!
             The constant number of records being provided into the engine, f.e 100 HZ.
             */
            uint16_t time_sample_rate_hz;

            //! Distance Sample Rate in Millimeters
            /*!
             The maximum distance between two distance records that the engine should generate, f.e 250 mm.
             */
            uint16_t distance_sample_rate_mm;
            };

        //! Sensor Configuration
        /*!
         Configuration for the various sensors used by the sampling engine.
         */
        struct sensorConfiguration
            {
            //! Tachometer Sensor Configuration
            struct samplingEngine::config::tachometerConfiguration tachometer;
            };

        //! Sampling Engine Operating Mode
        /*!
         The sampling engine operates in several different modes. The diagnostic mode
         allows the engine to be run like normal but with additional information being
         generated, while the calibration mode allows the engine to calculate what its
         configuration should be for various measurements.
         */
        enum engineConfigurationState
            {
            ENGINE_NORMAL_OPERATION=0,   /*!< Normal Operating Mode */
            ENGINE_DIAGNOSTIC_OPERATION, /*!< Diagnostic Operating Mode */
            ENGINE_CALIBRATION_OPERATION /*!< Measurement Calibration Mode */
            };

        //! Sampling Engine Configuration
        /*!
         The complete set of configuration data for the sampling engine.
         */
        struct engineConfiguration
            {
            //! Sampling Engine Operating Mode
            engineConfigurationState operationalState;

            //! Sample Configuration
            struct samplingEngine::config::sampleConfiguration samples;

            //! Sensors Configuration
            struct samplingEngine::config::sensorConfiguration sensors;

            //! Time-based Record Channel Configuration
            /*!
             Channel Configuration for Time-based Record data.

             This is required for the input data records, and may also
             be relevant to output data records if time-based record
             output is configured.
             */
            samplingEngine::channels::channelList time_channels;

            //! Distance-based Record Channel Configuration
            /*!
             Channel configuration for Distance-based Record data.

             Required if distance-based record output is configured.
             */
            samplingEngine::channels::channelList distance_channels;
            };
        }
    }

#endif //SAMPLING_ENGINE_CONFIGURATION_H__
