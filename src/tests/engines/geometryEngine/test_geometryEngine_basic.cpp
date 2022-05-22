#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_NO_MAIN

#include <boost/test/unit_test.hpp>

#include <samplingEngine/error_codes.h>

#include <samplingEngineInternal/geometricEngine/engine.h>

BOOST_AUTO_TEST_SUITE( GeometricEngine );

BOOST_AUTO_TEST_CASE( GeometricEngineInstantiationPublic )
{
	geometricEngine::geometricEngine testEngine;
}

BOOST_AUTO_TEST_CASE( GeometricEngineNotSupported )
{
	geometricEngine::geometricEngine testEngine;
    // doesn't matter what is in this because it's not actually processed
    // just need the type data
    samplingEngine::interfaces::abstractFilterList interdependentFilters;
    int32_t result = testEngine.addInterdependentFilters(interdependentFilters);
    BOOST_CHECK(SAMPLING_ENGINE_MATCHES_ERROR_CODE(result, SAMPLING_ENGINE_ERROR_NOT_SUPPORTED_YET));
}

BOOST_AUTO_TEST_SUITE_END();
