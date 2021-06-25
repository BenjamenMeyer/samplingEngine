#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_NO_MAIN

#include <functional>
#include <list>
#include <utility>

#include <boost/test/unit_test.hpp>

#include <samplingEngine/configuration.h>
#include <samplingEngine/engine.h>
#include <samplingEngine/error_codes.h>
#include <samplingEngine/log.h>

#include <samplingEngineTesting/testing/log/testLogger.h>

#include "fakeEngine.h"

/* static */ bool fakeSampleEngine::constructor_called = false;
/* static */  bool fakeSampleEngine::destructor_called = false;

BOOST_AUTO_TEST_SUITE( SamplingEngine );

BOOST_AUTO_TEST_CASE( SamplingEngineErrorMessages )
{
	/*
	 * Testing Sampling Engine Error Message Retrieval
	 */
    std::string unknownErrorMessage = "UNKNOWN ERROR";
    for (uint32_t i = 0; i <= SAMPLING_ENGINE_ERROR_MAX; ++i)
        {
        std::string message_A = samplingEngine::samplingEngine::getErrorMessage(i);
        std::string message_B = samplingEngine::samplingEngine::getErrorMessage(SAMPLING_ENGINE_MAKE_ERROR_CODE(i));
        if (i != SAMPLING_ENGINE_ERROR_MAX)
            {
            BOOST_CHECK_NE(message_A, unknownErrorMessage);
            BOOST_CHECK_NE(message_B, unknownErrorMessage);
            }
        else
            {
            BOOST_CHECK_EQUAL(message_A, unknownErrorMessage);
            BOOST_CHECK_EQUAL(message_B, unknownErrorMessage);
            }
        }
}

BOOST_AUTO_TEST_CASE( SamplingEngineInstantiationPublic )
{
	/*
	 * Test Setting the logger returns a NULL logger by default
	 */
    samplingEngine::samplingEngine testEngine;
    BOOST_CHECK_EQUAL(testEngine.getState(), samplingEngine::samplingEngine::SAMPLE_ENGINE_NOT_INITIALIZED);
    samplingEngine::logging::samplingEngineLogger* nullLogger = NULL;
    BOOST_CHECK_EQUAL(testEngine.setLogger(NULL), nullLogger);
	BOOST_CHECK_EQUAL(testEngine.getState(), samplingEngine::samplingEngine::SAMPLE_ENGINE_NOT_INITIALIZED);
}

BOOST_AUTO_TEST_CASE( SamplingEngineLoggerConfig )
{
	/*
	 * Test Setting the logger returns the previous logger
	 */
    samplingEngine::samplingEngine testEngine;
    testLogger newLogger;
    samplingEngine::logging::samplingEngineLogger* nullLogger = NULL;

    BOOST_CHECK_EQUAL(testEngine.setLogger(&newLogger), nullLogger);
    BOOST_CHECK_EQUAL(testEngine.setLogger(NULL), &newLogger);
}

BOOST_AUTO_TEST_CASE( SamplingEngineLoggerConfigInstantiation )
{
	/*
	 * Test setting the logger via constructor works
	 */
    testLogger newLogger;
    samplingEngine::samplingEngine testEngine2(&newLogger);
    BOOST_CHECK_EQUAL(testEngine2.setLogger(NULL), &newLogger);
}

