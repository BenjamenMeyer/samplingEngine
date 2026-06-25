#ifndef FAKE_SENSOR_TACHOMETER_H__
#define FAKE_SENSOR_TACHOMETER_H__

#include <samplingEngine/channels/time_channels.h>

#include <samplingEngineInternal/sensors/tachometer/abstractTachometer.h>
#include <samplingEngineInternal/utils/sine_generator.h>

namespace sensor
    {
    namespace fake
        {
        class fakeTachometerSensor: sensor::abstractTachometerSensor
            {
            public:
                //! Constructor
                fakeTachometerSensor();
                //! Destructor
                virtual ~fakeTachometerSensor();

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
                void updateRecord(samplingEngine::records::status_record*& _record, bool _timeDomain);

                // set the current Time-based Record Output Index (end of time queue)
                void setTimeRecordOutputIndex(uint64_t _input_index, size_t _data_size);
            protected:
                // if officialTachometer is true, then this is the sole tachometer
                // if it's false, then it needs to be stored into one of the MULTI_TACH channels
                // so that the multiTachometer can combine them together
                bool officialTachometer{false};
                bool ascending{true};
                uint32_t count_by{1};
                uint32_t max{0x00FFFFFF};
                uint32_t min{0x0};

                // is the sensor active
                bool active{false};

                // location in time records
                // samplingEngine::channels::time::timeChannels channelLocation;

                // sine wave generator
                utils::sineWaveGeneratorUnsignedInt32 sineWave;

            private:
                // official name
                std::string name{"fake-tachometer"};
            };
        }
    }

#endif // FAKE_SENSOR_TACHOMETER_H__
