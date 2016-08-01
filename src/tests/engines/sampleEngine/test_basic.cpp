#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MAIN
#define BOOST_TEST_MODULE SamplingEngineTest
#include <boost/test/unit_test.hpp>

#include <samplingEngine/engine.h>

BOOST_AUTO_TEST_SUITE( SamplingEngine );

BOOST_AUTO_TEST_CASE( SamplingEngineInstantiationPublic )
{
	samplingEngine::samplingEngine testEngine;
}

BOOST_AUTO_TEST_SUITE_END();
