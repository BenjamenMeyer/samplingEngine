#ifndef SAMPLING_ENGINE_CORE_H__
#define SAMPLING_ENGINE_CORE_H__

#include <samplingEngine/configuration.h>
#include <samplingEngine/core.h>
#include <samplingEngine/records/distance_record.h>
#include <samplingEngine/records/record_type.h>
#include <samplingEngine/records/status_record.h>
#include <samplingEngine/records/time_record.h>

namespace samplingEngine
    {
    namespace core
        {
        //! Public Interface of the internal sampling engine
        /*!
         The samplingEngine class is a wrapper that provides access to one or more specialized
         sampling engines. This class defines the public interface - what is known external to
         the library - for the internally implemented engines.
         */
        class coreSamplingEngine
            {
            public:
                //! Constructor
                /*!
                 Create an instance of the engine with all requisite base resources.
                 */
                coreSamplingEngine();
                //! Destructor
                /*!
                 Cleanup the instance of the engine and all resources on destruction.
                 */
                virtual ~coreSamplingEngine();

                //! Startup the engine for use, and provide the configuration
                /*!
                 Configure the engine for use, and start it up but do not initialize it.
                 \param _configuration const struct sampleEngine::config::engineConfiguration the configuration for the measurements, filters, etc.
                 \return int32_t containing a Sample Engine Error Code, see sampleEngine/error_codes.h
                 */
                virtual int32_t open(const struct config::engineConfiguration& _configuration)=0;
                //! Check whether the engine has been openned
                /*!
                 Check whether open() has been called and the configuration provided.
                 \return bool true if openned, otherwise false
                 */
                virtual bool isOpen() const=0;
                //! Initialize the engine
                /*!
                 Initialize the engine and apply the configuration to load the filters, measurements,
                 channels, etc.
                 \return int32_t containing a Sample Engine Error Code, see sampleEngine/error_codes.h
                 */
                virtual int32_t initialize()=0;
                //! Shutdown the engine and destroy all run-time resources.
                /*!
                 Shutdown the engine and clear out all resources, losing all remaining records.
                 \return int32_t containing a Sample Engine Error Code, see sampleEngine/error_codes.h

                 .. note:: For distance-based records it is recommended to run a simulated encoder
                    signal for the length of the delay buffer (maximum number of samples before all
                    signals could be good) to extract all data. However, keep in mind that data during
                    this segment will be skewed due to the simulation and thereby should be treated
                    as unreliable.
                 */
                virtual int32_t close()=0;

                // Process a Time Record
                /*!
                 Input a Time Record into the engine, creating a time tick in the time processor.

                 \param _record sampleEngine::records::time_record
                 \return int32_t containing a Sample Engine Error Code, see sampleEngine/error_codes.h
                 */
                virtual int32_t processRecord(const struct records::time_record*& _record)=0;

                //! Is the current output record a time record?
                /*!
                 Check the output record buffer for a record and query whether it is is a time record
                 \return sampleEngine::records::recordType - returns any of the records applicable to the time-based processing.
                 */
                virtual records::recordType getTimeRecordType() const=0;
                //! Is the current output record a distance record?
                /*!
                 Check the output record buffer for a record and query whether it is is a distance record
                 \return sampleEngine::records::recordType - returns any of the records applicable to the distance-based processing.
                 */
                virtual records::recordType getDistanceRecordType() const=0;
                //! Retrieve a Distance Data Record
                /*!
                 Retrieve the latest distance data record if and only if it is at the head of the output buffer.
                 The record data is written out to the input _record parameter.
                 \param _record sampleEngine::records::distance_record pointer - 
                 \return int32_t containing a Sample Engine Error Code, see sampleEngine/error_codes.h
                 */
                virtual int32_t getDataRecord(struct records::distance_record*& _record)=0;
                //! Retrieve a Status Record
                /*!
                 Retrieve the latest status record if and only if it is at the head of the output buffer.
                 The record data is written out to the input _record parameter.
                 \param _record sampleEngine::records::sample_record pointer - 
                 \return int32_t containing a Sample Engine Error Code, see sampleEngine/error_codes.h
                 */
                virtual int32_t getStatusRecord(struct records::status_record*& _record)=0;
                //! Retrieve a Time Record
                /*!
                 Retrieve the latest time data record if and only if it is at the head of the output buffer.
                 The record data is written out to the input _record parameter.
                 \param _record sampleEngine::records::time_record pointer - 
                 \return int32_t containing a Sample Engine Error Code, see sampleEngine/error_codes.h
                 */
                virtual int32_t getTimeRecord(struct records::time_record*& _record)=0;
            };
        }
    }

#endif //SAMPLING_ENGINE_CORE_H__
