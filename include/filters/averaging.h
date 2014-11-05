#ifndef ENGINE_FILTERS_AVERAGING_H__
#define ENGINE_FILTERS_AVERAGING_H__

#include <cstdint>
#include <deque>

namespace filters
	{
	template <class T>
	class AveragingFilter
		{
		public:
			AveragingFilter()
				{
				length = 0;
				}
			~AveragingFilter()
				{
				}

			void initialize()
				{
				length = _length;
				sum = T(0);
				values.clear();
				}
			void destroy()
				{
				sum = T(0);
				values.clear();
				}

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
			T get() const
				{
				return (sum / length);
				}

			size_t getLength() const
				{
				return length;
				}

		protected:
			typedef std::deque<T> datalist;

			size_t length;
			T sum;
			datalist values;
		};

	typedef AveragingFilter<int8_t> AveragingFilterInt8;
	typedef AveragingFilter<uint8_t> AveragingFilterUInt8;
	typedef AveragingFilter<int16_t> AveragingFilterInt16;
	typedef AveragingFilter<uint16_t> AveragingFilterUInt16;
	typedef AveragingFilter<int32_t> AveragingFilterInt32;
	typedef AveragingFilter<uint32_t> AveragingFilterUInt32;
	typedef AveragingFilter<int64_t> AveragingFilterInt64;
	typedef AveragingFilter<uint64_t> AveragingFilterUInt64;
	typedef AveragingFilter<float> AveragingFilterFloat;
	typedef AveragingFilter<double> AveragingFilterDouble;
	}

#endif //ENGINE_FILTERS_AVERAGING_H__
