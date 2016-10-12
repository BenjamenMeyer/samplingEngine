#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_NO_MAIN

#include <functional>

#include <boost/test/unit_test.hpp>

#include <samplingEngine/configuration.h>
#include <samplingEngine/engine.h>
#include <samplingEngine/error_codes.h>
#include <samplingEngine/log.h>

#include <samplingEngineTesting/testing/log/testLogger.h>


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

BOOST_AUTO_TEST_SUITE_END();
