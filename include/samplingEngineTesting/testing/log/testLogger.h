#ifndef SAMPLE_ENGINE_TESTING__TEST_LOGGER_H__
#define SAMPLE_ENGINE_TESTING__TEST_LOGGER_H__

#include <stdio.h>

#include <samplingEngine/log.h>


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
        testLogger() : samplingEngineLogger() {}
        //! Destructor
        /*! No-Op cleanup */
        ~testLogger() {}

        //! Emergency Level Log Messages
        /*!
         Record a message to the logger as an emergency level
         /param _message const char* ASCIIZ string containing the message to record
         */
        void emergency(const char* _message) { fprintf(stdout, "EMERGENCY: %s\n", _message); }
        //! Alert Level Log Messages
        /*!
         Record a message to the logger as an alert level
         /param _message const char* ASCIIZ string containing the message to record
         */
        void alert(const char* _message) { fprintf(stdout, "    ALERT: %s\n", _message); }
        //! Critical Level Log Messages
        /*!
         Record a message to the logger as a critical level
         /param _message const char* ASCIIZ string containing the message to record
         */
         void critical(const char* _message) { fprintf(stdout, " CRITICAL: %s\n", _message); }
        //! Error Level Log Messages
        /*!
         Record a message to the logger as an error level
         /param _message const char* ASCIIZ string containing the message to record
         */
        void error(const char* _message) { fprintf(stdout, "    ERROR: %s\n", _message); }
        //! Warning Level Log Messages
        /*!
         Record a message to the logger as a warning level
         /param _message const char* ASCIIZ string containing the message to record
         */
        void warn(const char* _message) { fprintf(stdout, "     WARN: %s\n", _message); }
        //! Notice Level Log Messages
        /*!
         Record a message to the logger as a notice level
         /param _message const char* ASCIIZ string containing the message to record
         */
        void notice(const char* _message) { fprintf(stdout, "   NOTICE: %s\n", _message); }
        //! Informational Level Log Messages
        /*!
         Record a message to the logger as an information level
         /param _message const char* ASCIIZ string containing the message to record
         */
        void info(const char* _message) { fprintf(stdout, "     INFO: %s\n", _message); }
        //! Debug Level Log Messages
        /*!
         Record a message to the logger as a debug level
         /param _message const char* ASCIIZ string containing the message to record
         */
        void debug(const char* _message) { fprintf(stdout, "    DEBUG: %s\n", _message); }
    };

#endif //SAMPLE_ENGINE_TESTING__TEST_LOGGER_H__
