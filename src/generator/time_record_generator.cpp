#include <samplingEngineInternal/generator/time_record_generator.h>

namespace samplingEngine
    {
    namespace generator
        {
        namespace time
            {
            TimeRecordGenerator::TimeRecordGenerator()
                {
                }
            TimeRecordGenerator::~TimeRecordGenerator()
                {
                }
            void TimeRecordGenerator::configure(const samplingEngine::generator::TimeRecordGeneratorConfiguration& /*(_config */)
                {
                }
            void TimeRecordGenerator::initialize()
                {
                }
            void TimeRecordGenerator::shutdown()
                {
                }
            void TimeRecordGenerator::generate_record(samplingEngine::records::time_record*& /* _record */)
                {
                // allocate a record
                // fill it out
                // return it
                }
            void TimeRecordGenerator::cleanup_record(samplingEngine::records::time_record*& /* _record */)
                {
                // deallocate a record
                }
            }
        }
    }
