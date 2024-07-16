#ifndef CHAOS_GENERATORS_LINEAR_HH
#define CHAOS_GENERATORS_LINEAR_HH

#include "chaos/types.hh"

#include <type_traits>

namespace chaos { //::chaos ////////////////////////////////////////////////////
namespace generators { //::chaos::generators ///////////////////////////////////

// http://courses.cse.tamu.edu/csce680/walker/lfsr_table.pdf

template <class utype, utype a, utype c, utype m>
class lcg {
protected:
	utype s;

public:
	// metadata
	CHAOS_META_DEFINE("LCG (Linear Congruential Generator)", "???");

	// typename
	typedef utype size_seed;
	typedef utype size_next;

	explicit lcg() : s(2147483648) {}

	void seed(utype seed) { s = seed; }

	inline utype next() {
		return (s = ((a) * s + (c)) % (m));
	}
};

template <class utype, utype a, utype c, class Enable = void>
// specialization for modulo 2^N types where N is the size of the utype in bits (32 for uint32_t, etc.)
class lcg_no_modulo {
protected:
	utype s;

public:
	// metadata
	CHAOS_META_DEFINE("LCG (Linear Congruential Generator)", "???");

	// typename
	typedef utype size_seed;
	typedef utype size_next;

	explicit lcg_no_modulo() : s(2147483648) {}

	void seed(utype seed) { s = seed; }

	inline utype next() { return (s = ((a)*s + (c))); }
};

} //::chaos::generators ////////////////////////////////////////////////////////
} //::chaos ////////////////////////////////////////////////////////////////////

CHAOS_GENERATOR_REGISTER_3PARAM(LCG_ZX81p, chaos::generators::lcg, uint16_t, 75, 74, (1U << 16) - 1); // Wikipedia says modulo is 2^16+1
CHAOS_GENERATOR_REGISTER_3PARAM(LCG_RANDUp, chaos::generators::lcg, uint32_t, 65539, 1, 1U << 31);  // Wikipedia says ADD=0, but that would make this one quite prone to all-zero output, so we modify to ADD=1
CHAOS_GENERATOR_REGISTER_3PARAM(LCG32, chaos::generators::lcg_no_modulo, uint32_t, 0x915f77f5U, 1, void);           // Steele and Vigna: table 4, row 5
CHAOS_GENERATOR_REGISTER_3PARAM(LCG64, chaos::generators::lcg_no_modulo, uint64_t, 0xd1342543de82ef95ULL, 1, void); // Steele and Vigna: table 6, row 5

#endif // CHAOS_GENERATORS_LINEAR_HH
