#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_NO_MAIN

#include <boost/test/unit_test.hpp>

#include <samplingEngine/core.h>

#include "fakeEngine.h"

bool fakeEngine::constructor_called = false;
bool fakeEngine::destructor_called = false;

BOOST_AUTO_TEST_SUITE( CoreEngine );

BOOST_AUTO_TEST_CASE( CoreEngineTestFrameworkStatics )
{
	fakeEngine::constructor_called = false;
	fakeEngine::destructor_called = false;

	BOOST_CHECK(!fakeEngine::constructor_called);
	BOOST_CHECK(!fakeEngine::destructor_called);
}

BOOST_AUTO_TEST_CASE( CoreEngineInstantiationPublic )
{
	fakeEngine::constructor_called = false;

	BOOST_CHECK(!fakeEngine::constructor_called);
	fakeEngine f;
	samplingEngine::core::coreSamplingEngine* testEngine = &f;
	BOOST_CHECK_EQUAL(dynamic_cast<fakeEngine*>(testEngine), &f);
	BOOST_CHECK(fakeEngine::constructor_called);
}

BOOST_AUTO_TEST_CASE( CoreEngineDestructionPublic )
{
	fakeEngine::constructor_called = false;
	fakeEngine::destructor_called = false;

	BOOST_CHECK(!fakeEngine::constructor_called);
	BOOST_CHECK(!fakeEngine::destructor_called);
	// segregate the instantiation in a new scope
	// to test the destructor
		{
		fakeEngine f;
		BOOST_CHECK(fakeEngine::constructor_called);
		}
	BOOST_CHECK(fakeEngine::destructor_called);
}

BOOST_AUTO_TEST_CASE( CoreEngineOpenInterface )
{
	fakeEngine f;
	BOOST_CHECK(!f.open_called);
	struct samplingEngine::config::engineConfiguration ec;
	f.open(ec);
	BOOST_CHECK(f.open_called);
}

BOOST_AUTO_TEST_CASE( CoreEngineIsOpenInterface )
{
	fakeEngine f;
	BOOST_CHECK(!f.is_open_called);
	BOOST_CHECK(!f.isOpen());
	BOOST_CHECK(f.is_open_called);
}

BOOST_AUTO_TEST_CASE( CoreEngineInitializeInterface )
{
	fakeEngine f;
	BOOST_CHECK(!f.initialized_called);
	BOOST_CHECK(!f.initialize());
	BOOST_CHECK(f.initialized_called);
}

BOOST_AUTO_TEST_CASE( CoreEngineCloseInterface )
{
	fakeEngine f;
	BOOST_CHECK(!f.close_called);
	BOOST_CHECK(!f.close());
	BOOST_CHECK(f.close_called);
}

BOOST_AUTO_TEST_CASE( CoreEngineProcessRecordInterface )
{
	fakeEngine f;
	const struct samplingEngine::records::time_record* tr = NULL;
	BOOST_CHECK(!f.process_record_called);
	BOOST_CHECK_EQUAL(f.processRecord(tr), 0);
	BOOST_CHECK(f.process_record_called);
}

BOOST_AUTO_TEST_CASE( CoreEngineGetTimeRecordTypeInterface )
{
	fakeEngine f;
	BOOST_CHECK(!f.get_time_record_type_called);
	BOOST_CHECK_EQUAL(f.getTimeRecordType(), samplingEngine::records::INVALID_RECORD_TYPE);
	BOOST_CHECK(f.get_time_record_type_called);
}

BOOST_AUTO_TEST_CASE( CoreEngineGetDataRecordTypeInterface )
{
	fakeEngine f;
	BOOST_CHECK(!f.get_data_record_type_called);
	BOOST_CHECK_EQUAL(f.getDistanceRecordType(), samplingEngine::records::INVALID_RECORD_TYPE);
	BOOST_CHECK(f.get_data_record_type_called);
}

BOOST_AUTO_TEST_CASE( CoreEngineGetDataRecordInterface )
{
	fakeEngine f;
	//const struct samplingEngine::records::time_record* tr = NULL;
	struct samplingEngine::records::distance_record* dr = NULL;
	BOOST_CHECK(!f.get_data_record_called);
	BOOST_CHECK_EQUAL(f.getDataRecord(dr), 0);
	BOOST_CHECK(f.get_data_record_called);
}

BOOST_AUTO_TEST_CASE( CoreEngineGetStatusRecordInterface )
{
	fakeEngine f;
	struct samplingEngine::records::status_record* sr = NULL;
	BOOST_CHECK(!f.get_status_record_called);
	BOOST_CHECK_EQUAL(f.getStatusRecord(sr), 0);
	BOOST_CHECK(f.get_status_record_called);
}

BOOST_AUTO_TEST_CASE( CoreEngineGetTimeRecordInterface )
{
	fakeEngine f;
	struct samplingEngine::records::time_record* tr = NULL;
	BOOST_CHECK(!f.get_time_record_called);
	BOOST_CHECK_EQUAL(f.getTimeRecord(tr), 0);
	BOOST_CHECK(f.get_time_record_called);
}

BOOST_AUTO_TEST_SUITE_END();

