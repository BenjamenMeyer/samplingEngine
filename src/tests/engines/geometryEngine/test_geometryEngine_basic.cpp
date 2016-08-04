#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MAIN
#define BOOST_TEST_MODULE SamplingEngineTest
#include <boost/test/unit_test.hpp>

#include <samplingEngineInternal/geometricEngine/engine.h>

BOOST_AUTO_TEST_SUITE( GeometricEngine );

BOOST_AUTO_TEST_CASE( GeometricEngineInstantiationPublic )
{
	geometricEngine::geometricEngine testEngine;
}

BOOST_AUTO_TEST_SUITE_END();
