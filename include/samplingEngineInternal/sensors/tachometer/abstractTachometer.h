#ifndef ABSTRACT_SENSOR_TACHOMETER_H__
#define ABSTRACT_SENSOR_TACHOMETER_H__

#include <deque>

#include <samplingEngine/configuration.h>

#include <samplingEngine/sensors/abstractSensor.h>

namespace sensor
    {
    class abstractTachometerSensor: samplingEngine::interfaces::abstractSensor
        {
        public:
            //! Constructor
            abstractTachometerSensor();
            //! Destructor
            virtual ~abstractTachometerSensor();

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

    typedef std::deque<abstractTachometerSensor*> tachometerSensorList;
    }

#endif // ABSTRACT_SENSOR_TACHOMETER_H__
