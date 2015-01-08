#ifndef GEOMETRIC_ENGINE_H__
#define GEOMETRIC_ENGINE_H__

#include <samplingEngine/configuration.h>
#include <samplingEngine/core.h>
#include <samplingEngine/record_queues.h>

#include <samplingEngineInternal/interfaces/abstractFilter.h>

namespace geometricEngine
	{
	class geometricEngine: public samplingEngine::core::coreSamplingEngine
		{
		public:
			geometricEngine();
			~geometricEngine();

			// initialization
			virtual int32_t initialize(const struct config::engineConfiguration& _configuration);

			// destruction
			virtual int32_t close();

			virtual int32_t addFilter(samplingEngine::interfaces::abstractFilter*); 

			// input
			virtual int32_t processRecord(const struct records::time_record*& _record);

			// output
			virtual records::recordType getTimeRecordType() const;
			virtual records::recordType getDistanceRecordType() const;
			virtual int32_t getDataRecord(struct records::distance_record*& _record);
			virtual int32_t getStatusRecord(struct records::status_record*& _record);
			virtual int32_t getTimeRecord(struct records::time_record*& _record);

		protected:
			queues::record_queue input_queue;

			samplingEngine::interfaces::abstractFilterList filters;

			queues::record_queue output_queue;

			void process_records();
		};
	}

#endif //GEOMETRIC_ENGINE_H__
