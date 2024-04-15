#include <samplingEngineInternal/sensors/tachometer/fakeTachometer.h>
#include <samplingEngine/error_codes.h>

namespace sensor {

    namespace fake {

    fakeTachometerSensor::fakeTachometerSensor() : sensor::abstractTachometerSensor()
        {
        }

    fakeTachometerSensor::~fakeTachometerSensor()
        {
        }

    const std::string& fakeTachometerSensor::sensorName()
        {
        return name;
        }

    void fakeTachometerSensor::open(const struct samplingEngine::config::engineConfiguration& _configuration)
        {
        //
        active = _configuration.sensors.tachometer.simulate_tachometer;
        if (true == active)
            {
            officialTachometer = _configuration.sensors.tachometer.simulator_official;
            ascending = _configuration.sensors.tachometer.simulator_ascending;
            count_by = _configuration.sensors.tachometer.simulator_count_by;
            min = _configuration.sensors.tachometer.simulator_min;
            max = _configuration.sensors.tachometer.simulator_max;
            sineWave.open(0, min, max, count_by, ascending);

            // how would time channels apply to this?
            // _configuration.time_channels.
            }
        }

    bool fakeTachometerSensor::isOpen() const
        {
        return active;
        }

    void fakeTachometerSensor::reset()
        {
        sineWave.reset();
        }

    void fakeTachometerSensor::close()
        {
        sineWave.close();
        }
    
    void fakeTachometerSensor::processRecord(const samplingEngine::records::time_record* /* _record */)
        {
        // there is nothing to process as the data is generated here
        }
    
    void fakeTachometerSensor::updateRecord(samplingEngine::records::time_record*& _record)
        {
        if (_record != NULL)
            {
            _record->tachometer = int64_t(sineWave.read());
            }
        }

    void fakeTachometerSensor::updateRecord(samplingEngine::records::status_record*& /* _record */, bool /* _timeDomain */)
        {
        // there are no channels to manage
        }

    void fakeTachometerSensor::setTimeRecordOutputIndex(uint64_t /* _input_index */, size_t /* _data_size_ */)
        {
        // nothing to track as its part of the core record data
        }

    }
}
