#ifndef GEOMETRIC_ENGINE_CHANNEL_OFFSETS_H__
#define GEOMETRIC_ENGINE_CHANNEL_OFFSETS_H__

#include <cstddef>
#include <map>
#include <string>

#include <samplingEngine/configuration.h>
#include <samplingEngine/channels/time_channels.h>
#include <samplingEngine/channels/distance_channels.h>
//#include <samplingEngine/channels/channel.h>

namespace geometricEngine
    {
    struct dataPoint
        {
        size_t offset;
        size_t length;
        uint16_t index;
        };

    typedef std::map<uint16_t, struct dataPoint> offsetMapping;
    typedef std::map<uint16_t, uint16_t> statusMapping;

    struct channelOffsetMap
        {
        offsetMapping channel;
        statusMapping status;
        };

    class recordOffsetMap
        {
        public:
            recordOffsetMap();
            ~recordOffsetMap();

            int32_t initialize(const struct samplingEngine::config::engineConfiguration& _configuration);
            void reset();

            int32_t storeDataValue(samplingEngine::channels::distance::distanceChannels channel, struct samplingEngine::records::distance_record*& _record);
            int32_t storeDataStatusValue(samplingEngine::channels::distance::distanceChannels channel, struct samplingEngine::records::status_record*& _record);

            int32_t storeTimeValue(samplingEngine::channels::distance::distanceChannels channel, struct samplingEngine::records::time_record*& _record);
            int32_t storeTimeStatusValue(samplingEngine::channels::distance::distanceChannels channel, struct samplingEngine::records::status_record*& _record);

        protected:
            struct channelOffsetMap timeRecords;
            struct channelOffsetMap distanceRecords;
        };
    }

#endif //GEOMETRIC_ENGINE_CHANNEL_OFFSETS_H__
