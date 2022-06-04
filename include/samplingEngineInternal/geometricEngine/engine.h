#ifndef GEOMETRIC_ENGINE_H__
#define GEOMETRIC_ENGINE_H__

#include <samplingEngine/configuration.h>
#include <samplingEngine/core.h>
#include <samplingEngine/record_queues.h>

#include <samplingEngineInternal/interfaces/abstractFilter.h>
#include <samplingEngineInternal/geometricEngine/channelOffsets.h>

namespace geometricEngine
    {
    //! Geometry Measurement Data Engine
    /*!
     An implementation of the sampling engine to calculate geometric data
     */
    class geometricEngine: public samplingEngine::core::coreSamplingEngine
        {
        public:
            //! Constructor
            /*!
             Create an instance of the engine with all requisite base resources.
             */
            geometricEngine();
            //! Destructor
            /*!
             Cleanup the instance of the engine and all resources on destruction.
             */
            ~geometricEngine();

            //! Startup the engine for use, and provide the configuration
            /*!
             Configure the engine for use, and start it up but do not initialize it.
             \param _configuration const struct sampleEngine::config::engineConfiguration the configuration for the measurements, filters, etc.
             \return int32_t containing a Sample Engine Error Code, see sampleEngine/error_codes.h
             */
            virtual int32_t open(const struct samplingEngine::config::engineConfiguration& _configuration);
            //! Check whether the engine has been openned
            /*!
             Check whether open() has been called and the configuration provided.
             \return bool true if openned, otherwise false
             */
            virtual bool isOpen() const;

            //! Initialize the engine
            /*!
             Initialize the engine and apply the configuration to load the filters, measurements,
             channels, etc.
             \return int32_t containing a Sample Engine Error Code, see sampleEngine/error_codes.h
             */
            virtual int32_t initialize();

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
            virtual int32_t close();

            //! Add a single filter to the listing
            /*!
             Add an independent filter to the processing listing. Order of addition directly impacts order of use.
             /param _filter samplingEngine::interface::abstractFilter* an object instance that implements the filter interface
             \return int32_t containing a Sample Engine Error Code, see sampleEngine/error_codes.h
             */
            virtual int32_t addFilter(samplingEngine::interfaces::abstractFilter* _filter);
            //! Add a series of inter-dependant filters to the listing
            /*!
             Add a series of filters to the processing listing. Order of addition directly impacts order of use.
             .. note:: filter set creator must ensure the filters will work out correctly
             /param _filter samplingEngine::interface::abstractFilter* an object instance that implements the filter interface
             \return int32_t containing a Sample Engine Error Code, see sampleEngine/error_codes.h
             */
            virtual int32_t addInterdependentFilters(samplingEngine::interfaces::abstractFilterList& _interdependentFilters);

            // Process a Time Record
            /*!
             Input a Time Record into the engine, creating a time tick in the time processor.

             \param _record sampleEngine::records::time_record
             \return int32_t containing a Sample Engine Error Code, see sampleEngine/error_codes.h
             */
            virtual int32_t processRecord(const struct samplingEngine::records::time_record*& _record);

            //! Is the current output record a time record?
            /*!
             Check the output record buffer for a record and query whether it is is a time record
             \return sampleEngine::records::recordType - returns any of the records applicable to the time-based processing.
             */
            virtual samplingEngine::records::recordType getTimeRecordType() const;
            //! Is the current output record a distance record?
            /*!
             Check the output record buffer for a record and query whether it is is a distance record
             \return sampleEngine::records::recordType - returns any of the records applicable to the distance-based processing.
             */
            virtual samplingEngine::records::recordType getDistanceRecordType() const;
            //! Retrieve a Distance Data Record
            /*!
             Retrieve the latest distance data record if and only if it is at the head of the output buffer.
             The record data is written out to the input _record parameter.
             \param _record sampleEngine::records::distance_record pointer - 
             \return int32_t containing a Sample Engine Error Code, see sampleEngine/error_codes.h
             */
            virtual int32_t getDataRecord(struct samplingEngine::records::distance_record*& _record);
            //! Retrieve a Status Record
            /*!
             Retrieve the latest status record if and only if it is at the head of the output buffer.
             The record data is written out to the input _record parameter.
             \param _record sampleEngine::records::sample_record pointer - 
             \return int32_t containing a Sample Engine Error Code, see sampleEngine/error_codes.h
             */
            virtual int32_t getStatusRecord(struct samplingEngine::records::status_record*& _record);
            //! Retrieve a Time Record
            /*!
             Retrieve the latest time data record if and only if it is at the head of the output buffer.
             The record data is written out to the input _record parameter.
             \param _record sampleEngine::records::time_record pointer - 
             \return int32_t containing a Sample Engine Error Code, see sampleEngine/error_codes.h
             */
            virtual int32_t getTimeRecord(struct samplingEngine::records::time_record*& _record);

            //! Release memory associated with the record
            /*!
             Retrieving records out of the samplingEngine will create memory allocations.
             .. note:: the caller must ensure that only memory related to records output by the samplingEngine
                are requested to be released. The system is not capable of tracking them.
             /param _record void*& pointer to a data record, if not NULL the memory will be released.
             */
            virtual void cleanup_record(void*& _record) const;

        protected:
            recordOffsetMap channelMapper; /*!< tool for positioning the data into the records */

            samplingEngine::queues::record_queue input_queue; /*!< record data provided as input */

            samplingEngine::interfaces::abstractFilterList filters; /*!< list of filters to apply */

            samplingEngine::queues::record_queue output_queue; /*!< list of records ready for output */

            //! Process data records from the input queue through the filters
            /*!
             Process the input queue until it is empty, running all the data through the filters, and then generating
             the output record(s) to the otuput queue.
             \return int32_t containing a Sample Engine Error Code, see sampleEngine/error_codes.h
             */
            int32_t process_records();

        private:
            // basic state of the engine - open (true) or closed (false)
            bool geometric_engine_active;
            // number of distance samples necessary for all channels to be valid assuming data is
            // within the tolerances of all the filters
            uint64_t maximum_sample_buffering;
        };
    }

#endif //GEOMETRIC_ENGINE_H__
