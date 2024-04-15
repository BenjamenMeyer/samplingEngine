#ifndef SAMPLING_ENGINE_RECORD_GENERATOR_H__
#define SAMPLING_ENGINE_RECORD_GENERATOR_H__

#include <samplingEngine/records/time_record.h>
#include <samplingEngine/channels/channel.h>

namespace samplingEngine
    {
    namespace generator
        {

        struct TimeRecordGeneratorConfiguration
            {
            uint16_t sample_rate{400};      // how many samples per second, default 400 HZ
            uint8_t  tachometer_count{1};   // how many tachometers should be emulated, default 1

            samplingEngine::channels::channelList time_channels;    // time record channel configuration
            };

        class AbstractTimeRecordGenerator
            {
            public:
                AbstractTimeRecordGenerator();
                virtual ~AbstractTimeRecordGenerator();

                virtual void configure(const TimeRecordGeneratorConfiguration& _config)=0;
                virtual void initialize()=0;
                virtual void shutdown()=0;

                virtual void generate_record(samplingEngine::records::time_record*& _record)=0;
                virtual void cleanup_record(samplingEngine::records::time_record*& _record)=0;
            };

        AbstractTimeRecordGenerator* NewTimeRecordGenerator();
        }
    }

#endif //SAMPLING_ENGINE_RECORD_GENERATOR__
