#ifndef ENGINE_CONFIGURATION_H__
#define ENGINE_CONFIGURATION_H__

#include <stdint.h>

#include "time_channels.h"
#include "distance_channels.h"
#include "channel.h"

struct engine_configuration
	{
	struct channels* ptr_time_channels;		// aka input channels
	struct channels* ptr_distance_channels;		// aka output channels
	
	struct tachometer
		{
		uint64_t pulses_per_meter;		// Tachometer Pulses (counts) Per Meter
		} tachometer;
        struct sampling
                {
                uint16_t time_sample_rate_hz;           // Time Sample Rate in HZ (e.g 100 HZ, 240 HZ, 400 HZ, 1000 HZ)
                uint16_t distance_sample_rate_mm;       // Distance Sample Rate in Millimeters
                } sampling;
	};


#endif //ENGINE_CONFIGURATION_H__
