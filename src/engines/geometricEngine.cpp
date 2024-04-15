#include <samplingEngineInternal/geometricEngine/engine.h>
#include <samplingEngine/error_codes.h>
#include <samplingEngine/records/time_record.h>
#include <samplingEngine/records/distance_record.h>
#include <samplingEngine/records/status_record.h>

#include <stdlib.h>
#include <string.h>

namespace geometricEngine {

// status records have a structure that make up each channel entry
inline size_t calculateStatusRecordSize(uint16_t _channel_count)
    {
    size_t status_size = sizeof(samplingEngine::records::status_record);
    status_size += (sizeof(samplingEngine::records::status_record_entry) * _channel_count);
    return status_size;
    }

geometricEngine::geometricEngine() : samplingEngine::core::coreSamplingEngine()
    {
    geometric_engine_active = false;
    maximum_sample_buffering = 0;
    current_distance_record = 0;
    }

geometricEngine::~geometricEngine()
    {
    filters.clear();
    }

bool geometricEngine::isOpen() const
    {
    return geometric_engine_active;
    }

int32_t geometricEngine::open(const struct samplingEngine::config::engineConfiguration& _configuration)
    {
    // TODO: build out the configuration
    int32_t returnValue = SAMPLING_ENGINE_MAKE_ERROR_CODE(SAMPLING_ENGINE_ERROR_SUCCESS);
    returnValue = channelMapper.initialize(_configuration);
    if (SAMPLING_ENGINE_MATCHES_ERROR_CODE(returnValue, SAMPLING_ENGINE_ERROR_SUCCESS) == true)
        {
        maximum_sample_buffering = 0;
        for (samplingEngine::interfaces::abstractFilterList::iterator iter = filters.begin(); iter != filters.end(); ++iter)
            {
            (*iter)->open(_configuration);
            maximum_sample_buffering = std::max(maximum_sample_buffering, (*iter)->required_samples());
            }
        }
    // reset the distance record counter
    current_distance_record = 0;
    return returnValue;
    }

// initialization
int32_t geometricEngine::initialize()
    {
    int32_t returnValue = SAMPLING_ENGINE_MAKE_ERROR_CODE(SAMPLING_ENGINE_ERROR_SUCCESS);
    for (samplingEngine::interfaces::abstractFilterList::iterator iter = filters.begin(); iter != filters.end(); ++iter)
        {
        (*iter)->reset();
        }
    return returnValue;
    }

// destruction
int32_t geometricEngine::close()
    {
    int32_t returnValue = SAMPLING_ENGINE_MAKE_ERROR_CODE(SAMPLING_ENGINE_ERROR_SUCCESS);
    for (samplingEngine::interfaces::abstractFilterList::iterator iter = filters.begin(); iter != filters.end(); ++iter)
        {
        (*iter)->close();
        }
    return returnValue;
    }

int32_t geometricEngine::addFilter(samplingEngine::interfaces::abstractFilter* _filter)
    {
    int32_t returnValue = SAMPLING_ENGINE_MAKE_ERROR_CODE(SAMPLING_ENGINE_ERROR_SUCCESS);

    if (_filter != NULL)
        {
        // ensure all dependent filters are available
        // sadly this is an O(N^2) search...
        for (samplingEngine::interfaces::filterNameList::iterator iter2 = _filter->filterDependencies().begin(); iter2 != _filter->filterDependencies().end(); ++iter2)
            {
            // check all the existing filters
            bool found_filter = false;
            for (samplingEngine::interfaces::abstractFilterList::iterator iter = filters.begin(); iter != filters.end(); ++iter)
                {
                if ((*iter)->filterName() == (*iter2))
                    {
                    _filter->add_dependencies((*iter));
                    found_filter = true;
                    break;
                    }
                }

            // if we didn't find it, update the return code and stop looking
            if (found_filter == false)
                {
                returnValue = SAMPLING_ENGINE_MAKE_ERROR_CODE(SAMPLING_ENGINE_ERROR_DEPENDENCY_NOT_FOUND);
                break;
                }
            }

        if (SAMPLING_ENGINE_MATCHES_ERROR_CODE(returnValue, SAMPLING_ENGINE_ERROR_SUCCESS) == true)
            {
            filters.push_back(_filter);
            }
        }
    else
        {
        returnValue = SAMPLING_ENGINE_MAKE_ERROR_CODE(SAMPLING_ENGINE_ERROR_INVALID_POINTER);
        }

    return returnValue;
    }

int32_t geometricEngine::addInterdependentFilters(samplingEngine::interfaces::abstractFilterList& /* _interdependentFilters */)
    {
    // filters that have seamlingly circular dependencies or close relationships
    int32_t returnValue = SAMPLING_ENGINE_MAKE_ERROR_CODE(SAMPLING_ENGINE_ERROR_NOT_SUPPORTED_YET);

    // TODO

    return returnValue;
    }

// input
int32_t geometricEngine::processRecord(const struct samplingEngine::records::time_record*& _record)
    {
    int32_t returnValue = SAMPLING_ENGINE_MAKE_ERROR_CODE(SAMPLING_ENGINE_ERROR_SUCCESS);

    if (_record != NULL)
        {
        // copy the record into the internal data so we don't need to care about what
        // happens to the incoming record and can use it as we like
        samplingEngine::queues::record_container new_record;
        new_record.record_data.time_record = (samplingEngine::records::time_record*) calloc(1, _record->length);
        memcpy(new_record.record_data.time_record, _record, _record->length);
        new_record.record_type = samplingEngine::records::TIME_RECORD_TYPE;

        // add it to the queue and process all the records
        input_queue.push_back(new_record);
        returnValue = process_records();
        }
    else
        {
        returnValue = SAMPLING_ENGINE_MAKE_ERROR_CODE(SAMPLING_ENGINE_ERROR_INVALID_POINTER);
        }

    return returnValue;
    }

// output
samplingEngine::records::recordType geometricEngine::getTimeRecordType() const
    {
    // geometricEngine right now only returns distance records
    return samplingEngine::records::INVALID_RECORD_TYPE;
    }
samplingEngine::records::recordType geometricEngine::getDistanceRecordType() const
    {
    samplingEngine::records::recordType returnValue = samplingEngine::records::INVALID_RECORD_TYPE;

    if (output_queue.size() > 0)
        {
        returnValue = output_queue.front().record_type;
        }

    return returnValue;
    }
int32_t geometricEngine::getDataRecord(struct samplingEngine::records::distance_record*& _record)
    {
    int32_t returnValue = SAMPLING_ENGINE_MAKE_ERROR_CODE(SAMPLING_ENGINE_ERROR_SUCCESS);

    if (_record == NULL)
        {
        if (output_queue.size() > 0)
            {
            if (output_queue.front().record_type == samplingEngine::records::DISTANCE_RECORD_TYPE)
                {
                _record = output_queue.front().record_data.distance_record;
                output_queue.pop_front();
                }
            else
                {
                returnValue = SAMPLING_ENGINE_MAKE_ERROR_CODE(SAMPLING_ENGINE_ERROR_FILTER_MISMATCH);
                }
            }
        else
            {
            returnValue = SAMPLING_ENGINE_MAKE_ERROR_CODE(SAMPLING_ENGINE_ERROR_NO_RECORDS_AVAILABLE);
            }
        }
    else
        {
        returnValue = SAMPLING_ENGINE_MAKE_ERROR_CODE(SAMPLING_ENGINE_ERROR_BAD_PARAMETER);
        }

    return returnValue;
    }
int32_t geometricEngine::getStatusRecord(struct samplingEngine::records::status_record*& _record)
    {
    int32_t returnValue = SAMPLING_ENGINE_MAKE_ERROR_CODE(SAMPLING_ENGINE_ERROR_SUCCESS);

    if (_record == NULL)
        {
        if (output_queue.size() > 0)
            {
            if (output_queue.front().record_type == samplingEngine::records::STATUS_RECORD_TYPE)
                {
                _record = output_queue.front().record_data.status_record;
                output_queue.pop_front();
                }
            else
                {
                returnValue = SAMPLING_ENGINE_MAKE_ERROR_CODE(SAMPLING_ENGINE_ERROR_FILTER_MISMATCH);
                }
            }
        else
            {
            returnValue = SAMPLING_ENGINE_MAKE_ERROR_CODE(SAMPLING_ENGINE_ERROR_NO_RECORDS_AVAILABLE);
            }
        }
    else
        {
        returnValue = SAMPLING_ENGINE_MAKE_ERROR_CODE(SAMPLING_ENGINE_ERROR_BAD_PARAMETER);
        }

    return returnValue;
    }
int32_t geometricEngine::getTimeRecord(struct samplingEngine::records::time_record*& _record)
    {
    int32_t returnValue = SAMPLING_ENGINE_MAKE_ERROR_CODE(SAMPLING_ENGINE_ERROR_SUCCESS);

    if (_record == NULL)
        {
        if (output_queue.size() > 0)
            {
            if (output_queue.front().record_type == samplingEngine::records::TIME_RECORD_TYPE)
                {
                _record = output_queue.front().record_data.time_record;
                output_queue.pop_front();
                }
            else
                {
                returnValue = SAMPLING_ENGINE_MAKE_ERROR_CODE(SAMPLING_ENGINE_ERROR_FILTER_MISMATCH);
                }
            }
        else
            {
            returnValue = SAMPLING_ENGINE_MAKE_ERROR_CODE(SAMPLING_ENGINE_ERROR_NO_RECORDS_AVAILABLE);
            }
        }
    else
        {
        returnValue = SAMPLING_ENGINE_MAKE_ERROR_CODE(SAMPLING_ENGINE_ERROR_BAD_PARAMETER);
        }

    return returnValue;
    }

// cleanup
void geometricEngine::cleanup_record(void*& _record) const
    {
    if (_record != NULL)
        {
        free(_record);
        _record = NULL;
        }
    }

// processing
int32_t geometricEngine::process_records()
    {
    int32_t returnValue = SAMPLING_ENGINE_MAKE_ERROR_CODE(SAMPLING_ENGINE_ERROR_SUCCESS);

    // pull the input records and push them through the filters
    while (input_queue.size() > 0)
        {
        for (samplingEngine::interfaces::abstractFilterList::iterator iter = filters.begin(); iter != filters.end(); ++iter)
            {
            (*iter)->setTimeRecordInputIndex(input_queue.front().record_data.time_record->index, maximum_sample_buffering);
            (*iter)->setTimeRecordOutputIndex(input_queue.back().record_data.time_record->index, maximum_sample_buffering);
            (*iter)->processRecord(input_queue.front().record_data.time_record);
            }
        free(input_queue.front().record_data.time_record);
        input_queue.front().record_data.time_record = NULL;
        input_queue.pop_front();
        }

    // make the output records - since their length is dynamic based
    // on configuration they must be allocated on the heap even temporarily
    struct samplingEngine::records::status_record* time_status = NULL;
    struct samplingEngine::records::status_record* distance_status = NULL;
    // time record
    struct samplingEngine::records::time_record* time_record = NULL;
    // distance record
    struct samplingEngine::records::distance_record* distance_record = NULL;

    const size_t time_status_size = calculateStatusRecordSize(channelMapper.time_channel_count());
    time_status = (samplingEngine::records::status_record*) calloc(1, time_status_size);
    if (time_status != NULL)
        {
        time_status->length = uint32_t(time_status_size);
        time_status->id = samplingEngine::records::STATUS_RECORD_TYPE;
        }
    // time record uses a byte array; its size is only known by accruing the size of all the time-based channels
    const size_t time_record_size = sizeof(samplingEngine::records::time_record) + channelMapper.time_channel_size();
    time_record = (samplingEngine::records::time_record*) calloc(1, time_record_size);
    if (time_record != NULL)
        {
        time_record->length = uint32_t(time_record_size);
        time_record->id = samplingEngine::records::TIME_RECORD_TYPE;
        }

    const size_t distance_status_size = calculateStatusRecordSize(channelMapper.distance_channel_count());
    distance_status = (samplingEngine::records::status_record*) calloc(1, distance_status_size);
    if (distance_status != NULL)
        {
        distance_status->length = uint32_t(distance_status_size);
        distance_status->id = samplingEngine::records::STATUS_RECORD_TYPE;
        }

    // distance record uses a byte array; its size is only known by accruing the size of all the distance-based channels
    const size_t distance_record_size = sizeof(samplingEngine::records::distance_record) + channelMapper.time_channel_size();
    distance_record = (samplingEngine::records::distance_record*) calloc(1, distance_record_size);
    if (distance_record != NULL)
        {
        distance_record->length = uint32_t(distance_record_size);
        distance_record->id = samplingEngine::records::DISTANCE_RECORD_TYPE;
        }
    
    // extract the data
    for (samplingEngine::interfaces::abstractFilterList::iterator iter = filters.begin(); iter != filters.end(); ++iter)
        {
        // set the distance record data
        (*iter)->setDistanceRecordOutputIndex(current_distance_record, maximum_sample_buffering);
        if ((*iter)->isTimeBasedFilter() == true)
            {
            // update the time status record
            if (time_status != NULL)
                {
                (*iter)->updateRecord(time_status, true);
                }
            // extract a time record
            if (time_record != NULL)
                {
                (*iter)->updateRecord(time_record);
                }
            }
        if ((*iter)->isDistanceBasedFilter() == true)
            {
            // update the distance status record
            if (distance_status != NULL)
                {
                (*iter)->updateRecord(distance_status, false);
                }
            // extract a distnace record
            if (distance_record != NULL)
                {
                (*iter)->updateRecord(distance_record);
                }
            }
        }
    
    if (time_status != NULL)
        {
        samplingEngine::queues::record_container new_record;
        new_record.record_data.status_record = (samplingEngine::records::status_record*) calloc(1, time_status->length);
        if (new_record.record_data.status_record != NULL)
            {
            memcpy(new_record.record_data.status_record, time_status, time_status->length);
            new_record.record_type = samplingEngine::records::STATUS_RECORD_TYPE;
            output_queue.push_back(new_record);
            }
        }
    if (time_record != NULL)
        {
        samplingEngine::queues::record_container new_record;
        new_record.record_data.time_record = (samplingEngine::records::time_record*) calloc(1, time_record->length);
        if (new_record.record_data.time_record != NULL)
            {
            memcpy(new_record.record_data.time_record, time_record, time_record->length);
            new_record.record_type = samplingEngine::records::TIME_RECORD_TYPE;
            output_queue.push_back(new_record);
            }
        }
    if (distance_status != NULL)
        {
        samplingEngine::queues::record_container new_record;
        new_record.record_data.status_record = (samplingEngine::records::status_record*) calloc(1, distance_status->length);
        if (new_record.record_data.status_record != NULL)
            {
            memcpy(new_record.record_data.status_record, distance_status, distance_status->length);
            new_record.record_type = samplingEngine::records::STATUS_RECORD_TYPE;
            output_queue.push_back(new_record);
            }
        }
    if (distance_record != NULL)
        {
        samplingEngine::queues::record_container new_record;
        new_record.record_data.distance_record = (samplingEngine::records::distance_record*) calloc(1, distance_record->length);
        if (new_record.record_data.distance_record != NULL)
            {
            memcpy(new_record.record_data.distance_record, distance_record, distance_record->length);
            new_record.record_type = samplingEngine::records::DISTANCE_RECORD_TYPE;
            output_queue.push_back(new_record);
            }
        }

    #define CLEANUP_MEMORY(p) \
       {                      \
       if (p != NULL )        \
           {                  \
           free(p);           \
           }                  \
       }
    CLEANUP_MEMORY(time_status);
    CLEANUP_MEMORY(time_record);
    CLEANUP_MEMORY(distance_status);
    CLEANUP_MEMORY(distance_record);

    return returnValue;
    }

}
