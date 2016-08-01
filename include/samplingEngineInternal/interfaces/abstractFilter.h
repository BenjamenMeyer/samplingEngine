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

                // filter name
                virtual const std::string& filterName()=0;
                // list of filter names the filter is dependent on
                virtual filterNameList filterDependencies()=0;

                // is the filter a time-based filter?
                virtual bool isTimeBasedFilter() const=0;
                // is the filter a distance-based filter?
                virtual bool isDistanceBasedFilter() const=0;

                // open the filter for use
                virtual void open()=0;
                // is the filter open for use?
                virtual bool isOpen() const=0;

                // reset the filter data
                virtual void reset()=0;

                // close the filter
                virtual void close()=0;

                // how many samples are required for the filter to operate
                virtual uint64_t required_samples() const=0;

                // input - function should get the required information from the record
                virtual void processRecord(records::time_record* _record)=0;
                virtual void processRecord(records::distance_record* _record)=0;

                // output - function should update its portion of the records
                virtual void updateRecord(const records::time_record*& _record)=0;
                virtual void updateRecord(const records::distance_record*& _record)=0;
                virtual void updateRecord(const records::status_record*& _record, bool timeDomain)=0;

                // set the current Time-based Record Input Index (start of time queue)
                virtual void setTimeRecordInputIndex(uint64_t _input_index, size_t _data_size)=0;

                // set the current Time-based Record Output Index (end of time queue)
                virtual void setTimeRecordOutputIndex(uint64_t _input_inde, size_t _data_sizex)=0;
                // set the current Distance Record Output Index
                virtual void setDistanceRecordOutputIndex(uint64_t _input_index, size_t _data_size)=0;

                // add a reference to a filter this filter is dependent upon
                void add_dependencies(abstractFilter* _filter);

                // reset the filter dependencies
                void reset_dependencies();

            protected:
                // list of the filters this filter is dependent upon
                abstractFilterList dependencies;
            };
        }
    }

#endif //SAMPLING_ENGINE_INTERFACE_ABSTRACT_FILTER_H__
