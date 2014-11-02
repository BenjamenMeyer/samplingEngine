#ifndef ENGINE_CHANNEL_H__
#define ENGINE_CHANNEL_H__

#include <stdint.h>

struct channel_config
{
    uint16_t channel_index;    // channel index
    uint16_t byte_count;       // number of bytes composing the channel data
    uint16_t channel_type;     // channel type identifier

    // channel_units is used to ensure that any required
    // conversions (e.g mm -> 100ths of mm) is managed propertly
    // only metric units are permissible
    uint16_t channel_units;    // channel units identifier

    // All channel data is stored as integer data
    uint16_t factor;           // scalar<->normalization factor

    // For simplicity, the various textual fields are stored
    // as a single text string in a JSON format.
    // At minimum, the JSON dict should contain:
    // {
    //    'name': '<human readable channel name>'
    //    'units': '<human readable channel units>'
    //    'description': '<human readable description of the channel>'
    // }
    //
    uint16_t json_data_length; // JSON dict containing the various text
    uint8_t  json[1];          // json dict text
};

struct channels
{
    uint16_t channel_count;   // total number of channels
    struct channel_config config[1]; // array of channels
};

// Channel Normalized Data to Scalar Data
#define NORMALIZED_TO_SCALAR(d, f) (d*f)

// Channel Scalar Data to Noramlized Data
#define SCALAR_TO_NORMALIZED(d, f) (d/f)

#endif //ENGINE_CHANNEL_H__