BOOST_AUTO_TEST_CASE( SamplingEngineInitialize )
{
	/*
	 * Test the instantiation of the engine
	 */
    testLogger newLogger;
    samplingEngine::samplingEngine testEngine3(&newLogger);

    struct samplingEngine::config::engineConfiguration configuration;
    configuration.operationalState = samplingEngine::config::ENGINE_NORMAL_OPERATION;
    configuration.samples.time_sample_rate_hz = 1000; // 1000 Samples/Second
    configuration.samples.distance_sample_rate_mm = 250; // 5mm samples
    configuration.sensors.tachometer.pulses_per_meter = 5000; // 5000 ppm

    int32_t result = testEngine3.initialize(configuration);

    BOOST_CHECK_EQUAL(SAMPLING_ENGINE_IS_ERROR_CODE(result), true);
    BOOST_CHECK_EQUAL(SAMPLING_ENGINE_GET_ERROR_CODE(result), SAMPLING_ENGINE_ERROR_SUCCESS);

    BOOST_CHECK_EQUAL(
        testEngine3.getState(),
        samplingEngine::samplingEngine::SAMPLE_ENGINE_OPERATION_MODE|samplingEngine::samplingEngine::SAMPLE_ENGINE_OPERATIONAL_STARTUP|samplingEngine::samplingEngine::SAMPLE_ENGINE_INITIALIZED
    );


    result = testEngine3.close();
    BOOST_CHECK_EQUAL(SAMPLING_ENGINE_IS_ERROR_CODE(result), true);
    BOOST_CHECK_EQUAL(SAMPLING_ENGINE_GET_ERROR_CODE(result), SAMPLING_ENGINE_ERROR_SUCCESS);

    BOOST_CHECK_EQUAL(
        testEngine3.getState(),
        samplingEngine::samplingEngine::SAMPLE_ENGINE_NOT_INITIALIZED
    );
}

BOOST_AUTO_TEST_CASE( SamplingEngineIndividualStates )
{
	fakeSampleEngine testEngine;

	BOOST_CHECK_EQUAL(
		testEngine.getState(),
		samplingEngine::samplingEngine::SAMPLE_ENGINE_NOT_INITIALIZED
	);

	std::list<samplingEngine::samplingEngine::sampleEngineState> states;
	#define ADD_STATE(s) states.push_back(samplingEngine::samplingEngine::s)
	ADD_STATE(SAMPLE_ENGINE_DIAGNOSTIC_MODE);
	ADD_STATE(SAMPLE_ENGINE_CALIBRATION_MODE);
	ADD_STATE(SAMPLE_ENGINE_OPERATION_MODE);
	ADD_STATE(SAMPLE_ENGINE_OPERATIONAL_STARTUP);
	ADD_STATE(SAMPLE_ENGINE_OPERATIONAL_READY);
	ADD_STATE(SAMPLE_ENGINE_OPERATIONAL_SHUTDOWN);
	ADD_STATE(SAMPLE_ENGINE_NOT_INITIALIZED);

	#undef ADD_STATE

	samplingEngine::samplingEngine::sampleEngineState masterState = samplingEngine::samplingEngine::SAMPLE_ENGINE_INITIALIZED;
	for (auto state=states.begin(); state != states.end(); ++state)
		{
		testEngine.setState(masterState);
		BOOST_CHECK_EQUAL(testEngine.getState(), masterState);

		testEngine.enableState(*state);
		auto combinedState = masterState|(*state);
		BOOST_CHECK_EQUAL(testEngine.getState(), combinedState);

		testEngine.disableState(*state);
		BOOST_CHECK_EQUAL(testEngine.getState(), masterState);
		}
}

BOOST_AUTO_TEST_CASE( SamplingEngineSimpleStates )
{
	fakeSampleEngine testEngine;

	BOOST_CHECK_EQUAL(
		testEngine.getState(),
		samplingEngine::samplingEngine::SAMPLE_ENGINE_NOT_INITIALIZED
	);

	std::list<samplingEngine::samplingEngine::sampleEngineState> states;
	#define ADD_STATE(s) states.push_back(samplingEngine::samplingEngine::s)
	ADD_STATE(SAMPLE_ENGINE_INITIALIZED);
	ADD_STATE(SAMPLE_ENGINE_DIAGNOSTIC_MODE);
	ADD_STATE(SAMPLE_ENGINE_CALIBRATION_MODE);
	ADD_STATE(SAMPLE_ENGINE_OPERATION_MODE);
	ADD_STATE(SAMPLE_ENGINE_OPERATIONAL_STARTUP);
	ADD_STATE(SAMPLE_ENGINE_OPERATIONAL_READY);
	ADD_STATE(SAMPLE_ENGINE_OPERATIONAL_SHUTDOWN);
	ADD_STATE(SAMPLE_ENGINE_NOT_INITIALIZED);

	#undef ADD_STATE

	for (auto state=states.begin(); state != states.end(); ++state)
		{
		testEngine.setState(*state);
		BOOST_CHECK_EQUAL(testEngine.getState(), *state);
		}
}

