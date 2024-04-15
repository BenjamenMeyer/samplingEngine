#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_NO_MAIN

#include <cstdlib>

#include <boost/test/unit_test.hpp>
#include <boost/mpl/list.hpp>

#include <samplingEngineInternal/filters/averaging.h>

template<typename modType>
modType getMod(modType value, modType max)
    {
    // ensure not too large
    if  (value >= max)
        {
        value -= max;
        }
    // ensure not too small
    if (value < 0)
        {
        value += max;
        }
    return value;
    }

BOOST_AUTO_TEST_SUITE( AveragingFilters );

typedef boost::mpl::list<int8_t, uint8_t, int16_t, uint16_t, int32_t, uint32_t, int64_t, uint64_t, float, double> test_types;

// be careful with the length and values as the combination
// needs to be within the limit of the types. For simplicity here
// keep the total value under 128; otherwise additional tests will be
// needed for int8_t and uint8_t.
const size_t length = 10;

BOOST_AUTO_TEST_CASE_TEMPLATE( AveragingFilters_initialize, T, test_types )
{
    filters::AveragingFilter<T> averagingFilterInstance;
    
    averagingFilterInstance.initialize(length);
    BOOST_CHECK_EQUAL(averagingFilterInstance.getLength(), length);
}

BOOST_AUTO_TEST_CASE_TEMPLATE( AveragingFilters_empty, T, test_types )
{
    filters::AveragingFilter<T> averagingFilterInstance;
    
    averagingFilterInstance.initialize(length);

    T result = averagingFilterInstance.get();
    BOOST_CHECK_EQUAL(result, 0);
}

BOOST_AUTO_TEST_CASE_TEMPLATE( AveragingFilters_average_const, T, test_types )
{
    filters::AveragingFilter<T> averagingFilterInstance;

    averagingFilterInstance.initialize(length);
    T value = 10;
    for (size_t i = 0; i < length; ++i)
        {
        averagingFilterInstance.apply(value);
        }

    BOOST_CHECK_EQUAL(averagingFilterInstance.getLength(), length);
    T result = averagingFilterInstance.get();
    BOOST_CHECK_EQUAL(result, value);
}

BOOST_AUTO_TEST_CASE_TEMPLATE( AveragingFilters_average_variable, T, test_types )
{
    filters::AveragingFilter<T> averagingFilterInstance;

    averagingFilterInstance.initialize(length);
    T total = 0;
    T value_max = 10;

    for (size_t i = 0; i < length; ++i)
        {
        T value = getMod<T>(rand(), value_max) + 1;
        averagingFilterInstance.apply(value);
        total += value;
        }
    T expected_average = total / length;

    BOOST_CHECK_EQUAL(averagingFilterInstance.getLength(), length);
    T result = averagingFilterInstance.get();
    BOOST_CHECK_EQUAL(result, expected_average);
}

BOOST_AUTO_TEST_SUITE_END();
