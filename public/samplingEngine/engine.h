#ifndef SAMPLING_ENGINE_ENGINE_H__
#define SAMPLING_ENGINE_ENGINE_H__

#include <stdint.h>

#include <string>

#include <samplingEngine/configuration.h>
#include <samplingEngine/core.h>
#include <samplingEngine/distance_record.h>
#include <samplingEngine/log.h>
#include <samplingEngine/record_queues.h>
#include <samplingEngine/record_type.h>
#include <samplingEngine/status_record.h>
#include <samplingEngine/time_record.h>

namespace samplingEngine
    {
    // library interface class that will be used externally
    class samplingEngine
        {
        public:
            enum sampleEngineState
                {
                // Sampling Engine has not been initialized with a configuration yet
                SAMPLE_ENGINE_NOT_INITIALIZED = 0,
                // Sampling Engine has been initialized and is ready for use
                SAMPLE_ENGINE_INITIALIZED = 1,
                // Sampling Engine is in diagnostic mode
                SAMPLE_ENGINE_DIAGNOSTIC_MODE = 2,
                // Sampling Engine is in calibration mode
                SAMPLE_ENGINE_CALIBRATION_MODE = 4,
                // Sampling Engine is in operations mode
                SAMPLE_ENGINE_OPERATION_MODE = 8,
                // Sampling Engine is starting up for operation, priming filters, etc
                SAMPLE_ENGINE_OPERATIONAL_STARTUP = 16,
                // Sampling Engine is ready for data collection output
                SAMPLE_ENGINE_OPERATIONAL_READY = 32,
                // Sampling Engine is being shutdown
                SAMPLE_ENGINE_OPERATIONAL_SHUTDOWN = 64,

                // Sampling Engine is shutting down for destruction
                SAMPLE_ENGINE_DESTRUCTION = 0xFFFFFFFFFFFFFFFF,

                // The values below are convenience names
                SAMPLE_ENGINE_IN_STANDBY = SAMPLE_ENGINE_INITIALIZED,

                // Operational Modes:
                //    Startup - filters not yet primed, some filters may be ready, some not
                //  Ready - all filters primed and ready
                //  Shutdown - pushing data out, some filters may be ready, some not
                SAMPLE_ENGINE_IN_OPERATION = SAMPLE_ENGINE_INITIALIZED|SAMPLE_ENGINE_OPERATION_MODE,
                SAMPLE_ENGINE_IN_OPERATION_STARTUP = SAMPLE_ENGINE_IN_OPERATION|SAMPLE_ENGINE_OPERATIONAL_STARTUP,
                SAMPLE_ENGINE_IN_OPERATION_READY = SAMPLE_ENGINE_IN_OPERATION|SAMPLE_ENGINE_OPERATIONAL_READY,
                SAMPLE_ENGINE_IN_OPERATION_SHUTDOWN = SAMPLE_ENGINE_IN_OPERATION|SAMPLE_ENGINE_OPERATIONAL_SHUTDOWN,

                // Diagnostics Modes:
                //    Startup - filters not yet primed, some filters may be ready, some not
                //  Ready - all filters primed and ready
                //  Shutdown - pushing data out, some filters may be ready, some not
                SAMPLE_ENGINE_IN_DIAGNOSTICS = SAMPLE_ENGINE_INITIALIZED|SAMPLE_ENGINE_DIAGNOSTIC_MODE,
                SAMPLE_ENGINE_IN_DIAGNOSTICS_STARTUP = SAMPLE_ENGINE_IN_DIAGNOSTICS|SAMPLE_ENGINE_OPERATIONAL_STARTUP,
                SAMPLE_ENGINE_IN_DIAGNOSTICS_READY = SAMPLE_ENGINE_IN_DIAGNOSTICS|SAMPLE_ENGINE_OPERATIONAL_READY,
                SAMPLE_ENGINE_IN_DIAGNOSTICS_SHUTDOWN = SAMPLE_ENGINE_IN_DIAGNOSTICS|SAMPLE_ENGINE_OPERATIONAL_SHUTDOWN,

                // Calibration Modes:
                //    Startup - filters not yet primed, some filters may be ready, some not
                //  Ready - all filters primed and ready
                //  Shutdown - pushing data out, some filters may be ready, some not
                SAMPLE_ENGINE_IN_CALIBRATION = SAMPLE_ENGINE_INITIALIZED|SAMPLE_ENGINE_CALIBRATION_MODE,
                SAMPLE_ENGINE_IN_CALIBRATION_STARTUP = SAMPLE_ENGINE_IN_CALIBRATION|SAMPLE_ENGINE_OPERATIONAL_STARTUP,
                SAMPLE_ENGINE_IN_CALIBRATION_READY = SAMPLE_ENGINE_IN_CALIBRATION|SAMPLE_ENGINE_OPERATIONAL_READY,
                SAMPLE_ENGINE_IN_CALIBRATION_SHUTDOWN = SAMPLE_ENGINE_IN_CALIBRATION|SAMPLE_ENGINE_OPERATIONAL_SHUTDOWN,
                };

            samplingEngine(logging::samplingEngineLogger* _logger=NULL);
            ~samplingEngine();


            //
            // setLogger()
            //
            // Purpose:
            //      Provide a means to record messages to an external logger
            //
            // Parameters:
            //      _logger - logging::samplingEngineLogger* - pointer to an instance of the logging::samplingEngineLogger
            //                                      that provides the complete interface
            //
            // Returns:
            //      logging::samplingEngineLogger* - pointer to the previous logger
            //
            //
            logging::samplingEngineLogger* setLogger(logging::samplingEngineLogger* _logger);

            //
            // getErrorMessage()
            //
            // Purpose:
            //    Provide a means to get a reliable human readable form of the error message
            //
            // Parameters:
            //    _error_code - int32_t - error code provided by one of the engine functions
            //
            // Returns:
            //    Human readable error message encoded as 8-bit UTF-8 ASCIIZ text
            //
            static const std::string getErrorMessage(uint32_t _error_code);

            //
            // getState()
            //
            // Purpose:
            //      Provide a means to determine the current state of the samplingEngine
            //
            // Parameters:
            //    n/a
            //
            // Returns:
            //    A bit-map of the samplingEngine state. Each bit maps to a value in the enum
            //    samplineEngine::samplingEngine::sampleEngineState.
            uint32_t getState() const;

            //
            // initialize()
            //
            // Purpose:
            //    Configure the engine and prepare for operational usage based on the configuration
            //
            // Parameters:
            //    _configuration - reference to a struct engine_configuration containing the configuration data
            //
            // Returns:
            //    integer value specifying the error code
            //
            int32_t initialize(const struct config::engineConfiguration& _configuration);

            //
            // shutdown()
            //
            // Purpose:
            //    Graceful shutdown of the engine allowing all data, valid or invalid, to be retrieved.
            //    This performs an auto-simulation of the data until the buffers clear of any good derivative data
            //     to ensure that all distance records are properly generated.
            //
            // Parameters:
            //    n/a
            //
            // Returns:
            //    integer value containing either of the following:
            //        if negative - error code
            //              if zero or postive - number of records available to be retrieved
            //
            int32_t shutdown();

            //
            // close()
            //
            // Purpose:
            //    To terminate the engine, releasing all buffers, and destroying any remaining run-time data
            //
            // Parameters:
            //    n/a
            //
            // Returns:
            //    integer value specifying the error code
            //
            //    Note: Any data not retrieved from the processing engine will automatically be destroyed
            //
            int32_t close(void);

            //
            // processRecord()
            //
            // Purpose:
            //    To input new time data into the processing engine in order to generate new distance data
            //
            // Parameters:
            //    _record - pointer to struct time_record containing a time sample to process
            //
            // Returns:
            //    integer value containing either of the following:
            //        if negative - error code
            //              if zero or postive - number of records available to be retrieved
            //
            int32_t processRecord(const struct records::time_record*& _record);

            //
            // getRecord()
            //
            // Purpose:
            //    To retrieve a generated record from the system
            //
            // Parameters:
            //    _record - reference to a pointer of the various record types - referenced pointer that will receive the record data
            //        - value must be NULL going in
            //
            // Returns:
            //    integer value containing the error
            //    if no error, then the parameters may be relied on
            //
            //    Note: When data is passed out, it must be copied from the buffer. Memory is not necessarily allocated
            //        to pass the record out of the processing engine. Memory that is allocated will be reclaimed when
            //        the next record is processed by engine_process_record(). Any previous logger objects are not
            //          automatically freed since they are always created externally.
            //
            records::recordType getTimeRecordType() const;
            records::recordType getDistanceRecordType() const;
            int32_t getDataRecord(struct records::distance_record*& _record);
            int32_t getStatusRecord(struct records::status_record*& _record);
            int32_t getTimeRecord(struct records::time_record*& _record);

        protected:
            struct config::engineConfiguration configuration;

            void setState(sampleEngineState _state);
            void enableState(sampleEngineState _state_bit);
            void disableState(sampleEngineState _state_bit);
            bool isStateSet(sampleEngineState _state_bit) const;

        private:
            uint32_t state;
            queues::record_queue input_queue;

            queues::record_queue intermediate_time_queue;
            queues::record_queue output_time_queue;

            queues::record_queue intermediate_distance_queue;
            queues::record_queue output_distance_queue;

            // core engine
            core::coreSamplingEngine* coreEngine;
        };
    }

#endif //SAMPLING_ENGINE_ENGINE_H__
