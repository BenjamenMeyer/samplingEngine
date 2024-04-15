#include <samplingEngineInternal/sensors/tachometer/multiTachometer.h>
#include <samplingEngine/error_codes.h>

namespace sensor {

    namespace multi {

    tachometerEntry::tachometerEntry()
        {
        }
    tachometerEntry::~tachometerEntry()
        {
        }
    void tachometerEntry::init()
        {
        }
    void tachometerEntry::reset()
        {
        }
    void tachometerEntry::apply(uint32_t /* _value */)
        {
        //uint32_t mask = 0x0000FFFF;
        //uint32_t roll_managed = _value & mask;
        }

    multiTachometerSensor::multiTachometerSensor() : sensor::abstractTachometerSensor()
        {
        }

    multiTachometerSensor::~multiTachometerSensor()
        {
        }

    const std::string& multiTachometerSensor::sensorName()
        {
        return name;
        }

    void multiTachometerSensor::open(const struct samplingEngine::config::engineConfiguration& /* _configuration */)
        {
        }

    bool multiTachometerSensor::isOpen() const
        {
        return active;
        }

    void multiTachometerSensor::reset()
        {
        }

    void multiTachometerSensor::close()
        {
        }
    
    void multiTachometerSensor::processRecord(const samplingEngine::records::time_record* /* _record */)
        {
        }
    
    void multiTachometerSensor::updateRecord(samplingEngine::records::time_record*& _record)
        {
        if (_record != NULL)
            {
            // _record->tachometer = int64_t(sineWave.read());
            }
        }

    void multiTachometerSensor::updateRecord(samplingEngine::records::status_record*& /* _record */, bool /* _timeDomain */)
        {
        }

    void multiTachometerSensor::setTimeRecordOutputIndex(uint64_t /* _input_index */, size_t /* _data_size_ */)
        {
        }

    }
}
