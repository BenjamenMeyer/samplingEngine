#ifndef SAMPLING_ENGINE_TIME_RECORD_H__
#define SAMPLING_ENGINE_TIME_RECORD_H__

#include <stdint.h>

namespace samplingEngine
    {
    namespace records
        {
        namespace time_record_flags
            {
            //! Time Record Flags
            /*!
             Flags that specify various time-based states that must
             be carried through the system.
             */
            enum timeFlags
                {
                TIME_FLAGS_CLEAR=0,                /*!< No flags are set */
                TIME_FLAGS_SIMULATION_MODE,        /*!< Simulation Mode Enabled */
                };
            };

        //! Time Data Record
        /*!
         The Time Data Record; there are certain portions that are guaranteed
         to exist; the rest are left to the Time Channel Map to define how
         they will look. The Time Records are generally raw sensor data.
         */
        struct time_record
            {
            //! Length in bytes of the entire record
            uint32_t length;
            //! Record identifier
            uint32_t id;
            //! Time Record Index
            uint64_t index;
            //! Tachometer (Encoder) Sensor
            /*!
             Distance Moved in pulses, raw signal.
             */
            int64_t tachometer;
            //! Active flags
            uint64_t flags;
            //! Time Channel Data Array
            /*!
             See Time Channel Specification for the run-time dynamic meaning.
             */
            uint8_t channels[1];
            };
        }
    }

#endif //SAMPLING_ENGINE_TIME_RECORD_H__
