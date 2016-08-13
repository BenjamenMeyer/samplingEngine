#ifndef SAMPLING_ENGINE_ENGINE_H__
#define SAMPLING_ENGINE_ENGINE_H__

#include <stdint.h>

#include <string>

#include <samplingEngine/configuration.h>
#include <samplingEngine/core.h>
#include <samplingEngine/records/distance_record.h>
#include <samplingEngine/log.h>
#include <samplingEngine/record_queues.h>
#include <samplingEngine/records/record_type.h>
#include <samplingEngine/records/status_record.h>
#include <samplingEngine/records/time_record.h>

namespace samplingEngine
    {
    //! Public interface to the sampleEngine library
    class samplingEngine
        {
        public:
            //! Sample Engine State
            enum sampleEngineState
                {
                SAMPLE_ENGINE_NOT_INITIALIZED = 0,                                                                       /*!< Sampling Engine has not been initialized with a configuration yet */
                SAMPLE_ENGINE_INITIALIZED = 1,                                                                           /*!< Sampling Engine has been initialized and is ready for use */
                SAMPLE_ENGINE_DIAGNOSTIC_MODE = 2,                                                                       /*!< Sampling Engine is in diagnostic mode */
                SAMPLE_ENGINE_CALIBRATION_MODE = 4,                                                                      /*!< Sampling Engine is in calibration mode */
                SAMPLE_ENGINE_OPERATION_MODE = 8,                                                                        /*!< Sampling Engine is in operations mode */
                SAMPLE_ENGINE_OPERATIONAL_STARTUP = 16,                                                                  /*!< Sampling Engine is starting up for operation, priming filters, etc */
                SAMPLE_ENGINE_OPERATIONAL_READY = 32,                                                                    /*!< Sampling Engine is ready for data collection output */
                SAMPLE_ENGINE_OPERATIONAL_SHUTDOWN = 64,                                                                 /*!< Sampling Engine is being shutdown */

                SAMPLE_ENGINE_DESTRUCTION = 0xFFFFFFFFFFFFFFFF,                                                          /*!< Sampling Engine is shutting down for destruction */

                // The values below are convenience names
                SAMPLE_ENGINE_IN_STANDBY = SAMPLE_ENGINE_INITIALIZED,                                                    /*!< Alternate name for sampleEngine::samplingEngine::SAMPLE_ENGINE_INITIALIZED */

                // Operational Modes:
                //    Startup - filters not yet primed, some filters may be ready, some not
                //  Ready - all filters primed and ready
                //  Shutdown - pushing data out, some filters may be ready, some not
                SAMPLE_ENGINE_IN_OPERATION = SAMPLE_ENGINE_INITIALIZED|SAMPLE_ENGINE_OPERATION_MODE,                     /*!< Initialized and in Operations Mode */
                SAMPLE_ENGINE_IN_OPERATION_STARTUP = SAMPLE_ENGINE_IN_OPERATION|SAMPLE_ENGINE_OPERATIONAL_STARTUP,       /*!< Initialized, in Operations Mode, and Starting Up */
                SAMPLE_ENGINE_IN_OPERATION_READY = SAMPLE_ENGINE_IN_OPERATION|SAMPLE_ENGINE_OPERATIONAL_READY,           /*!< Initialized, in Operations Mode, and Ready for use */
                SAMPLE_ENGINE_IN_OPERATION_SHUTDOWN = SAMPLE_ENGINE_IN_OPERATION|SAMPLE_ENGINE_OPERATIONAL_SHUTDOWN,     /*!< Initialized, in Operations Mode, and Shutting Down */

                // Diagnostics Modes:
                //    Startup - filters not yet primed, some filters may be ready, some not
                //  Ready - all filters primed and ready
                //  Shutdown - pushing data out, some filters may be ready, some not
                SAMPLE_ENGINE_IN_DIAGNOSTICS = SAMPLE_ENGINE_INITIALIZED|SAMPLE_ENGINE_DIAGNOSTIC_MODE,                  /*!< Initialaized and in Diagnostics mode */
                SAMPLE_ENGINE_IN_DIAGNOSTICS_STARTUP = SAMPLE_ENGINE_IN_DIAGNOSTICS|SAMPLE_ENGINE_OPERATIONAL_STARTUP,   /*!< Initialized, in Diagnostics Mode, and Starting Up */
                SAMPLE_ENGINE_IN_DIAGNOSTICS_READY = SAMPLE_ENGINE_IN_DIAGNOSTICS|SAMPLE_ENGINE_OPERATIONAL_READY,       /*!< Initialized, in Diagnostics Mode, and Ready for use */
                SAMPLE_ENGINE_IN_DIAGNOSTICS_SHUTDOWN = SAMPLE_ENGINE_IN_DIAGNOSTICS|SAMPLE_ENGINE_OPERATIONAL_SHUTDOWN, /*!< Initialized, in Diagnostics Mode, and Shutting Down */

                // Calibration Modes:
                //    Startup - filters not yet primed, some filters may be ready, some not
                //  Ready - all filters primed and ready
                //  Shutdown - pushing data out, some filters may be ready, some not
                SAMPLE_ENGINE_IN_CALIBRATION = SAMPLE_ENGINE_INITIALIZED|SAMPLE_ENGINE_CALIBRATION_MODE,                 /*!< Initialized and in Calibration Mode */
                SAMPLE_ENGINE_IN_CALIBRATION_STARTUP = SAMPLE_ENGINE_IN_CALIBRATION|SAMPLE_ENGINE_OPERATIONAL_STARTUP,   /*!< Initialized, in Calibration Mode, and Startup Up */
                SAMPLE_ENGINE_IN_CALIBRATION_READY = SAMPLE_ENGINE_IN_CALIBRATION|SAMPLE_ENGINE_OPERATIONAL_READY,       /*!< Initialized, in Calibration Mode, and Ready for use */
                SAMPLE_ENGINE_IN_CALIBRATION_SHUTDOWN = SAMPLE_ENGINE_IN_CALIBRATION|SAMPLE_ENGINE_OPERATIONAL_SHUTDOWN, /*!< Initialized, in Calibration Mode, and Shutting Down */
                };

            //! Constructor
            /*!
             Create an instance of the Sampling Engine
             /param _logger samplingEngine::logging::samplingEngineLogger an instance of object implementing the samplingEngineLogger interface
                    for the samplingEngine to write out any log information to. If none is specified, then no logs will be recorded.
             */
            samplingEngine(logging::samplingEngineLogger* _logger=NULL);
            //! Destructor
            ~samplingEngine();

            //! Set a new logger interface
            /*!
             Specify the samplingEngine use a new logger instance to write logs out to.
             /param _logger samplingEngine::logging::samplingEngineLogger an instance of the logger or NULL to disable all logging
             /returns samplingEngine::logging::samplingEngineLogger the previous logger, or NULL if no logger was set
             */
            logging::samplingEngineLogger* setLogger(logging::samplingEngineLogger* _logger);

            //! Convert an error code to a user message string
            /*!
             Retrieve an error message for a given error code for user or log purposes.
             /param _error_code uint32_t an error code from a fucntion call into the samplingEngine
             /returns std::string containing the related error message as an UTF-8 ASCIIZ text
             */
            static const std::string getErrorMessage(uint32_t _error_code);

            //! Get the state of the samplingEngine
            /*!
             Access the current state of the samplingEngine
             /returns uint32_t containing a bit-map of the samplingEngine state. Each bit maps to a
                value in the enum samplingEngine::samplingEngine::sampleEngineState.
             */
            uint32_t getState() const;

            //! Initialize the samplingEngine
            /*!
             Configure the samplingEngine so it is prepared for operational use based on the provided configuration.
             /param samplingEngine::config::engineConfiguration& sampling engine configuration
             /returns int32_t samplingEngine error code value
             */
            int32_t initialize(const struct config::engineConfiguration& _configuration);

            //! Extract unstable records from the samplingEngine before closing the engine
            /*!
             Perform a graceful shutdown of the samplingEngine allowing all the data, valid and invalid, to be retrieved.
             This is accomplished through an auto-simulation of the data until the internal buffers clear of any potential
             good derived data.
             /returns int32_t samplingEngine error code value
             */
            int32_t shutdown();

            //! Close the engine, releasing all related resources
            /*!
             Releases all buffers, resets the configuration, and destroy any remaining run-time data.
             /returns int32_t samplingEngine error code value

             .. note:: Any data not retrieved from the processing engine will automatically be destroyed
             */
            int32_t close(void);

            //! Input a Time Data Record into the samplingEngine
            /*!
             Insert a time data record into the sampling engine to apply into the Measurement Framework
             /param _record samplingEngine::records::time_record*& time data record containing sensor measurements in its data array
                in accordance with the specified Time Data Channels. Some measurements may be from another 
             */
            int32_t processRecord(const struct records::time_record*& _record);

            //! Check the if the latest available record is a Time Data Record
            /*!
             The samplingEngine generates different kinds of records. Apply a filter to only check for Time Domain Records.
             /returns samplingEngine::records::recordType
             */
            records::recordType getTimeRecordType() const;
            //! Check the if the latest available record is a Distance Data Record
            /*!
             The samplingEngine generates different kinds of records. Apply a filter to only check for Distance Domain Records.
             /returns samplingEngine::records::recordType
             */
            records::recordType getDistanceRecordType() const;
            //! Access the Distance Data Record
            /*!
             Retrieve the current Distance Data Records from the system if and only if they are at the head of the output queue
             /param samplingEngine::records::distance_record*& NULL pointer that will received an allocated record with the distance domain data
             /returns int32_t samplingEngine error code value
             */
            int32_t getDataRecord(struct records::distance_record*& _record);
            //! Access the Status Record
            /*!
             Retrieve the current Status Records from the system if and only if they are at the head of the output queue
             .. note:: Status Records may be either Time or Distance domain.
             /param samplingEngine::records::status_record*& NULL pointer that will receive an allocated record with the status record
             /returns int32_t samplingEngine error code value
             */
            int32_t getStatusRecord(struct records::status_record*& _record);
            //! Access the Time Data Record
            /*!
             Retrieve the current Time Data Records from the system if and only if they are at the head of the output queue
             /param samplingEngine::records::time_record*& NULL pointer that will receive an allocated record with the time domain data
             /returns int32_t samplingEngine error code value
             */
            int32_t getTimeRecord(struct records::time_record*& _record);

        protected:
            struct config::engineConfiguration configuration; /*!< Active Configuration */

            //! (internal) set the state
            /*!
             internally accessible function to set the state of the samplingEngine system
             /param samplingEngine::samplingEngine::sampleEngineState state bit-map to set
             */
            void setState(sampleEngineState _state);
            //! (internal) enable a specific state
            /*!
             Activate a specific state by setting its bitmap value
             /param samplingEngine::samplingEngine::sampleEngineState state bit-map to set
             */
            void enableState(sampleEngineState _state_bit);
            //! (internal) disable a specific state
            /*!
             Deactivate (or clear) a specific state by setting its bitmap value
             /param samplingEngine::samplingEngine::sampleEngineState state bit-map to set
             */
            void disableState(sampleEngineState _state_bit);
            //! (internal) check state status
            /*!
             Determine if a given state's bitmap entry is set to activate
             /param samplingEngine::samplingEngine::sampleEngineState state bit-map to set
             /returns true if set, otherwise false
             */
            bool isStateSet(sampleEngineState _state_bit) const;

        private:
            uint32_t state; /*!< Current samplingEngine State */
            queues::record_queue input_queue; /*!< Externally provided Time Data Records used for input */

            queues::record_queue intermediate_time_queue; /*!< Buffered Time Data Records that need to be delayed until the output buffers are ready */
            queues::record_queue output_time_queue; /*!< internally generated Time Data Records that have been fully updated */

            queues::record_queue intermediate_distance_queue; /*!< Buffered Distance Data Records that need to be delayed until the output buffers are ready */
            queues::record_queue output_distance_queue; /*!< internally generated Distance Data Records that have been fully updated */

            const struct records::time_record* lastTimeRecord; /*!< Last seen Time Data Record used for the samplingEngine::samplingEngine::sampleEngine::shutdown() */

            core::coreSamplingEngine* coreEngine; /*!< Active sampling engine */
        };
    }

#endif //SAMPLING_ENGINE_ENGINE_H__
