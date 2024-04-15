#ifndef UTILS_SINE_GENERATOR_H__
#define UTILS_SINE_GENERATOR_H__

#include <stdint.h>
#include <stdexcept>

namespace utils
    {

    //!  utility for generating a sine-wave
    /*!
      The sine wve generator just produces a sine-like wave by incrementing a
      numberic value. It is recommended to use an integer type for T, such
      as uint8_t, uint16_t, uint32_t, or uint64_t or their signed equiavalents.
      These are simple and efficient values.

      If unsigned types are used, then it is recommended to give a starting
      offset equal to at least half the delta between the min and max ranges to
      prevent rollover of the type.
     */
    template<class T>
    class sineWaveGenerator
        {
        public:
            sineWaveGenerator() {}
            ~sineWaveGenerator() {}

            void open(T _starting_offset, T _min, T _max, T _count_by, bool _ascending)
                {
                // encource that it must count by a value greater than 0
                if (_count_by < T(0)) {
                    throw std::out_of_range("counter must be greater than 0");
                }

                is_open = true;
                max = _max;
                min = _min;
                start = _starting_offset;
                count_by = _count_by;
                ascending = _ascending;
                if (start < _min || start > _max)
                    {
                    throw std::out_of_range("start is outside the specified min and max");
                    }
                // is there a good way to test the type to verify it
                // has enough travel for the sinewave? Especially unsigned types?
                if (int64_t(T(-1)) != int64_t(-1))
                    {
                    // calculate the travel
                    double travel_distance = max - min;
                    // determine the max the value can hold
                    double type_max = double(T(-1));
                    // check travel distance is smaller than the maximum of the type
                    // note: this is done using double floating point to try to match
                    //  the maximum range possible. Theoretically a 64-bit unsigned
                    //  integer could also work, but its better to use something larger
                    //  than is actually used for this test
                    if (travel_distance > type_max)
                        {
                        throw std::out_of_range("storage type does not allow enough travel for the specified configuration");
                        }
                    }
                current = start;
                }
            bool isOpen() const
                {
                return is_open;
                }
            void reset()
                {
                current = start;
                }
            void close()
                {
                is_open = false;
                }

            T read()
                {
                // for the purposes here, a sine-wave is just incrementing/decrementing
                // the counter
                T result = current;
                if (ascending) {
                    current += count_by;
                } else {
                    current -= count_by;
                }

                if (current >= max)
                    {
                    ascending = false;
                    }
                else if (current <= min)
                    {
                    ascending = true;
                    }
                return result;
                }

            T reverse()
                {
                ascending = !ascending;
                }

        protected:
            bool is_open{false};
            bool ascending{true};
            T max;
            T min;
            T start;
            T current{0};
            T count_by{1};
        };

    // common types that may be useful
    typedef sineWaveGenerator<int8_t> sineWaveGeneratorSignedInt8;
    typedef sineWaveGenerator<uint8_t> sineWaveGeneratorUnsignedInt8;
    typedef sineWaveGenerator<int16_t> sineWaveGeneratorSignedInt16;
    typedef sineWaveGenerator<uint16_t> sineWaveGeneratorUnsignedInt16;
    typedef sineWaveGenerator<int32_t> sineWaveGeneratorSignedInt32;
    typedef sineWaveGenerator<uint32_t> sineWaveGeneratorUnsignedInt32;
    typedef sineWaveGenerator<int64_t> sineWaveGeneratorSignedInt64;
    typedef sineWaveGenerator<uint64_t> sineWaveGeneratorUnsignedInt64;
    }

#endif //UTILS_SINE_GENERATOR_H__
