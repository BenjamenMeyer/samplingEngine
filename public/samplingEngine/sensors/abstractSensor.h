#ifndef SAMPLING_ENGINE_INTERFACE_ABSTRACT_SENSOR_H__
#define SAMPLING_ENGINE_INTERFACE_ABSTRACT_SENSOR_H__

#include <stdint.h>

#include <deque>
#include <string>

#include <samplingEngine/configuration.h>

#include <samplingEngine/records/time_record.h>
#include <samplingEngine/records/status_record.h>

namespace samplingEngine
    {
    namespace interfaces
        {
        //! List of Sensor names
        typedef std::deque<std::string> sensorNameList;

        class abstractSensor;
        //! List of sensors
        typedef std::deque<abstractSensor*> abstractSensorList;

        //! Interface of a sensor
        /*!
         Generic interface for any implemented sensor

         Sensors can only work on time-based data.
         */
        class abstractSensor
            {
            public:
                //! Constructor
                abstractSensor();
                //! Destructor
                virtual ~abstractSensor();

                //! sensor name
                /*!
                 Access the human readable name of the sensor
                 /returns std::string containing an UTF-8 ASCIIZ  string with the name of the sensor
                 */
                virtual const std::string& sensorName()=0;

                // open the sensor for use
                virtual void open(const struct samplingEngine::config::engineConfiguration& _configuration)=0;
                // is the sensor open for use?
                virtual bool isOpen() const=0;

                // reset the sensor data
                virtual void reset()=0;

                // close the sensor
                virtual void close()=0;

                // input - function should get the required information from the record
                virtual void processRecord(const samplingEngine::records::time_record* _record)=0;

                // output - function should update its portion of the records
                virtual void updateRecord(samplingEngine::records::time_record*& _record)=0;
                virtual void updateRecord(samplingEngine::records::status_record*& _record, bool timeDomain)=0;

                // set the current Time-based Record Output Index (end of time queue)
                virtual void setTimeRecordOutputIndex(uint64_t _input_index, size_t _data_size)=0;
            };
        }
    }

#endif // SAMPLING_ENGINE_INTERFACE_ABSTRACT_SENSOR_H__
