
#pragma once

#ifndef __ETERNAL_TIMESTAMP_HPP__
#define __ETERNAL_TIMESTAMP_HPP__

#include "eternal_timestamp.h"
#include <time.h>

namespace eternal_timestamp 
{
	class EternalTimestamp
	{
		static eternal_timestamp_t now();

		static eternal_timestamp_t today();
		static eternal_timestamp_t today_at(int hour = 0xFF, int minute = 0xFF, int second = 0xFF);

		static inline eternal_timestamp_t epoch() { return {0}; };

		// produce a timestamp that has all fields set to 'not specified':
		static inline eternal_timestamp_t unknown() { return {0x3FFFFFFFFFFFFFFFULL}; };

		static int is_valid(eternal_timestamp_t t);
		static int validate(eternal_timestamp_t t);
		static int is_partial_timestamp(eternal_timestamp_t t);
		// convert a partial timestamp by rebasing it against the given base timestamp (using epoch() as default)
		static eternal_timestamp_t normalize(eternal_timestamp_t t, eternal_timestamp_t base = {0});

		static int has_century(eternal_timestamp_t t);
		static int has_year(eternal_timestamp_t t);
		static int has_century_and_year(eternal_timestamp_t t);
		static int has_month(eternal_timestamp_t t);
		static int has_day(eternal_timestamp_t t);
		static int has_hour(eternal_timestamp_t t);
		static int has_minute(eternal_timestamp_t t);
		static int has_seconds(eternal_timestamp_t t);
		static int has_milliseconds(eternal_timestamp_t t);
		static int has_microseconds(eternal_timestamp_t t);
		static int has_complete_date(eternal_timestamp_t t);
		static int has_time(eternal_timestamp_t t);
		static int has_hh_mm_ss(eternal_timestamp_t t);

		static int is_modern_format(eternal_timestamp_t t);
		static int is_prehistoric_format(eternal_timestamp_t t);

		static int64_t calc_time_delta(eternal_timestamp_t t1, eternal_timestamp_t t2);

		static int cvt_to_time_t(time_t &dst, eternal_timestamp_t t);
		static int cvt_to_real(double &dst, eternal_timestamp_t t);
	};

	class ModernEternalTimestamp : public EternalTimestamp
	{
		static eternal_timestamp_t now();

		static eternal_timestamp_t today();
		static eternal_timestamp_t today_at(int hour = 0xFF, int minute = 0xFF, int second = 0xFF);

		static inline eternal_timestamp_t epoch() { return {0}; };

		// produce a timestamp that has all fields set to 'not specified':
		static inline eternal_timestamp_t unknown() { return {0x3FFFFFFFFFFFFFFFULL}; };

		static int is_valid(eternal_timestamp_t t);
		static int validate(eternal_timestamp_t t);
		static int is_partial_timestamp(eternal_timestamp_t t);
		// convert a partial timestamp by rebasing it against the given base timestamp (using epoch() as default)
		static eternal_timestamp_t normalize(eternal_timestamp_t t, eternal_timestamp_t base = {0});

		static int has_century(eternal_timestamp_t t);
		static int has_year(eternal_timestamp_t t);
		static int has_century_and_year(eternal_timestamp_t t);
		static int has_month(eternal_timestamp_t t);
		static int has_day(eternal_timestamp_t t);
		static int has_hour(eternal_timestamp_t t);
		static int has_minute(eternal_timestamp_t t);
		static int has_seconds(eternal_timestamp_t t);
		static int has_milliseconds(eternal_timestamp_t t);
		static int has_microseconds(eternal_timestamp_t t);
		static int has_complete_date(eternal_timestamp_t t);
		static int has_time(eternal_timestamp_t t);
		static int has_hh_mm_ss(eternal_timestamp_t t);

		static int64_t calc_time_delta(eternal_timestamp_t t1, eternal_timestamp_t t2);

		static int cvt_to_time_t(time_t &dst, eternal_timestamp_t t);
		static int cvt_to_real(double &dst, eternal_timestamp_t t);
	};

	class PrehistoricEternalTimestamp : public EternalTimestamp
	{
		static int is_valid(eternal_timestamp_t t);
		static int validate(eternal_timestamp_t t);
		static int is_partial_timestamp(eternal_timestamp_t t);
		// convert a partial timestamp by rebasing it against the given base timestamp (using epoch() as default)
		static eternal_timestamp_t normalize(eternal_timestamp_t t, eternal_timestamp_t base = {0});

		static int has_century(eternal_timestamp_t t);
		static int has_year(eternal_timestamp_t t);
		static int has_century_and_year(eternal_timestamp_t t);
		static int has_month(eternal_timestamp_t t);
		static int has_day(eternal_timestamp_t t);
		static int has_hour(eternal_timestamp_t t);
		static int has_minute(eternal_timestamp_t t);
		static int has_complete_date(eternal_timestamp_t t);
		static int has_time(eternal_timestamp_t t);
		static int has_any_mm_dd_hh_mm(eternal_timestamp_t t);
	};
}

#endif
