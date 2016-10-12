#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_NO_MAIN

#include <boost/test/unit_test.hpp>

#include <samplingEngineInternal/geometricEngine/engine.h>

BOOST_AUTO_TEST_SUITE( GeometricEngine );

BOOST_AUTO_TEST_CASE( GeometricEngineInstantiationPublic )
{
	geometricEngine::geometricEngine testEngine;
}

BOOST_AUTO_TEST_SUITE_END();
