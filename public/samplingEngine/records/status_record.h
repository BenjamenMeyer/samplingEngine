#ifndef SAMPLING_ENGINE_STATUS_RECORD_H__
#define SAMPLING_ENGINE_STATUS_RECORD_H__

#include <stdint.h>

namespace samplingEngine
    {
    namespace records
        {
        //! Channel Status Values
        /*!
         Data Channels have a general state based on their input. Some
         channels, like the Tachometer, are always valid. Other channels
         require certain amounts of data before they can be calculated,
         or must only be calculated under certain conditions (e.g above
         a certain speed). The Channel Status Value provides this state
         information in the data stream.
         */
        enum channelStatusValues
            {
            CHANNEL_STATUS_VALID=0x00000000,                        /*! data is valid */
            CHANNEL_STATUS_INCOMPLETE_SENSOR_DATA=0x00000001,       /*! data is missing for one or more required sensors */
            CHANNEL_STATUS_DELAY_BUFFER_FILLING=0x00000002,         /*! calculation buffer does not have sufficient data */
            CHANNEL_STATUS_FILTER_CUTOFF_NOT_MET=0x00000004,        /*! data generating signals below the cut off filter */
            CHANNEL_STATUS_FILTER_CUTOFF_EXCEEDED=0x00000008,       /*! data generating signals above the cut off filter */
            CHANNEL_STATUS_RESERVED_01=0x00000010,                  /*! Reserved for future meaning */
            CHANNEL_STATUS_RESERVED_02=0x00000020,                  /*! Reserved for future meaning */
            CHANNEL_STATUS_RESERVED_03=0x00000040,                  /*! Reserved for future meaning */
            CHANNEL_STATUS_RESERVED_04=0x00000080,                  /*! Reserved for future meaning */
            CHANNEL_STATUS_RESERVED_05=0x00000100,                  /*! Reserved for future meaning */
            CHANNEL_STATUS_RESERVED_06=0x00000200,                  /*! Reserved for future meaning */
            CHANNEL_STATUS_RESERVED_07=0x00000400,                  /*! Reserved for future meaning */
            CHANNEL_STATUS_RESERVED_08=0x00000800,                  /*! Reserved for future meaning */
            CHANNEL_STATUS_RESERVED_09=0x00001000,                  /*! Reserved for future meaning */
            CHANNEL_STATUS_RESERVED_10=0x00002000,                  /*! Reserved for future meaning */
            CHANNEL_STATUS_RESERVED_11=0x00004000,                  /*! Reserved for future meaning */
            CHANNEL_STATUS_RESERVED_12=0x00008000,                  /*! Reserved for future meaning */
            CHANNEL_STATUS_RESERVED_13=0x00010000,                  /*! Reserved for future meaning */
            CHANNEL_STATUS_RESERVED_14=0x00020000,                  /*! Reserved for future meaning */
            CHANNEL_STATUS_RESERVED_15=0x00040000,                  /*! Reserved for future meaning */
            CHANNEL_STATUS_RESERVED_16=0x00080000,                  /*! Reserved for future meaning */
            CHANNEL_STATUS_RESERVED_17=0x00100000,                  /*! Reserved for future meaning */
            CHANNEL_STATUS_RESERVED_18=0x00200000,                  /*! Reserved for future meaning */
            CHANNEL_STATUS_RESERVED_19=0x00400000,                  /*! Reserved for future meaning */
            CHANNEL_STATUS_RESERVED_20=0x00800000,                  /*! Reserved for future meaning */
            CHANNEL_STATUS_RESERVED_21=0x01000000,                  /*! Reserved for future meaning */
            CHANNEL_STATUS_RESERVED_22=0x02000000,                  /*! Reserved for future meaning */
            CHANNEL_STATUS_RESERVED_23=0x04000000,                  /*! Reserved for future meaning */
            CHANNEL_STATUS_RESERVED_24=0x08000000,                  /*! Reserved for future meaning */
            CHANNEL_STATUS_RESERVED_25=0x10000000,                  /*! Reserved for future meaning */
            CHANNEL_STATUS_RESERVED_26=0x20000000,                  /*! Reserved for future meaning */
            CHANNEL_STATUS_RESERVED_27=0x40000000,                  /*! Reserved for future meaning */
            CHANNEL_STATUS_RESERVED_28=0x80000000,                  /*! Reserved for future meaning */
            };

        //! Channel Status
        /*!
         The status for a given data channel
         */
        struct status_record_entry
            {
            //! Index of the channel
            /*!
             Channel Array Index the status is for.
             */
            uint16_t channel_index;
            //! Channel Status Bitmap
            /*!
             The explicit status of the channel. The value is a combination of
             all applicable channel status are specified in the bitmap at every
             specification.
             */
            uint16_t channel_status;
            };

        //! Status record
        /*!
         The complete status record for all configured channels.

         Every configured channel is specified in full every time the record
         is generated.
         */
        struct status_record
            {
            //! Length in bytes of the entire record
            uint32_t length;
            //! Record identifier
            uint32_t id;
            //! List of status entries, one for each configured channel
            struct samplingEngine::records::status_record_entry channelStatus[1];
            };
        }
    }

#endif //SAMPLING_ENGINE_STATUS_RECORD_H__
