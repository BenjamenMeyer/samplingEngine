#ifndef SAMPLING_ENGINE_RECORD_QUEUES_H__
#define SAMPLING_ENGINE_RECORD_QUEUES_H__

#include <samplingEngine/records/record_type.h>
#include <samplingEngine/records/distance_record.h>
#include <samplingEngine/records/status_record.h>
#include <samplingEngine/records/time_record.h>

#include <deque>

namespace samplingEngine
    {
    namespace queues
        {

        struct record_container
            {
            samplingEngine::records::recordType record_type;
            union record_data_pointers
                {
                samplingEngine::records::time_record* time_record;
                samplingEngine::records::distance_record* distance_record;
                samplingEngine::records::status_record* status_record;
                } record_data;
            };

        typedef std::deque<struct record_container> record_queue;

        }
    }

#endif //SAMPLING_ENGINE_RECORD_QUEUES_H__
