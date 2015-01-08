#ifndef SAMPLING_ENGINE_INTERFACE_ABSTRACT_FILTER_H__
#define SAMPLING_ENGINE_INTERFACE_ABSTRACT_FILTER_H__

#include <stdint.h>

#include <deque>

#include <samplingEngine/time_record.h>
#include <samplingEngine/distance_record.h>
#include <samplingEngine/status_record.h>

namespace samplingEngine 
	{
	namespace interfaces
		{
		class abstractFilter()
			{
			public:
				abstractFilter();
				virtual ~abstractFilter();

				virtual const std::string& filterName()=0;

				virtual bool isTimeBasedFilter() const=0;
				virtual bool isDistanceBasedFilter() const=0;

				// input - function should get the required information from the record
				virtual void processRecord(const samplingEngine::records::time_record*& _record)=0;
				virtual void processRecord(const samplingEngine::records::distance_record*& _record)=0;

				// output - function should update its portion of the records
				virtual void updateRecord(const samplingEngine::record::time_record*& _record)=0;
				virtual void updateRecord(const samplingEngine::record::distance_record*& _record)=0;
				virtual void updateRecord(const samplingEngine::record::status_record*& _record, bool timeDomain)=0;

				virtual void setTimeRecordInputIndex(uint64_t _input_index, size_t _data_size); 

				virtual void setTimeRecordOutputIndex(uint64_t _input_inde, size_t _data_sizex); 
				virtual void setDistanceRecordOutputIndex(uint64_t _input_index, size_t _data_size); 

			protected:
			};

		typedef std::deque<abstractFilter*> abstractFilterList;
		}
	}

#endif //SAMPLING_ENGINE_INTERFACE_ABSTRACT_FILTER_H__
