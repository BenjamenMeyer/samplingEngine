#ifndef SAMPLING_ENGINE_DISTANCE_RECORD_H__
#define SAMPLING_ENGINE_DISTANCE_RECORD_H__

#include <stdint.h>

namespace samplingEngine
    {
    namespace records
        {
        namespace distance_record_flags
            {
            // Distance Record Flags
            /*!
             Flags that specify various distance-based states that must
             be carried through the system; these are generally related
             to similar flags from the time records.
             */
            enum distanceFlags
                {
                DISTANCE_FLAGS_CLEAR=0,         /*!< No Flags are set */
                DISTANCE_FLAGS_SIMULATION_MODE, /*!< Simulation Mode Enabled */
                };
            };

        //! Associated Time Sample Index Ranges
        /*!
         The system has a maximum time sample rate that determines
         the maximum velocity for capturing data. As the velocity
         reaches that maximum velocity value then the start/end
         indexes will shrink together and ultimately reach the same
         value at the maximum velocity.

         For example, 400 HZ time collection yields a maximum
         velocity of 360 KPH. When the vehicle stands still, no
         distance data will be able to be generated since it is not
         moving and thus the maximum number of possible time sample
         data records will be used for generating the distance sample
         that eventually comes out. As the system goes from 0 KPH (zero)
         to 360 KPH fewer time sample records will be used for each
         distance record. When the system reaches 360 KPH then there will
         be 1 time record for each distance record (start = end).
         It is not wise to surpass the maximum velocity (start > end) as
         data will then be unreliable.
         */
        struct time_indexes
            {
            uint64_t start_index; /*!< earliest time sample used to generate the distance sample */
            uint64_t end_index;   /*!< latest time sample used to generate the distance sample */
            };

        //! Distance Data Record
        /*!
         The Distance Data Record; there are certain portions that are guaranteed
         to exist; the rest are left to the Distance Channel Map to define how
         they will look. The Distance Records are generally calculated sensor data.
         */
        struct distance_record
            {
            //! Length in bytes of the entire record
            uint32_t length;
            //! Record identifier
            uint32_t id;
            //! Distance Record Index
            uint64_t sample_index;
            //! Associated time sample index range
            struct time_indexes index;
            //! Tachometer (Encoder) Sensor - Distance Moved in pulses
            /*!
             Distance Moved in pulses

             Some implementations allow the distance record to vary slightly
             around where it should be generated, e.g 250mm +/- 5mm, based on
             when the time samples come in.

             Other implementations will allow for interpolation between the
             samples in order to put all the data as close to the true
             location of the distance record as possible.

             Both have valid and invalid points against why they should be.
             */
            int64_t tachometer;
            //! Active flags
            uint64_t flags;
            //! Distance Channel Data Array
            /*!
             See Distance Channel Specification for the run-time dynamic meaning.
             */
            uint8_t channels[1];
            };
        }
    }

#endif //SAMPLING_ENGINE_DISTANCE_RECORD_H__
