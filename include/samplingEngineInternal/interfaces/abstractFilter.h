#ifndef SAMPLING_ENGINE_INTERFACE_ABSTRACT_FILTER_H__
#define SAMPLING_ENGINE_INTERFACE_ABSTRACT_FILTER_H__

#include <stdint.h>

#include <deque>
#include <string>

#include <samplingEngine/time_record.h>
#include <samplingEngine/distance_record.h>
#include <samplingEngine/status_record.h>

namespace samplingEngine 
	{
	namespace interfaces
		{
		typedef std::deque<std::string> filterNameList;

		class abstractFilter;
		typedef std::deque<abstractFilter*> abstractFilterList;

		class abstractFilter
			{
			public:
				abstractFilter();
				virtual ~abstractFilter();

				virtual const std::string& filterName()=0;
				virtual filterNameList filterDependencies()=0; 

				virtual bool isTimeBasedFilter() const=0;
				virtual bool isDistanceBasedFilter() const=0;

				virtual void open()=0;
				virtual bool isOpen() const=0;

				virtual void reset()=0;

				virtual void close()=0;

				virtual uint64_t required_samples() const=0;

				// input - function should get the required information from the record
				virtual void processRecord(samplingEngine::records::time_record* _record)=0;
				virtual void processRecord(samplingEngine::records::distance_record* _record)=0;

				// output - function should update its portion of the records
				virtual void updateRecord(const samplingEngine::records::time_record*& _record)=0;
				virtual void updateRecord(const samplingEngine::records::distance_record*& _record)=0;
				virtual void updateRecord(const samplingEngine::records::status_record*& _record, bool timeDomain)=0;

				virtual void setTimeRecordInputIndex(uint64_t _input_index, size_t _data_size); 

				virtual void setTimeRecordOutputIndex(uint64_t _input_inde, size_t _data_sizex); 
				virtual void setDistanceRecordOutputIndex(uint64_t _input_index, size_t _data_size); 

				void add_dependencies(abstractFilter* _filter)
					{
					dependencies.push_back(_filter);
					};

				void reset_dependencies()
					{
					dependencies.clear();
					};

			protected:
				abstractFilterList dependencies;
			};
		}
	}

#endif //SAMPLING_ENGINE_INTERFACE_ABSTRACT_FILTER_H__
