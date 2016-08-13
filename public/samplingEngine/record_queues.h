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

        //! a container to manage the record data
        /*!
         A container that describes the records traversing the sampling engine
         in a consistent format for interfacing with the engine and its components.
         */
        struct record_container
            {
            //! record type for the data tracked by the container
            samplingEngine::records::recordType record_type;
            //! record data
            /*!
             The actual data being managed by the container; which value is active is
             based on the `record_type` value.
             */
            union record_data_pointers
                {
                //! Time Record reference if `record_type` specifies a time-based record.
                samplingEngine::records::time_record* time_record;
                //! Distanec Record reference if `record_type` specifies a distance-based record.
                samplingEngine::records::distance_record* distance_record;
                //! Status Record reference if `record_type` specifies a status record.
                samplingEngine::records::status_record* status_record;
                } record_data;
            };

        //! container used to manage data records
        /*!
         A listing of records used to keep track of a series of records.
         */
        typedef std::deque<struct record_container> record_queue;

        }
    }

#endif //SAMPLING_ENGINE_RECORD_QUEUES_H__
