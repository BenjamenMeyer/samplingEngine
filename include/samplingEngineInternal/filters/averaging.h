#ifndef SAMPLING_ENGINE_FILTERS_AVERAGING_H__
#define SAMPLING_ENGINE_FILTERS_AVERAGING_H__

#include <cstdint>
#include <deque>

namespace filters
    {
    //! Value Averaging
    /*!
     High Performance Averaging Measurement

     Maintains a running sum of the values for the associated data channel,
     and a list of those values. When a new value is added it adds it to the sum;
     if there are too many values in the list it subtracts the first value and removes
     it from the list. The Average can be retrieved at any time by dividing the sum
     by the number of entries in the list.

     This methodology keeps from having to iterate over the value list to recalculate
     the sum whenever the average is required.

     The filter is only stable once the maximum number of values has been added to it.
     */
    template <class T>
    class AveragingFilter
        {
        public:
            //! Constructor
            AveragingFilter()
                {
                length = 0;
                }
            //! Destructor
            ~AveragingFilter()
                {
                }

            //! Initialize the filter for use
            /*!
             Initialize the filter for use
             /param _length size_t the maximum number of values in the filter
             */
            void initialize(size_t _length)
                {
                length = _length;
                sum = T(0);
                values.clear();
                }
            //! Destroy the filter resources
            void destroy()
                {
                sum = T(0);
                values.clear();
                }

            //! Apply a measurement value to the filter data for averaging
            /*!
             Apply a new value to the filter and regenerate the running sum;
             if too many values have been applied then remove the oldest.
             /param _value T value to be applied
             */
            void apply(T _value)
                {
                sum += _value;
                values.push_back(_value);

                if (values.length() > length)
                    {
                    sum -= values.front();
                    values.pop_front();
                    }
                }
            //! Access the average
            /*!
             Retrieve the average, calculating it at time of retrieval
             /returns T average value in the form of the type T
             */
            T get() const
                {
                return T(sum / length);
                }

            //! Access the filter length
            /*!
             Access the number of samples required for the filter.
             This defines the number of samples to make the average stable.
             /returns size_t length in terms of number of samples
             */
            size_t getLength() const
                {
                return length;
                }

        protected:
            typedef std::deque<T> datalist; /*!< internal type for storing the values */

            size_t length; /*!< filter length */
            T sum; /*!< Running summation of the values */
            datalist values; /*!< listing of values being averaged. */
        };

    typedef AveragingFilter<int8_t> AveragingFilterInt8; /*!< 8-bit Integer Averaging Filter */
    typedef AveragingFilter<uint8_t> AveragingFilterUInt8; /*!< 8-bit Unsigned Integer Averaging Filter */
    typedef AveragingFilter<int16_t> AveragingFilterInt16; /*!< 16-bit Integer Averaging Filter */
    typedef AveragingFilter<uint16_t> AveragingFilterUInt16; /*!< 16-bit Unsigned Integer Averaging Filter */
    typedef AveragingFilter<int32_t> AveragingFilterInt32; /*!< 32-bit Integer Averaging Filter */
    typedef AveragingFilter<uint32_t> AveragingFilterUInt32; /*!< 32-bit Unsigned Integer Averaging Filter */
    typedef AveragingFilter<int64_t> AveragingFilterInt64; /*!< 64-bit Integer Averaging Filter */
    typedef AveragingFilter<uint64_t> AveragingFilterUInt64; /*!< 64-bit Unsigned Integer Averaging Filter */
    typedef AveragingFilter<float> AveragingFilterFloat; /*!< Single Precision Floating Point Averaging Filter */
    typedef AveragingFilter<double> AveragingFilterDouble; /*!< Double Precision Floating Point Averaging Filter */
    }

#endif //SAMPLING_ENGINE_FILTERS_AVERAGING_H__
