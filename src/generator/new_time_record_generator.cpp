#include <generator/time_generator.h>

#include <samplingEngineInternal/generator/time_record_generator.h>

namespace samplingEngine
    {
    namespace generator
        {
        AbstractTimeRecordGenerator* NewTimeRecordGenerator()
            {
            // auto trg = new samplingEngine::generator::time::TimeRecordGenerator();
            // return reinterpret_cast<AbstractTimeRecordGenerator*>(trg);
            return new samplingEngine::generator::time::TimeRecordGenerator();
            }
        }
    }
