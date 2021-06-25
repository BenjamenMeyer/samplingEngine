#ifndef SAMPLE_ENGINE_TESTING__TEST_LOGGER_H__
#define SAMPLE_ENGINE_TESTING__TEST_LOGGER_H__

#include <stdio.h>

#include <samplingEngine/log.h>
#include <samplingEngineInternal/logging/log.h>

//! Callback Function Definition for testing the log levels
/*!
 When a log message is received by testLogger, then if the callback function is set it will call out to that function
 which can then perform tests to ensure the correct log level and message were being sent.
 /param _level samplingEngine::LOG_LEVELS enum for the log level being generated
 /param _message const char* ASCIIZ message that is being sent to the logger.
 */
class testLoggerCallback
	{
	public:
		virtual void callback(samplingEngine::LOG_LEVELS _level, const char* _message)=0;
	};



//! Logger implementation for Unit Tests
/*!
 In order to test certain functionality a logging interface must be implemented.
 This provides a minimal and very basic logging implementation that adheres to the
 samplingEngine::logging::samplingEngineLogger interface specification. All messages
 are simply written to Standard Out (stdout), making debugging easier.
 */
class testLogger: public samplingEngine::logging::samplingEngineLogger
    {
    public:
        //! Constructor
        /*! Initialize the Sampling Engine Logger */
        testLogger(testLoggerCallback *_callback=NULL) : samplingEngineLogger(), callback(_callback) {}
        //! Destructor
        /*! No-Op cleanup */
        ~testLogger() {}

        //! Emergency Level Log Messages
        /*!
         Record a message to the logger as an emergency level
         /param _message const char* ASCIIZ string containing the message to record
         */
        void emergency(const char* _message) { fprintf(stdout, "EMERGENCY: %s\n", _message); DO_CALLBACK(samplingEngine::LOG_LEVEL_EMERGENCY, _message); }
        //! Alert Level Log Messages
        /*!
         Record a message to the logger as an alert level
         /param _message const char* ASCIIZ string containing the message to record
         */
        void alert(const char* _message) { fprintf(stdout, "    ALERT: %s\n", _message); DO_CALLBACK(samplingEngine::LOG_LEVEL_ALERT, _message); }
        //! Critical Level Log Messages
        /*!
         Record a message to the logger as a critical level
         /param _message const char* ASCIIZ string containing the message to record
         */
        void critical(const char* _message) { fprintf(stdout, " CRITICAL: %s\n", _message); DO_CALLBACK(samplingEngine::LOG_LEVEL_CRITICAL, _message); }
        //! Error Level Log Messages
        /*!
         Record a message to the logger as an error level
         /param _message const char* ASCIIZ string containing the message to record
         */
        void error(const char* _message) { fprintf(stdout, "    ERROR: %s\n", _message); DO_CALLBACK(samplingEngine::LOG_LEVEL_ERROR, _message); }
        //! Warning Level Log Messages
        /*!
         Record a message to the logger as a warning level
         /param _message const char* ASCIIZ string containing the message to record
         */
        void warn(const char* _message) { fprintf(stdout, "     WARN: %s\n", _message); DO_CALLBACK(samplingEngine::LOG_LEVEL_WARN, _message); }
        //! Notice Level Log Messages
        /*!
         Record a message to the logger as a notice level
         /param _message const char* ASCIIZ string containing the message to record
         */
        void notice(const char* _message) { fprintf(stdout, "   NOTICE: %s\n", _message); DO_CALLBACK(samplingEngine::LOG_LEVEL_NOTICE, _message); }
        //! Informational Level Log Messages
        /*!
         Record a message to the logger as an information level
         /param _message const char* ASCIIZ string containing the message to record
         */
        void info(const char* _message) { fprintf(stdout, "     INFO: %s\n", _message); DO_CALLBACK(samplingEngine::LOG_LEVEL_INFO, _message); }
        //! Debug Level Log Messages
        /*!
         Record a message to the logger as a debug level
         /param _message const char* ASCIIZ string containing the message to record
         */
        void debug(const char* _message) { fprintf(stdout, "    DEBUG: %s\n", _message); DO_CALLBACK(samplingEngine::LOG_LEVEL_DEBUG, _message); }

	protected:
		//! Callback Function for testing the log levels
		/*!
		 When a log message is received by testLogger, then if the callback function is set it will call out to that function
		 which can then perform tests to ensure the correct log level and message were being sent.
		 /param _level samplingEngine::LOG_LEVELS enum for the log level being generated
		 /param _message const char* ASCIIZ message that is being sent to the logger.
		 */
		testLoggerCallback *callback;

		//! Macro for making it easier to call the callback
		/*!
		 When a log message is received by testLogger, then if the callback function is set it will call out to that function
		 which can then perform tests to ensure the correct log level and message were being sent.
		 /param level samplingEngine::LOG_LEVELS enum for the log level being generated without the namespace prefix since the Macro can add it
		 /param msg const char* ASCIIZ message that is being sent to the logger.
		 */
		inline void DO_CALLBACK(samplingEngine::LOG_LEVELS _level, const char* _msg)
			{
			if (callback != NULL)
				{
				callback->callback(_level, _msg);
				}
			}
    };

// Reset the Macro so it doesn't escape the header
#undef DO_CALLBACK

#endif //SAMPLE_ENGINE_TESTING__TEST_LOGGER_H__
