#ifndef INTERNAL_SAMPLING_ENGINE_LOGGER_H__
#define INTERNAL_SAMPLING_ENGINE_LOGGER_H__

namespace samplingEngine
    {

    //! Log level
    /*!
     Log level specification used internally for where to send log message data.
     */
    enum LOG_LEVELS
        {
        LOG_LEVEL_EMERGENCY=0,         /*!< Emergency Logs (typically fatal) */
        LOG_LEVEL_ALERT,               /*!< Alert Logs */
        LOG_LEVEL_CRITICAL,            /*!< Critical Logs */
        LOG_LEVEL_ERROR,               /*!< Errors */
        LOG_LEVEL_WARN,                /*!< Warnings */
        LOG_LEVEL_NOTICE,              /*!< Notices */
        LOG_LEVEL_INFO,                /*!< Informational */
        LOG_LEVEL_DEBUG,               /*!< Debug */
        LOG_LEVEL_DEFAULT=999999999999 /*!< Default Configuration Log Level */
        };

    //! (Internal) Send Message to Logger
    /*!
     Common internal function used to send all log messages to the logger.
     /param _level samplingEngine::LOG_LEVELS where to send the log message
     /param _message const char* UTF-8 ASCIIZ Log Message

     .. note::

        All log messages from inside the library should be in English.
     */
    void send_to_log(LOG_LEVELS _level, const char* _message);
    }

#endif //INTERNAL_SAMPLING_ENGINE_LOGGER_H__
