#ifndef SAMPLE_ENGINE_TESTING__TEST_LOGGER_H__
#define SAMPLE_ENGINE_TESTING__TEST_LOGGER_H__

#include <stdio.h>

#include <samplingEngine/log.h>


class testLogger: public samplingEngine::logging::samplingEngineLogger
    {
    public:
        testLogger() : samplingEngineLogger() {}
        ~testLogger() {}

        void emergency(const char* _message) { fprintf(stdout, "EMERGENCY: %s\n", _message); }
            void alert(const char* _message) { fprintf(stdout, "    ALERT: %s\n", _message); }
         void critical(const char* _message) { fprintf(stdout, " CRITICAL: %s\n", _message); }
            void error(const char* _message) { fprintf(stdout, "    ERROR: %s\n", _message); }
             void warn(const char* _message) { fprintf(stdout, "     WARN: %s\n", _message); }
           void notice(const char* _message) { fprintf(stdout, "   NOTICE: %s\n", _message); }
             void info(const char* _message) { fprintf(stdout, "     INFO: %s\n", _message); }
            void debug(const char* _message) { fprintf(stdout, "    DEBUG: %s\n", _message); }
    };

#endif //SAMPLE_ENGINE_TESTING__TEST_LOGGER_H__
