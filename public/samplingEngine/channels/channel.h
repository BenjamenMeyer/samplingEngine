#ifndef SAMPLING_ENGINE_CHANNEL_H__
#define SAMPLING_ENGINE_CHANNEL_H__

#include <stdint.h>

#include <string>
#include <list>

namespace samplingEngine
    {
    namespace channels
        {
        // channel configuration information
        struct channel_config
            {
            // byte offset in data array for the channel data
            // Note: For performance reasons it is best to have the data_offset value
            //       be a multiple of 2, 4, or 8 to match machine byte boundaries.
            //       Most systems will benefit best from a 4 byte (32-bit systems)
            //       or 8 bytes (64-bit systems).
            uint16_t data_offset;
            // number of bytes composing the channel data
            uint16_t byte_count;
            // channel type identifier
            uint16_t channel_type;

            // channel units identifier
            // channel_units is used to ensure that any required
            // conversions (e.g mm -> 100ths of mm) is managed propertly
            // only metric units are permissible
            uint16_t channel_units;

            // scalar<->normalization factor
            // All channel data is stored as integer data
            uint16_t factor;

            // JSON dict containing the various text
            // For simplicity, the various textual fields are stored
            // as a single text string in a JSON format.
            // At minimum, the JSON dict should contain:
            // {
            //    'name': '<human readable channel name>'
            //    'units': '<human readable channel units>'
            //    'description': '<human readable description of the channel>'
            // }
            //
            std::string json_data;
            };

        // list of channels
        typedef std::list<struct channel_config> channelList;

        // Channel Normalized Data to Scalar Data
        template <class T>
        inline T NORMALIZED_TO_SCALAR(T d, T f)
            {
            return T(d*f);
            }

        // Channel Scalar Data to Noramlized Data
        template <class T>
        inline T SCALAR_TO_NORMALIZED(T d, T f)
            {
            return T(d/f);
            }
        }
    }

#endif //SAMPLING_ENGINE_CHANNEL_H__