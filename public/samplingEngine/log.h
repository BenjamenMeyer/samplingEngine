#ifndef SAMPLING_ENGINE_LOG_H__
#define SAMPLING_ENGINE_LOG_H__

namespace samplingEngine
    {
    namespace logging
        {
        class samplingEngineLogger
            {
            public:
                samplingEngineLogger();
                virtual ~samplingEngineLogger();

                virtual void emergency(const char* _message)=0;
                virtual void alert(const char* _message)=0;
                virtual void critical(const char* _message)=0;
                virtual void error(const char* _message)=0;
                virtual void warn(const char* _message)=0;
                virtual void notice(const char* _message)=0;
                virtual void info(const char* _message)=0;
                virtual void debug(const char* _message)=0;
            };
        }
    }

#endif //SAMPLING_ENGINE_LOG_H__
