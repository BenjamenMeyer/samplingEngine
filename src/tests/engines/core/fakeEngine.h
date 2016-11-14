#ifndef SAMPLE_ENGINE_CORE_TESTING_FAKE_ENGINE_H__
#define SAMPLE_ENGINE_CORE_TESTING_FAKE_ENGINE_H__

#include <samplingEngine/core.h>

//! fakeEngine is an object for testing interface compliance
/*!
 fakeEngine is a simplified instantiable version of the coreSamplingEngine
 that is used for testing the interface complaince of the coreSamplingEngine class
 since it is a pure virtual (aka interface) class. It only exists for the testing
 capabilities.
 */

#define FUNC_INT_RETURNED_CALLED(name, param, called_var)	\
	bool called_var;										\
	int32_t name(param) { called_var = true; return 0; }

class fakeEngine : public samplingEngine::core::coreSamplingEngine
{
	public:
		static bool constructor_called;
		static bool destructor_called;

		fakeEngine() :coreSamplingEngine()
			{
			open_called = false;

			is_open_called = false;

			initialized_called = false;
			close_called = false;
			process_record_called = false;

			get_time_record_type_called = false;
			get_data_record_type_called = false;

			get_data_record_called = false;
			get_status_record_called = false;
			get_time_record_called = false;

			fakeEngine::constructor_called = true;
			}
		~fakeEngine()
			{
			fakeEngine::destructor_called = true;
			}

		FUNC_INT_RETURNED_CALLED(open, const struct samplingEngine::config::engineConfiguration&, open_called)

		bool is_open_called;
		bool isOpen() const { const_cast<fakeEngine*>(this)->is_open_called = true; return false; }

		FUNC_INT_RETURNED_CALLED(initialize, void, initialized_called)
		FUNC_INT_RETURNED_CALLED(close, void, close_called)
		FUNC_INT_RETURNED_CALLED(processRecord, const struct samplingEngine::records::time_record*&, process_record_called)

		bool get_time_record_type_called;
		samplingEngine::records::recordType getTimeRecordType() const
			{
			const_cast<fakeEngine*>(this)->get_time_record_type_called = true;
			return samplingEngine::records::INVALID_RECORD_TYPE;
			}
		bool get_data_record_type_called;
		samplingEngine::records::recordType getDistanceRecordType() const
			{
			const_cast<fakeEngine*>(this)->get_data_record_type_called = true;
			return samplingEngine::records::INVALID_RECORD_TYPE;
			}

		FUNC_INT_RETURNED_CALLED(getDataRecord, struct samplingEngine::records::distance_record*&, get_data_record_called)
		FUNC_INT_RETURNED_CALLED(getStatusRecord, struct samplingEngine::records::status_record*&, get_status_record_called)
		FUNC_INT_RETURNED_CALLED(getTimeRecord, struct samplingEngine::records::time_record*&, get_time_record_called)
};

#endif //SAMPLE_ENGINE_CORE_TESTING_FAKE_ENGINE_H__
