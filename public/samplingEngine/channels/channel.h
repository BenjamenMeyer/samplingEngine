#ifndef SAMPLING_ENGINE_CHANNEL_H__
#define SAMPLING_ENGINE_CHANNEL_H__

#include <stdint.h>

#include <string>
#include <list>

namespace samplingEngine
    {
    namespace channels
        {
        //! channel configuration information
        /*!
         Configuration data for a given data channel in either time or distance records.

         Data Channels are sets of bytes in the data portion of the time or distance records
         that provide some useful information. Some systems used fixed channel sizes; however,
         this has the following side-effects:

            - multiple channels must be reserved to hold data that spans multiple channels
            - downstream systems must know about all the channels and how to properly combine
              them in order to extract the stored data.

         This system uses a dynamic channel configuration with a minimum channel width and no
         real maximum channel width. This allows the channel data to be aligned by the system
         for best performance while keeping all the data together (consecutive bytes). This
         has the benefits that:

            - the channels will always be expandable to the measurements being made
            - the channel data is always consecutive bytes
            - no two channels need to be combined to store any data
            - the system can be optimized for best performance, e.g 4 byte alignment

         Note: Channel Layout should be considered when designing the system so channels are
            placed in a way that provides optimal performance with minimum dead space. That is,
            the following layout is non-optimal:

                channel 1:  offset=0, bytes=1   -> data[0]
                channel 2:  offset=2, bytes=2   -> data[2:3]
                channel 3:  offset=4, bytes=1   -> data[4]
                channel 4:  offset=5, bytes=2   -> data[5:6]

            It would be better if channels 2 and 3 were swapped, thus creating the following
            data layout:

                channel 1:  offset=0, bytes=1   -> data[0]
                channel 2:  offset=2, bytes=1   -> data[1]
                channel 3:  offset=3, bytes=2   -> data[2:3]
                channel 4:  offset=5, bytes=2   -> data[4:5]

            Thus a 7 byte data array becomes a 6 byte data array with data properly aligned
            for optimal processing since 16-bit values are on 16-bit boundaries and there
            is no dead-space (unused bytes) in the data array of the record. When possible,
            channels should align based on their bits consumed, e.g 16-bit values are on
            16-bit boundaries and 64-bit values are on 64-bit boundaries.
            */
        struct channel_config
            {
            //! byte offset into data array for the channel data
            /*!
             The zero-based byte offset from the start of the channel data array in the
             time or distance records where the channel data lives.
             
             Note: For performance reasons it is best to have the data_offset value
                   be a multiple of 2, 4, or 8 to match machine byte boundaries.
                   Most systems will benefit best from a 4 byte (32-bit systems)
                   or 8 bytes (64-bit systems).
             */
            uint16_t data_offset;
            //! number of bytes composing the channel data
            /*!
             The size of the channel data in bytes.

             Minimum channel data size is 1 byte (8 bits).
             Maximum channel data size is 2^16 bytes.

             Channels should only be between 1 and 16 bytes. This supports data sizes of
             up to 128-bit values.
             */
            uint16_t byte_count;
            //! channel type identifier
            /*!
             The integer value that maps to either the distance or time record
             channel types. These ultimately map to input sensor values and output
             measurements values.
             */
            uint16_t channel_type;

            // channel units identifier
            /*!
             channel_units is used to ensure that any required
             conversions (e.g mm -> 100ths of mm) is managed propertly
             only metric units are permissible
             */
            uint16_t channel_units;

            //! scalar<->normalization factor
            /*!
             All channel data is stored as integer data; however, the system
             needs to know what the accuracy of the data is, and how to properly
             display it to the user.

             Consider, for example, a width measurement. The user cares about seeing
             the data in meters but expects a 3 decimal accuracy. Thus the system
             needs to store the value in millimeters. The `factor` will therefore be
             1000. The system can operate on the value as an integer in millimeters,
             or when necessary apply the factor to get to a desired accuracy level.
             When the system displays the value to the user, it will simply take the
             channel data and divide it by the factor.

             For simplicity, the following is true:

                record data = (data * factor)
                display data = (record data / factor)

            The record data is known as `scalar data`; while the display data is
            known as `normalized data`.
             */
            uint16_t factor;

            //! channel description
            /*!
             A string containing user information about the channel.

             Current recommendata is to use either YAML or JSON. The sample engine
             itself does not use anything from this field - it is descriptive only.

             At minimum the field should contain the following inforamtion:

                - name: a human readable name for the channel, f.e Tachometer Counts
                - units: human readable data units, f.e pulses
                - description: human readable description of the channel, f.e pulses
                    detected by the optical encoder for distance travel in the
                    X direction.

             A JSON dictionary might look like the following:

                {
                    'name': '<human readable channel name>'
                    'units': '<human readable channel units>'
                    'description': '<human readable description of the channel>'
                }

             A YAML spec might look like the following:

                name: human readable channel name
                units: human readable channel units
                description: human readable description of the channel

             JSON Example:
                {
                    'name': 'Tachometer Counts',
                    'units': 'pulses',
                    'description': 'pulses from the optical encoder for movement in X-axis'
                }

            YAML Example:

                name: Tachometer Counts
                units: pulses
                description: pulses from the optical encoder for movement in X-axis
             */
            std::string json_data;
            };

        //! channel list
        /*!
         The data channel listing. The order in the list determines
         the channel index.
         */
        typedef std::list<struct channel_config> channelList;

        //! Normalized Data to Scalar Data
        /*!
         Convert data from Normalized Data to Scalar Data.

         Example: 99.125 * 1000 -> 99125
         */
        template <class T, class T2>
        inline T2 NORMALIZED_TO_SCALAR(T normalized, T2 scale)
            {
            return T2(normalized*scale);
            }

        //! Scalar Data to Normalized Data
        /*!
         Convert data from Scalar Data to Normalized Data.

         Example: 99125 / 1000 -> 99.125
         */
        template <class T, class T2>
        inline T SCALAR_TO_NORMALIZED(T2 scalar, T2 scale, const T ignored)
            {
            return T(scalar)/T(scale);
            }
        }
    }

#endif //SAMPLING_ENGINE_CHANNEL_H__
