#include <samplingEngineInternal/geometricEngine/engine.h>
#include <samplingEngine/error_codes.h>

#include <stdlib.h>
#include <string.h>

namespace geometricEngine {

geometricEngine::geometricEngine() : samplingEngine::core::coreSamplingEngine()
    {
    geometric_engine_active = false;
    maximum_sample_buffering = 0;
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
    int32_t returnValue = SAMPLING_ENGINE_MAKE_ERROR_CODE(SAMPLING_ENGINE_ERROR_SUCCESS);
    maximum_sample_buffering = 0;
    for (samplingEngine::interfaces::abstractFilterList::iterator iter = filters.begin(); iter != filters.end(); ++iter)
        {
        (*iter)->open();
        maximum_sample_buffering = std::max(maximum_sample_buffering, (*iter)->required_samples());
        }
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
int32_t geometricEngine::addInterdependentFilters(samplingEngine::interfaces::abstractFilterList& _interdependentFilters)
    {
    int32_t returnValue = SAMPLING_ENGINE_MAKE_ERROR_CODE(SAMPLING_ENGINE_ERROR_SUCCESS);

    // TODO

    return returnValue;
    }

// input
int32_t geometricEngine::processRecord(const struct samplingEngine::records::time_record*& _record)
    {
    int32_t returnValue = SAMPLING_ENGINE_MAKE_ERROR_CODE(SAMPLING_ENGINE_ERROR_SUCCESS);

    if (_record != NULL)
        {
        samplingEngine::queues::record_container new_record;
        new_record.record_data.time_record = (samplingEngine::records::time_record*) calloc(1, _record->length);
        memcpy(new_record.record_data.time_record, _record, _record->length);
        new_record.record_type = samplingEngine::records::TIME_RECORD_TYPE;
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

    while (input_queue.size() > 0)
        {
        for (samplingEngine::interfaces::abstractFilterList::iterator iter = filters.begin(); iter != filters.end(); ++iter)
            {
            (*iter)->processRecord(input_queue.front().record_data.time_record);
            }
        free(input_queue.front().record_data.time_record);
        input_queue.front().record_data.time_record = NULL;
        input_queue.pop_front();

        // TODO:
        //    1. Extract data
        //    2. Delay the data appropriately
        //    3. Build a status record
        //  3.1 Add to output queue
        //    4. Build a time record
        //    4.1 Build Record
        //    4.2 Add to output queue
        //    5. Build a distance record
        //    5.1 Build Record
        //    5.2 Add to output queue
        }

    return returnValue;
    }

}
