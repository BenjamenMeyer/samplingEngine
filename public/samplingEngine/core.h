#ifndef SAMPLING_ENGINE_CORE_H__
#define SAMPLING_ENGINE_CORE_H__

#include <samplingEngine/configuration.h>
#include <samplingEngine/core.h>
#include <samplingEngine/distance_record.h>
#include <samplingEngine/record_type.h>
#include <samplingEngine/status_record.h>
#include <samplingEngine/time_record.h>

namespace samplingEngine
	{
	namespace core
		{
		// base class for the internal core engine functionality
		class coreSamplingEngine
			{
			public:
				coreSamplingEngine();
				virtual ~coreSamplingEngine();

				// initialization
				virtual int32_t initialize(const struct config::engineConfiguration& _configuration)=0;
				// destruction
				virtual int32_t close()=0;

				// input
				virtual int32_t processRecord(const struct records::time_record*& _record)=0;

				// output
				virtual records::recordType getTimeRecordType() const=0;
				virtual records::recordType getDistanceRecordType() const=0;
				virtual int32_t getDataRecord(struct records::distance_record*& _record)=0;
				virtual int32_t getStatusRecord(struct records::status_record*& _record)=0;
				virtual int32_t getTimeRecord(struct records::time_record*& _record)=0;
			};
		}
	}

#endif //SAMPLING_ENGINE_CORE_H__
