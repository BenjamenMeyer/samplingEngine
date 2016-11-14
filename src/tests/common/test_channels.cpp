#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_NO_MAIN

#include <functional>
#include <string>

#include <boost/test/unit_test.hpp>

#include <samplingEngine/channels/channel.h>

BOOST_AUTO_TEST_SUITE( CommonChannels );

/*
	Float Normalized
 */
BOOST_AUTO_TEST_CASE( CommonChannels_NormalizedToScalar_Float )
{
	float input = 99.125;
	unsigned int scale = 1000;
	unsigned int expected_output = 99125;

	unsigned int output = samplingEngine::channels::NORMALIZED_TO_SCALAR(input, scale);
	BOOST_CHECK_EQUAL(output, expected_output);
}

BOOST_AUTO_TEST_CASE( CommonChannels_ScalarToNormalized_Float )
{
	unsigned int input = 99125;
	unsigned int scale = 1000;
	float expected_output = 99.125;

	float output = samplingEngine::channels::SCALAR_TO_NORMALIZED(input, scale, expected_output);
	BOOST_CHECK_EQUAL(output, expected_output);
}

BOOST_AUTO_TEST_CASE( CommonChannels_NormalizedToScalarToNormalized_Float )
{
	float input = 99.125;
	unsigned int scale = 1000;

	unsigned int output_1 = samplingEngine::channels::NORMALIZED_TO_SCALAR(input, scale);
	float output_2 = samplingEngine::channels::SCALAR_TO_NORMALIZED(output_1, scale, input);
	BOOST_CHECK_EQUAL(output_2, input);
}

/*
	Double Normalized
 */
BOOST_AUTO_TEST_CASE( CommonChannels_NormalizedToScalar_Double )
{
	double input = 99.125;
	unsigned int scale = 1000;
	unsigned int expected_output = 99125;

	unsigned int output = samplingEngine::channels::NORMALIZED_TO_SCALAR(input, scale);
	BOOST_CHECK_EQUAL(output, expected_output);
}

BOOST_AUTO_TEST_CASE( CommonChannels_ScalarToNormalized_Double )
{
	unsigned int input = 99125;
	unsigned int scale = 1000;
	double expected_output = 99.125;

	double output = samplingEngine::channels::SCALAR_TO_NORMALIZED(input, scale, expected_output);
	BOOST_CHECK_EQUAL(output, expected_output);
}

BOOST_AUTO_TEST_CASE( CommonChannels_NormalizedToScalarToNormalized_Double )
{
	double input = 99.125;
	unsigned int scale = 1000;

	unsigned int output_1 = samplingEngine::channels::NORMALIZED_TO_SCALAR(input, scale);
	double output_2 = samplingEngine::channels::SCALAR_TO_NORMALIZED(output_1, scale, input);
	BOOST_CHECK_EQUAL(output_2, input);
}

/*
	Signed Int Normalized
 */
BOOST_AUTO_TEST_CASE( CommonChannels_NormalizedToScalar_Int )
{
	int input = 99;
	unsigned int scale = 1000;
	unsigned int expected_output = 99000;

	unsigned int output = samplingEngine::channels::NORMALIZED_TO_SCALAR(input, scale);
	BOOST_CHECK_EQUAL(output, expected_output);
}

BOOST_AUTO_TEST_CASE( CommonChannels_ScalarToNormalized_Int )
{
	unsigned int input = -99000;
	unsigned int scale = 1000;
	int expected_output = -99;

	int output = samplingEngine::channels::SCALAR_TO_NORMALIZED(input, scale, expected_output);
	BOOST_CHECK_EQUAL(output, expected_output);
}

BOOST_AUTO_TEST_CASE( CommonChannels_NormalizedToScalarToNormalized_Int )
{
	int input = -99;
	unsigned int scale = 1000;

	unsigned int output_1 = samplingEngine::channels::NORMALIZED_TO_SCALAR(input, scale);
	int output_2 = samplingEngine::channels::SCALAR_TO_NORMALIZED(output_1, scale, input);
	BOOST_CHECK_EQUAL(output_2, input);
}

/*
	Unsigned Int Normalized
 */
BOOST_AUTO_TEST_CASE( CommonChannels_NormalizedToScalar_UnsignedInt )
{
	unsigned int input = 99;
	unsigned int scale = 1000;
	unsigned int expected_output = 99000;

	unsigned int output = samplingEngine::channels::NORMALIZED_TO_SCALAR(input, scale);
	BOOST_CHECK_EQUAL(output, expected_output);
}

BOOST_AUTO_TEST_CASE( CommonChannels_ScalarToNormalized_UnsignedInt )
{
	unsigned int input = 99000;
	unsigned int scale = 1000;
	unsigned int expected_output = 99;

	unsigned int output = samplingEngine::channels::SCALAR_TO_NORMALIZED(input, scale, expected_output);
	BOOST_CHECK_EQUAL(output, expected_output);
}

BOOST_AUTO_TEST_CASE( CommonChannels_NormalizedToScalarToNormalized_UnsignedInt )
{
	unsigned int input = 99;
	unsigned int scale = 1000;

	unsigned int output_1 = samplingEngine::channels::NORMALIZED_TO_SCALAR(input, scale);
	unsigned int output_2 = samplingEngine::channels::SCALAR_TO_NORMALIZED(output_1, scale, input);
	BOOST_CHECK_EQUAL(output_2, input);
}

BOOST_AUTO_TEST_SUITE_END();
