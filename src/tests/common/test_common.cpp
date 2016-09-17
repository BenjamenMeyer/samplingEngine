#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MAIN
#define BOOST_TEST_MODULE SamplingEngineTest
#include <boost/test/unit_test.hpp>

#include <samplingEngine/error_codes.h>

BOOST_AUTO_TEST_SUITE( Common );

BOOST_AUTO_TEST_CASE( Common_IsErrorCode )
{
	int32_t real_error_code = (1 | SAMPLING_ENGINE_MASK_ERROR_VALUE);
	uint32_t not_error_code = 2;

	BOOST_CHECK(!SAMPLING_ENGINE_IS_ERROR_CODE(not_error_code));
	BOOST_CHECK(SAMPLING_ENGINE_IS_ERROR_CODE(real_error_code));
}

BOOST_AUTO_TEST_CASE( Common_GetErrorCode )
{
	uint32_t value = 4;
	int32_t masked_value = (value | SAMPLING_ENGINE_MASK_ERROR_VALUE);

	BOOST_CHECK_EQUAL(SAMPLING_ENGINE_GET_ERROR_CODE(masked_value), value);
	BOOST_CHECK_EQUAL(SAMPLING_ENGINE_GET_ERROR_CODE(value), value);
}

BOOST_AUTO_TEST_CASE( Common_MakeErrorCode )
{
	uint32_t value = 8;
	int32_t masked_value = (value | SAMPLING_ENGINE_MASK_ERROR_VALUE);

	BOOST_CHECK_EQUAL(SAMPLING_ENGINE_MAKE_ERROR_CODE(value), masked_value);
}

BOOST_AUTO_TEST_CASE( Common_MatchesErrorCode )
{
	uint32_t value = 16;
	int32_t masked_value = (value | SAMPLING_ENGINE_MASK_ERROR_VALUE);

	BOOST_CHECK(SAMPLING_ENGINE_MATCHES_ERROR_CODE(masked_value, value));
}

BOOST_AUTO_TEST_CASE( Common_CheckSuccess )
{
	int32_t value = (SAMPLING_ENGINE_ERROR_SUCCESS | SAMPLING_ENGINE_MASK_ERROR_VALUE);
	BOOST_CHECK(SAMPLING_ENGINE_CHECK_SUCCESS(value));
}

BOOST_AUTO_TEST_SUITE_END();

