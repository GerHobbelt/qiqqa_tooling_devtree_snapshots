
#pragma once

#ifndef __ETERNAL_TIMESTAMP_H__
#define __ETERNAL_TIMESTAMP_H__

#include <stdint.h>

#if defined(__cplusplus)
extern "C" {
#endif

// available range: 3000 AD .. 48200 BC

struct eternal_modern_timestamp 
{
	unsigned dummy: 1;
	unsigned mode: 1;     // MUST be ZERO.

	// legal values for each field are 0..N-1; highest possible value for the bitfield is the 'magic value' indicating 'not specified'.

	unsigned century: 9;
	unsigned year: 7;
	unsigned month: 4;
	unsigned day: 5;     // NOTE: legal day numbers are 0..30, NOT 1..31 as you might assume!
	unsigned hour: 5;
	unsigned minute: 6;
	unsigned seconds: 6;
	unsigned milliseconds: 10;
	unsigned microseconds: 10;
};

// available range: 48200 BC .. Big Bang & before.

struct eternal_prehistoric_timestamp 
{
	unsigned dummy: 1;
	unsigned mode: 1;     // MUST be ONE.

	// legal values for each field are 0..N-1; highest possible value for the bitfield is the 'magic value' indicating 'not specified'.

	uint64_t years: 38;
	unsigned month: 4;
	unsigned day: 5;     // NOTE: legal day numbers are 0..30, NOT 1..31 as you might assume!
	unsigned hour: 5;
	unsigned minute: 6;
	unsigned precision: 4;
};

typedef union eternal_timestamp_u 
{
	uint64_t t;
	struct eternal_modern_timestamp modern;
	struct eternal_prehistoric_timestamp prehistoric;
} eternal_timestamp_t;


#if defined(__cplusplus)
}
#endif

#endif
