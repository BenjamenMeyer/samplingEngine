#ifndef GEOMETRIC_ENGINE_H__
#define GEOMETRIC_ENGINE_H__

#include <samplingEngine/configuration.h>
#include <samplingEngine/core.h>
#include <samplingEngine/record_queues.h>

#include <samplingEngineInternal/interfaces/abstractFilter.h>

namespace geometricEngine
    {
    class geometricEngine: public samplingEngine::core::coreSamplingEngine
        {
        public:
            geometricEngine();
            ~geometricEngine();

            virtual int32_t open(const struct samplingEngine::config::engineConfiguration& _configuration);
            virtual bool isOpen() const;

            // initialization
            virtual int32_t initialize();

            // destruction
            virtual int32_t close();

            virtual int32_t addFilter(samplingEngine::interfaces::abstractFilter* _filter);

            // input
            virtual int32_t processRecord(const struct samplingEngine::records::time_record*& _record);

            // output
            virtual samplingEngine::records::recordType getRecordType() const;
            virtual int32_t getDataRecord(struct samplingEngine::records::distance_record*& _record);
            virtual int32_t getStatusRecord(struct samplingEngine::records::status_record*& _record);
            virtual int32_t getTimeRecord(struct samplingEngine::records::time_record*& _record);

            virtual void cleanup_record(void*& _record) const;

        protected:
            samplingEngine::queues::record_queue input_queue;

            samplingEngine::interfaces::abstractFilterList filters;

            samplingEngine::queues::record_queue output_queue;

            int32_t process_records();

        private:
            bool geometric_engine_active;
            uint64_t maximum_sample_buffering;
        };
    }


#endif //GEOMETRIC_ENGINE_H__
