#ifndef ENGINE_RECORD_TYPE_H__
#define ENGINE_RECORD_TYPE_H__

namespace samplingEngine
    {
    namespace records
        {
        enum recordType
            {
            INVALID_RECORD_TYPE=0,
            TIME_RECORD_TYPE,
            STATUS_RECORD_TYPE,
            DISTANCE_RECORD_TYPE
            };
        }
    }

#endif //ENGINE_RECORD_TYPE_H__
