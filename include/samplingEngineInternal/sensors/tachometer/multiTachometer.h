#ifndef MULTI_TACHOMETER_H__
#define MULTI_TACHOMETER_H__

#include <stdint.h>

#include <samplingEngine/configuration.h>
#include <samplingEngine/channels/time_channels.h>

#include <samplingEngineInternal/sensors/tachometer/abstractTachometer.h>
#include <samplingEngineInternal/filters/averaging.h>

namespace sensor
    {
    namespace multi
        {
        class tachometerEntry {
            public:
                filters::AveragingFilterUInt32 tach32;
                filters::AveragingFilterUInt16 tach16;

                tachometerEntry();
                ~tachometerEntry();
                void init();
                void reset();
                void apply(uint32_t _value);
        };

        //! multiTachometer - integrate multiple tachometer sensors
        /*!
            Receive multiple tachometers and combine them together into a single time-based channels.
            This requires all the hardware sensors to be integrated into the time-based record prior
            to this tachometer being used.

            The multiTachometer works by averaging the hardware tachometer sensors and generating
            a new tachometer sensor value.
         */
        class multiTachometerSensor: abstractTachometerSensor
            {
            public:
                //! Constructor
                multiTachometerSensor();
                //! Destructor
                virtual ~multiTachometerSensor();

                //! sensor name
                /*!
                 Access the human readable name of the sensor
                 /returns std::string containing an UTF-8 ASCIIZ  string with the name of the sensor
                 */
                const std::string& sensorName();

                // open the sensor for use
                void open(const struct samplingEngine::config::engineConfiguration& _configuration);
                // is the sensor open for use?
                bool isOpen() const;

                // reset the sensor data
                void reset();

                // close the sensor
                void close();

                // input - function should get the required information from the record
                void processRecord(const samplingEngine::records::time_record* _record);

                // output - function should update its portion of the records
                void updateRecord(samplingEngine::records::time_record*& _record);
                void updateRecord(samplingEngine::records::status_record*& _record, bool timeDomain);

                // set the current Time-based Record Output Index (end of time queue)
                void setTimeRecordOutputIndex(uint64_t _input_index, size_t _data_size);
            protected:
                typedef std::map<samplingEngine::channels::time::timeChannels, struct tachometerEntry> tachTracker;

                const std::string name{"multitach"};
                bool active{false};

                // reads the MULTI_TACH_ channels, combines them together using an averaging
                // algorithm and then puts the result into the singular tachometer record.
                // these channels are only in use when the multi-tach is in use
                uint32_t runningAverage;

                tachTracker inputTachometers;
            };
        }
    }

#endif
