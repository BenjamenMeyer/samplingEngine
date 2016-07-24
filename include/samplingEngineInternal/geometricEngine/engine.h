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

            // startup the geometric engine and configure it with the given configuration data
            virtual int32_t open(const struct samplingEngine::config::engineConfiguration& _configuration);
            // determine whether or not the geometry engine has been opened and configured
            virtual bool isOpen() const;

            // initialization
            virtual int32_t initialize();

            // destruction
            virtual int32_t close();

            // Add a single filter to the listing
            virtual int32_t addFilter(samplingEngine::interfaces::abstractFilter* _filter);
            // Add a series of filters that are dependent on each other, e.g potentially circular dependencies
            // it is up to the filter creators to ensure the filters work correctly even though they are seemingly circular
            virtual int32_t addInterdependentFilters(samplingEngine::interfaces::abstractFilterList& _interdependentFilters);

            // input
            virtual int32_t processRecord(const struct samplingEngine::records::time_record*& _record);

            // output
            virtual samplingEngine::records::recordType getTimeRecordType() const;
            virtual samplingEngine::records::recordType getDistanceRecordType() const;
            virtual int32_t getDataRecord(struct samplingEngine::records::distance_record*& _record);
            virtual int32_t getStatusRecord(struct samplingEngine::records::status_record*& _record);
            virtual int32_t getTimeRecord(struct samplingEngine::records::time_record*& _record);

            // release memory associated with the record
            virtual void cleanup_record(void*& _record) const;

        protected:
            // record data provided as input
            samplingEngine::queues::record_queue input_queue;

            // list of filters to apply
            samplingEngine::interfaces::abstractFilterList filters;

            // list of records ready for output
            samplingEngine::queues::record_queue output_queue;

            // process the records in the input queue through the filtesr and generate any output
            // records as necessary
            int32_t process_records();

        private:
            // basic state of the engine - open (true) or closed (false)
            bool geometric_engine_active;
            // number of distance samples necessary for all channels to be valid assuming data is
            // within the tolerances of all the filters
            uint64_t maximum_sample_buffering;
        };
    }


#endif //GEOMETRIC_ENGINE_H__
