#ifndef INTERNAL_SAMPLING_ENGINE_RECORD_GENERATOR_H__
#define INTERNAL_SAMPLING_ENGINE_RECORD_GENERATOR_H__

#include <generator/time_generator.h>
#include <samplingEngineInternal/sensors/tachometer/abstractTachometer.h>

namespace samplingEngine
    {
    namespace generator
        {
        namespace time
            {

            class TimeRecordGenerator : public samplingEngine::generator::AbstractTimeRecordGenerator
                {
                public:
                    TimeRecordGenerator();
                    virtual ~TimeRecordGenerator();

                    virtual void configure(const samplingEngine::generator::TimeRecordGeneratorConfiguration& _config);
                    virtual void initialize();
                    virtual void shutdown();

                    virtual void generate_record(samplingEngine::records::time_record*& _record);
                    virtual void cleanup_record(samplingEngine::records::time_record*& _record);

                protected:
                    const samplingEngine::generator::TimeRecordGeneratorConfiguration* configuration;
                    // sensor emulators

                    std::deque<sensor::abstractTachometerSensor> tachometers;
                };
            }
        }
    }

#endif //INTERNAL_SAMPLING_ENGINE_RECORD_GENERATOR_H__
