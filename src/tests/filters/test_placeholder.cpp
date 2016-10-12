#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_NO_MAIN

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE( Filters );

BOOST_AUTO_TEST_CASE( Filters_Placeholder )
{
	BOOST_CHECK_EQUAL(true, true);
}

BOOST_AUTO_TEST_SUITE_END();

