#ifndef SAMPLING_ENGINE_INTERFACE_ABSTRACT_FILTER_H__
#define SAMPLING_ENGINE_INTERFACE_ABSTRACT_FILTER_H__

#include <samplingEngine/time_record.h>
#include <samplingEngine/distance_record.h>
#include <samplingEngine/status_record.h>

namespace samplingEngine
	{
	namespace interfaaces
		{

		class abstractFilter()
			{
			public:
				abstractFilter();
				virtual ~abstractFilter();

				bool isTimeBasedFilter() const=0;
				bool isDistanceBasedFilter() const=0;

				// input - function should get the required information from the record
				void processRecord(const samplingEngine::records::time_record*& _record)=0;
				void processRecord(const samplingEngine::records::distance_record*& _record)=0;

				// output - function should update its portion of the records
				void updateRecord(const samplingEngine::record::time_record*& _record)=0;
				void updateRecord(const samplingEngine::record::distance_record*& _record)=0;
				void updateRecord(const samplingEngine::record::status_record*& _record, bool timeDomain)=0;

			protected:
			};
		}
	}

#endif //SAMPLING_ENGINE_INTERFACE_ABSTRACT_FILTER_H__
