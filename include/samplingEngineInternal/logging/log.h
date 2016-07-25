#ifndef INTERNAL_SAMPLING_ENGINE_LOGGER_H__
#define INTERNAL_SAMPLING_ENGINE_LOGGER_H__

namespace samplingEngine
    {

    enum LOG_LEVELS
        {
        LOG_LEVEL_EMERGENCY=0,
        LOG_LEVEL_ALERT,
        LOG_LEVEL_CRITICAL,
        LOG_LEVEL_ERROR,
        LOG_LEVEL_WARN,
        LOG_LEVEL_NOTICE,
        LOG_LEVEL_INFO,
        LOG_LEVEL_DEBUG,

        // default log level
        LOG_LEVEL_DEFAULT=999999999999
        };

    void send_to_log(LOG_LEVELS _level, const char* _message);
    }

#endif //INTERNAL_SAMPLING_ENGINE_LOGGER_H__
