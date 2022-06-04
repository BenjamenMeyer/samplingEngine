#include <samplingEngineInternal/geometricEngine/engine.h>
#include <samplingEngine/error_codes.h>

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
    for (auto iter = _configuration.time_channels.cbegin(); iter != _configuration.time_channels.cend(); ++iter)
        {
        struct dataPoint dp;
        dp.offset = iter->data_offset;
        dp.length = iter->byte_count;
        dp.index = index;
        timeRecords.channel[iter->channel_type] = dp;

        timeRecords.status[iter->channel_type] = index;
        }

    index = 0;
    for (auto iter = _configuration.distance_channels.cbegin(); iter != _configuration.distance_channels.cend(); ++iter)
        {
        struct dataPoint dp;
        dp.offset = iter->data_offset;
        dp.length = iter->byte_count;
        dp.index = index;
        distanceRecords.channel[iter->channel_type] = dp;

        distanceRecords.status[iter->channel_type] = index;
        }

    return returnValue;
    }

void recordOffsetMap::reset()
    {
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

}