BOOST_AUTO_TEST_CASE( SamplingEngineComplexStates )
{
	fakeSampleEngine testEngine;

	BOOST_CHECK_EQUAL(
		testEngine.getState(),
		samplingEngine::samplingEngine::SAMPLE_ENGINE_NOT_INITIALIZED
	);

	std::list<
		std::pair<
			samplingEngine::samplingEngine::sampleEngineState,
			std::pair<
				samplingEngine::samplingEngine::sampleEngineState,
				samplingEngine::samplingEngine::sampleEngineState
			>
		>
	> states;
	#define ADD_STATE(s, a, b)							\
		{												\
		states.push_back(								\
			std::make_pair(								\
				samplingEngine::samplingEngine::s,		\
				std::make_pair(							\
					samplingEngine::samplingEngine::a,	\
					samplingEngine::samplingEngine::b	\
				)										\
			)											\
		);												\
		}
	// Operations
	ADD_STATE(SAMPLE_ENGINE_IN_OPERATION, SAMPLE_ENGINE_INITIALIZED, SAMPLE_ENGINE_OPERATION_MODE);
	ADD_STATE(SAMPLE_ENGINE_IN_OPERATION_STARTUP, SAMPLE_ENGINE_IN_OPERATION, SAMPLE_ENGINE_OPERATIONAL_STARTUP);
	ADD_STATE(SAMPLE_ENGINE_IN_OPERATION_READY, SAMPLE_ENGINE_IN_OPERATION, SAMPLE_ENGINE_OPERATIONAL_READY);
	ADD_STATE(SAMPLE_ENGINE_IN_OPERATION_SHUTDOWN, SAMPLE_ENGINE_IN_OPERATION, SAMPLE_ENGINE_OPERATIONAL_SHUTDOWN);

	// Diagnostic
	ADD_STATE(SAMPLE_ENGINE_IN_DIAGNOSTICS, SAMPLE_ENGINE_INITIALIZED, SAMPLE_ENGINE_DIAGNOSTIC_MODE);
	ADD_STATE(SAMPLE_ENGINE_IN_DIAGNOSTICS_STARTUP, SAMPLE_ENGINE_IN_DIAGNOSTICS, SAMPLE_ENGINE_OPERATIONAL_STARTUP);
	ADD_STATE(SAMPLE_ENGINE_IN_DIAGNOSTICS_READY, SAMPLE_ENGINE_IN_DIAGNOSTICS, SAMPLE_ENGINE_OPERATIONAL_READY);
	ADD_STATE(SAMPLE_ENGINE_IN_DIAGNOSTICS_SHUTDOWN, SAMPLE_ENGINE_IN_DIAGNOSTICS, SAMPLE_ENGINE_OPERATIONAL_SHUTDOWN);

	// Calibration
	ADD_STATE(SAMPLE_ENGINE_IN_CALIBRATION, SAMPLE_ENGINE_INITIALIZED, SAMPLE_ENGINE_CALIBRATION_MODE);
	ADD_STATE(SAMPLE_ENGINE_IN_CALIBRATION_STARTUP, SAMPLE_ENGINE_IN_CALIBRATION, SAMPLE_ENGINE_OPERATIONAL_STARTUP);
	ADD_STATE(SAMPLE_ENGINE_IN_CALIBRATION_READY, SAMPLE_ENGINE_IN_CALIBRATION, SAMPLE_ENGINE_OPERATIONAL_READY);
	ADD_STATE(SAMPLE_ENGINE_IN_CALIBRATION_SHUTDOWN, SAMPLE_ENGINE_IN_CALIBRATION, SAMPLE_ENGINE_OPERATIONAL_SHUTDOWN);

	#undef ADD_STATE

	for (auto state=states.begin(); state != states.end(); ++state)
		{
		auto master_state = (*state).first;
		auto state_a = (*state).second.first;
		auto state_b = (*state).second.second;
		testEngine.setState(master_state);
		BOOST_CHECK_EQUAL(testEngine.getState(), master_state);
		BOOST_CHECK(testEngine.isStateSet(state_a));
		BOOST_CHECK(testEngine.isStateSet(state_b));
		}
}

BOOST_AUTO_TEST_SUITE_END();
