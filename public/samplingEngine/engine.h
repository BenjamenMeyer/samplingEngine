#ifndef SAMPLING_ENGINE_ENGINE_H__
#define SAMPLING_ENGINE_ENGINE_H__

#include <stdint.h>

#include <samplingEngine/time_record.h>
#include <samplingEngine/configuration.h>
#include <samplingEngine/distance_record.h>
#include <samplingEngine/record_type.h>
#include <samplingEngine/status_record.h>
#include <samplingEngine/configuration.h>

namespace samplingEngine
    {
    class samplingEngine
        {
        public:
            samplingEngine();
            ~samplingEngine();

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
            //        the next record is processed by engine_process_record()
            //
            records::recordType getRecordType() const;
            int32_t getDataRecord(struct records::distance_record*& _record);
            int32_t getStatusRecord(struct records::status_record*& _record);
            int32_t getTimeRecord(struct records::time_record*& _record);

        protected:
            struct config::engineConfiguration configuration;
            
        };
    }

#endif //SAMPLING_ENGINE_ENGINE_H__
