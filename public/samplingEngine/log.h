#ifndef SAMPLING_ENGINE_LOG_H__
#define SAMPLING_ENGINE_LOG_H__

namespace samplingEngine
    {
    namespace logging
        {
        //! Log Interface
        /*!
         Interface to extract log messages from inside the sampling engine.
         */
        class samplingEngineLogger
            {
            public:
                //! Constructor
                samplingEngineLogger();
                //! Destructor
                virtual ~samplingEngineLogger();

                //! Log message at Emergency Log Level
                /*!
                  \param _message a constant character pointer to an ASCIIZ string to be sent to the log
                 */
                virtual void emergency(const char* _message)=0;
                //! Log message at Alert Log Level
                /*!
                  \param _message a constant character pointer to an ASCIIZ string to be sent to the log
                 */
                virtual void alert(const char* _message)=0;
                //! Log message at Critical Log Level
                /*!
                  \param _message a constant character pointer to an ASCIIZ string to be sent to the log
                 */
                virtual void critical(const char* _message)=0;
                //! Log message at Error Log Level
                /*!
                  \param _message a constant character pointer to an ASCIIZ string to be sent to the log
                 */
                virtual void error(const char* _message)=0;
                //! Log message at Warning Log Level
                /*!
                  \param _message a constant character pointer to an ASCIIZ string to be sent to the log
                 */
                virtual void warn(const char* _message)=0;
                //! Log message at Notice Log Level
                /*!
                  \param _message a constant character pointer to an ASCIIZ string to be sent to the log
                 */
                virtual void notice(const char* _message)=0;
                //! Log message at Info Log Level
                /*!
                  \param _message a constant character pointer to an ASCIIZ string to be sent to the log
                 */
                virtual void info(const char* _message)=0;
                //! Log message at Debug Log Level
                /*!
                  \param _message a constant character pointer to an ASCIIZ string to be sent to the log
                 */
                virtual void debug(const char* _message)=0;
            };
        }
    }

#endif //SAMPLING_ENGINE_LOG_H__
