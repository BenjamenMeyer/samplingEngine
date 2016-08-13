#ifndef SAMPLING_ENGINE_TIME_CHANNELS_H__
#define SAMPLING_ENGINE_TIME_CHANNELS_H__

namespace samplingEngine
    {
    namespace channels
        {
        namespace time
            {
            //! Time Record Data Channels
            /*!
             Channel Type for the Time Data Record's Channels stored
             in its Data Array.
             */
            enum timeChannels
                {
                INVALID_CHANNEL=0,            /*!< Invalid Data Channel */

                // Record Channels
                TIME_RECORD_INDEX,            /*!< Record index from when the system started, zero-based */

                // Diagnostic Channels
                TEST_CHANNEL_SINE_WAVE,       /*!< Sine Wave Data Channel for Diagnostics */
                TEST_CHANNEL_COSINE_WAVE,     /*!< Co-sine Wave Data Channel for Diagnostics */

                // Basic Sensors
                TACHOMETER,                   /*!< Tachometer, useful for Diagnostics */
                INERTIAL_PITCH_GYRO,          /*!< Inertial Instrument's Pitch (Gyro) */
                INERTIAL_PITCH_ACCELEROMETER, /*!< Inertial Instrument's Pitch (Accelerometer) */
                INERTIAL_YAW_GYRO,            /*!< Inertial Instrument's Yaw (Gyro) */
                INERTIAL_YAW_ACCELEROMETER,   /*!< Inertial Instrument's Yaw (Accelerometer) */
                INERTIAL_ROLL_GYRO,           /*!< Inertial Instrument's Roll (Gyro) */
                INERTIAL_ROLL_ACCELEROMETER,  /*!< Inertial Instrument's Roll (Accelerometer) */

                // Basic Calculations
                TACHOMETER_SPEED,             /*!< Velocity (Delta Tachometer) */
                TACHOMETER_ACCELERATION,      /*!< Acceleration  (Delta Tachometer Speed)*/
                TACHOMETER_JERK,              /*!< Rate of Change of Acceleration (Delta Tachometer Acceleration) */

                PITCH,                        /*!< X-Axis Rotation */
                PITCH_VELOCITY,               /*!< Velocity of change in Pitch (Delta Pitch) */
                PITCH_ACCELERATION,           /*!< Acceleration of Pitch (Delta Pitch Velocity) */
                PITCH_JERK,                   /*!< Rate of Change of Pitch Acceleration (Delta Pitch Acceleration) */

                YAW,                          /*!< Z-Axis Rotation */
                YAW_VELOCITY,                 /*!< Velocity of change in Yaw (Delta Yaw) */
                YAW_ACCELERATION,             /*!< Acceleration of Yaw (Delta Yaw Velocity) */
                YAW_JERK,                     /*!< Rate of Change of Yaw Acceleration (Delta Yaw Acceleration) */

                ROLL,                         /*!< Z-Axis Rotation */
                ROLL_VELOCITY,                /*!< Velocity of change in Roll (Delta Roll) */
                ROLL_ACCELERATION,            /*!< Acceleration of Roll (Delta Roll Velocity) */
                ROLL_JERK,                    /*!< Rate of Change of Roll Acceleration (Delta Roll Acceleration) */

                LONGITUDINAL,                 /* X-Axis Rotation (Pitch) */
                LATITUDINAL,                  /* Y-Axis Rotation (Roll) */
                SPIN,                         /* Z-Axis Rotation (Yaw) */
                };
            }
        }
    }

#endif //SAMPLING_ENGINE_TIME_CHANNELS_H__
