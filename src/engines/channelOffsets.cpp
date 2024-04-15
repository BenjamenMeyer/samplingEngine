#include <samplingEngineInternal/geometricEngine/engine.h>
#include <samplingEngine/error_codes.h>
#include <samplingEngine/records/time_record.h>
#include <samplingEngine/records/distance_record.h>
#include <samplingEngine/records/status_record.h>

namespace geometricEngine {

recordOffsetMap::recordOffsetMap()
    {
    reset();
    }
recordOffsetMap::~recordOffsetMap()
    {
    reset();
    }

int32_t recordOffsetMap::initialize(const struct samplingEngine::config::engineConfiguration& _configuration)
    {
    int32_t returnValue = SAMPLING_ENGINE_MAKE_ERROR_CODE(SAMPLING_ENGINE_ERROR_SUCCESS);
    uint16_t index = 0;
    size_time_channels = 0;
    size_distance_channels = 0;
    for (auto iter = _configuration.time_channels.cbegin(); iter != _configuration.time_channels.cend(); ++iter)
        {
        struct dataPoint dp;
        dp.offset = iter->data_offset;
        dp.length = iter->byte_count;
        dp.index = index;
        dp.zero_on_invalid = iter->zero_on_invalid;

        size_time_channels += iter->byte_count;

        timeRecords.channel[iter->channel_type] = dp;
        timeRecords.status[iter->channel_type] = index;
        }
    count_time_channels = index + 1;
    if ((sizeof(samplingEngine::records::time_record) + size_time_channels) > samplingEngine::records::time_record_max_size)
        {
        returnValue = SAMPLING_ENGINE_MAKE_ERROR_CODE(SAMPLING_ENGINE_ERROR_TOO_MANY_TIME_CHANNELS);
        return returnValue;
        }
    if ((sizeof(samplingEngine::records::status_record) + (sizeof(samplingEngine::records::status_record_entry)*count_time_channels)) > samplingEngine::records::status_record_max_size)
        {
        returnValue = SAMPLING_ENGINE_MAKE_ERROR_CODE(SAMPLING_ENGINE_ERROR_TOO_MANY_TIME_CHANNELS);
        return returnValue;
        }

    index = 0;
    for (auto iter = _configuration.distance_channels.cbegin(); iter != _configuration.distance_channels.cend(); ++iter)
        {
        struct dataPoint dp;
        dp.offset = iter->data_offset;
        dp.length = iter->byte_count;
        dp.index = index;
        dp.zero_on_invalid = iter->zero_on_invalid;

        size_distance_channels += iter->byte_count;

        distanceRecords.channel[iter->channel_type] = dp;
        distanceRecords.status[iter->channel_type] = index;
        }
    count_distance_channels = index + 1;
    if ((sizeof(samplingEngine::records::distance_record) + size_distance_channels) > samplingEngine::records::distance_record_max_size)
        {
        returnValue = SAMPLING_ENGINE_MAKE_ERROR_CODE(SAMPLING_ENGINE_ERROR_TOO_MANY_DISTNACE_CHANNELS);
        return returnValue;
        }
    if ((sizeof(samplingEngine::records::status_record) + (sizeof(samplingEngine::records::status_record_entry)*count_distance_channels)) > samplingEngine::records::status_record_max_size)
        {
        returnValue = SAMPLING_ENGINE_MAKE_ERROR_CODE(SAMPLING_ENGINE_ERROR_TOO_MANY_TIME_CHANNELS);
        return returnValue;
        }

    return returnValue;
    }

void recordOffsetMap::reset()
    {
    count_time_channels = 0;
    size_time_channels = 0;
    count_distance_channels = 0;
    size_distance_channels = 0;
    distanceRecords.channel.clear();
    distanceRecords.status.clear();
    timeRecords.channel.clear();
    timeRecords.status.clear();
    }

int32_t recordOffsetMap::storeDataValue(samplingEngine::channels::distance::distanceChannels /* channel */, struct samplingEngine::records::distance_record*& /* _record */)
    {
    int32_t returnValue = SAMPLING_ENGINE_MAKE_ERROR_CODE(SAMPLING_ENGINE_ERROR_SUCCESS);
    return returnValue;
    }

int32_t recordOffsetMap::storeDataStatusValue(samplingEngine::channels::distance::distanceChannels /* channel */, struct samplingEngine::records::status_record*& /* _record */)
    {
    int32_t returnValue = SAMPLING_ENGINE_MAKE_ERROR_CODE(SAMPLING_ENGINE_ERROR_SUCCESS);
    return returnValue;
    }

int32_t recordOffsetMap::storeTimeValue(samplingEngine::channels::distance::distanceChannels /* channel */, struct samplingEngine::records::time_record*& /* _record */)
    {
    int32_t returnValue = SAMPLING_ENGINE_MAKE_ERROR_CODE(SAMPLING_ENGINE_ERROR_SUCCESS);
    return returnValue;
    }

int32_t recordOffsetMap::storeTimeStatusValue(samplingEngine::channels::distance::distanceChannels /* channel */, struct samplingEngine::records::status_record*& /* _record */)
    {
    int32_t returnValue = SAMPLING_ENGINE_MAKE_ERROR_CODE(SAMPLING_ENGINE_ERROR_SUCCESS);
    return returnValue;
    }

uint16_t recordOffsetMap::time_channel_count() const
    {
    return count_time_channels;
    }

size_t recordOffsetMap::time_channel_size() const
    {
    return size_time_channels;
    }

uint16_t recordOffsetMap::distance_channel_count() const
    {
    return count_distance_channels;
    }

size_t recordOffsetMap::distance_channel_size() const
    {
    return size_distance_channels;
    }
}
