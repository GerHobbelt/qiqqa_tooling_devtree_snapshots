#ifndef CHAOS_GENERATORS_XORSHIFT_HH
#define CHAOS_GENERATORS_XORSHIFT_HH

#include "chaos/types.hh"

namespace chaos { //::chaos ////////////////////////////////////////////////////
namespace generators { //::chaos::generators ///////////////////////////////////

namespace xorshift_seedemixer {

/*
Initialization

In the xoshiro paper, it is recommended to initialize the state of the
generators using a generator which is radically different from the initialized
generators, as well as one which will never give the "all-zero" state; for
shift-register generators, this state is impossible to escape from. The authors
specifically recommend using the SplitMix64 generator, from a 64-bit seed, as
follows:
*/

constexpr uint64_t splitmix64(uint64_t &state) {
	state += 0x9E3779B97f4A7C15ULL;
	uint64_t result = state;

	// extra patch to prevent all-zero state in adversarial state init situation:
	//result |= 0x1000100000001000ULL;

	result = (result ^ (result >> 30)) * 0xBF58476D1CE4E5B9ULL;
	result = (result ^ (result >> 27)) * 0x94D049BB133111EBULL;

	// extra patch to prevent all-zero state in adversarial state init situation:
	const uint32_t shift = result & 63;
	const uint64_t mask = (((uint64_t)1) << shift);
	result |= mask;

	return result ^ (result >> 31);
}

constexpr inline uint64_t splitmix(uint64_t &state) {
	return splitmix64(state);
}

// quickly whipped up 32bit version
constexpr uint32_t splitmix32(uint32_t &state) {
	state += 0x7f4A7C15U;
	uint32_t result = state;

	// extra patch to prevent all-zero state in adversarial state init situation:
	//result |= 0x00001000U;

	result = (result ^ (result >> 14)) * 0xBF58476DU;
	result = (result ^ (result >> 11)) * 0x94D049BBU;

	// extra patch to prevent all-zero state in adversarial state init situation:
	const uint32_t shift = result & 31;
	const uint32_t mask = (((uint32_t)1) << shift);
	result |= mask;

	return result ^ (result >> 15);
}

constexpr inline uint32_t splitmix(uint32_t &state) {
	return splitmix32(state);
}

// one could do the same for any of the other generators
constexpr void xorshift128_init(uint32_t state[4], uint64_t seed) {
	uint64_t tmp = splitmix64(seed);
	state[0] = (uint32_t)tmp;
	state[1] = (uint32_t)(tmp >> 32);

	tmp = splitmix64(seed);
	state[2] = (uint32_t)tmp;
	state[3] = (uint32_t)(tmp >> 32);
}

constexpr void xorwow_init(uint32_t state[6], uint64_t seed) {
	uint64_t tmp = splitmix64(seed);
	state[0] = (uint32_t)tmp;
	state[1] = (uint32_t)(tmp >> 32);

	tmp = splitmix64(seed);
	state[2] = (uint32_t)tmp;
	state[3] = (uint32_t)(tmp >> 32);

	tmp = splitmix64(seed);
	state[4] = (uint32_t)tmp;
	state[5] = (uint32_t)(tmp >> 32);
}

} // internal namespace

//-------------------------------------------------------------------------


template <class utype, utype a, utype b, utype c> class xorshift {
protected:
	utype s;

public:
	// metadata
	CHAOS_META_DEFINE("xorshift", "George Marsaglia");

	// typename
	typedef utype size_seed;
	typedef utype size_next;

	explicit xorshift() : s(2463534242) {}

	void seed(utype seed) { s = xorshift_seedemixer::splitmix(seed); }

	inline utype next() {
		s ^= s << a;
		s ^= s >> b;
		return (s ^= s << c);
	}
};

// source: https://en.wikipedia.org/wiki/Xorshift

/*
Xorshift random number generators, also called shift-register generators, are a
class of pseudorandom number generators that were invented by George
Marsaglia. They are a subset of linear-feedback shift registers (LFSRs) which
allow a particularly efficient implementation in software without the excessive
use of sparse polynomials. They generate the next number in their sequence by
repeatedly taking the exclusive or of a number with a bit-shifted version of
itself. This makes execution extremely efficient on modern computer
architectures, but it does not benefit efficiency in a hardware implementation.
Like all LFSRs, the parameters have to be chosen very carefully in order to
achieve a long period.

For execution in software, xorshift generators are among the fastest PRNGs,
requiring very small code and state. However, they do not pass every statistical
test without further refinement. This weakness is amended by combining them with
a non-linear function, as described in the original paper. Because plain
xorshift generators (without a non-linear step) fail some statistical tests,
they have been accused of being unreliable.

Example implementation

A C version[a] of three xorshift algorithms  is given here. The first
has one 32-bit word of state, and period 2^32−1. The second has one 64-bit word
of state and period 2^64−1. The last one has four 32-bit words of state, and
period 2^128−1. The 128-bit algorithm passes the diehard tests. However, it fails
the MatrixRank and LinearComp tests of the BigCrush test suite from the TestU01
framework.

All use three shifts and three or four exclusive-or operations:

- XORSHIFT32
- XORSHIFT64   (this implementation requires you use uint64_t, not uint32_t)
- XORSHIFT128
*/

template <class utype, utype a, utype b, utype c> class xorshift128 {
protected:
	utype s[4];

public:
	// metadata
	CHAOS_META_DEFINE("xorshift128", "George Marsaglia");

	// typename
	typedef utype size_seed[4];
	typedef utype size_next;

	explicit xorshift128()
		: s({1204974936, 1885686145, 673330634, 2463534242})
	{}

	void seed(utype seed) {
		xorshift_seedemixer::xorshift128_init(s, seed);
	}

	inline utype next() {
		/* Algorithm "xor128" from p. 5 of Marsaglia, "Xorshift RNGs" */
		utype t = s[3];

		utype s0 = s[0]; /* Perform a contrived 32-bit shift. */
		s[3] = s[2];
		s[2] = s[1];
		s[1] = s0;

		t ^= t << a;
		t ^= t >> b;
		return (s[0] = t ^ s0 ^ (s0 >> c));
	}
};

/*
Non-linear variations

All xorshift generators fail some tests in the BigCrush test suite. This is true for all generators based on linear recurrences, such as the Mersenne Twister or WELL. However, it is easy to scramble the output of such generators to improve their quality.

The scramblers known as + and * still leave weakness in the low bits,[4] so they are intended for floating point use, where the lowest bits of floating-point numbers have a smaller impact on the interpreted value. For general purpose, the scrambler ** (pronounced starstar) makes the LFSR generators pass in all bits.

xorwow

Marsaglia suggested scrambling the output by combining it with a simple additive counter modulo 232 (which he calls a "Weyl sequence" after Weyl's equidistribution theorem). This also increases the period by a factor of 2^32, to 2^192−2^32:

This performs well, but fails a few tests in BigCrush.[6] This generator is the default in Nvidia's CUDA toolkit.
*/

template <class utype, utype a, utype b, utype c, utype d> class xorwow {
protected:
	utype s[4];

public:
	// metadata
	CHAOS_META_DEFINE("xorwow", "George Marsaglia");

	// typename
	typedef utype size_seed[6];  // 1 counter + 5 seed
	typedef utype size_next;

	explicit xorwow()
		: s({1204974936, 1885686145, 673330634, 2463534242, 18141480, 1}) {}

	void seed(utype seed) {
		xorshift_seedemixer::xorwow_init(s, seed);
	}

	inline utype next() {
		/* Algorithm "xorwow" from p. 5 of Marsaglia, "Xorshift RNGs" */
		utype t = s[4];

		utype s0 = s[0]; /* Perform a contrived 32-bit shift. */
		s[4] = s[3];
		s[3] = s[2];
		s[2] = s[1];
		s[1] = s0;

		t ^= (t >> a);
		t ^= (t << b);
		t ^= (s0 ^ (s0 << c));
		s[0] = t;
		utype &counter = s[5];
		counter += d;
		return t + counter;
	}
};

/*
xorshift*

An xorshift* generator applies an invertible multiplication (modulo the word size) as a non-linear transformation to the output of an xorshift generator, as suggested by Marsaglia.[1] All xorshift* generators emit a sequence of values that is equidistributed in the maximum possible dimension (except that they will never output zero for 16 calls, i.e. 128 bytes, in a row).

The following 64-bit generator has a maximal period of 2^64−1.

The generator fails only the MatrixRank test of BigCrush, however if the generator is modified to return only the high 32 bits, then it passes BigCrush with zero failures.  In fact, a reduced version with only 40 bits of internal state passes the suite, suggesting a large safety margin.  A similar generator suggested in Numerical Recipes as RanQ1 also fails the BirthdaySpacings test.
*/


template <class utype, utype a, utype b, utype c> class xorshiftplus {
protected:
	utype s;

public:
	// metadata
	CHAOS_META_DEFINE("xorshift+", "George Marsaglia");

	// typename
	typedef utype size_seed;
	typedef utype size_next;

	explicit xorshiftplus()
	    : s(1) {}

	void seed(utype seed) {
		s = xorshift_seedemixer::splitmix(seed);
	}

	inline utype next() {
		/* initial seed must be nonzero, don't use a static variable for the state
		 * if multithreaded */
		utype x = s;
		x ^= x >> a;
		x ^= x << b;
		x ^= x >> c;
		s = x;
		return x * 0x2545F4914F6CDD1DULL;
	}
};

/*
Vigna suggests the following xorshift1024* generator with 1024 bits of state and a maximal period of 2^1024−1; however, it does not always pass BigCrush. xoshiro256** is therefore a much better option.
*/


#if 0

/* The state must be seeded so that there is at least one non-zero element in array */
struct xorshift1024s_state {
	uint64_t x[16];
	int index;
};

uint64_t xorshift1024s(struct xorshift1024s_state *state)
{
	int index = state->index;
	uint64_t const s = state->x[index++];
	uint64_t t = state->x[index &= 15];
	t ^= t << 31;       // a
	t ^= t >> 11;       // b  -- Again, the shifts and the multipliers are tunable
	t ^= s ^ (s >> 30); // c
	state->x[index] = t;
	state->index = index;
	return t * 1181783497276652981ULL;
}

/*
xorshift+

An xorshift+ generator can achieve an order of magnitude fewer failures than Mersenne Twister or WELL. A native C implementation of an xorshift+ generator that passes all tests from the BigCrush suite can typically generate a random number in fewer than 10 clock cycles on x86, thanks to instruction pipelining.

Rather than using multiplication, it is possible to use addition as a faster non-linear transformation. The idea was first proposed by Saito and Matsumoto (also responsible for the Mersenne Twister) in the XSadd generator, which adds two consecutive outputs of an underlying xorshift generator based on 32-bit shifts. However, one disadvantage of adding consecutive outputs is that, while the underlying xorshift128 generator is 2-dimensionally equidistributed, the xorshift128+ generator is only 1-dimensionally equidistributed.

XSadd has some weakness in the low-order bits of its output; it fails several BigCrush tests when the output words are bit-reversed. To correct this problem, Vigna introduced the xorshift+ family, based on 64-bit shifts. xorshift+ generators, even as large as xorshift1024+, exhibit some detectable linearity in the low-order bits of their output; it passes BigCrush, but doesn't when the 32 lowest-order bits are used in reverse order from each 64-bit word. This generator is one of the fastest generators passing BigCrush.

The following xorshift128+ generator uses 128 bits of state and has a maximal period of 2^128−1.
*/


#include <stdint.h>

struct xorshift128p_state {
	uint64_t x[2];
};

/* The state must be seeded so that it is not all zero */
uint64_t xorshift128p(struct xorshift128p_state *state)
{
	uint64_t t = state->x[0];
	uint64_t const s = state->x[1];
	state->x[0] = s;
	t ^= t << 23;      // a
	t ^= t >> 18;      // b -- Again, the shifts and the multipliers are tunable
	t ^= s ^ (s >> 5); // c
	state->x[1] = t;
	return t + s;
}

/*
xoshiro / xoroshiro

xoshiro (short for "xor, shift, rotate") and xoroshiro (short for "xor, rotate, shift, rotate") use rotations in addition to shifts. According to Vigna, they are faster and produce better quality output than xorshift.

This class of generator has variants for 32-bit and 64-bit integer and floating point output; for floating point, one takes the upper 53 bits (for binary64) or the upper 23 bits (for binary32), since the upper bits are of better quality than the lower bits in the floating point generators. The algorithms also include a jump function, which sets the state forward by some number of steps – usually a power of two that allows many threads of execution to start at distinct initial states.

For 32-bit output, xoshiro128** and xoshiro128+ are exactly equivalent to xoshiro256** and xoshiro256+, with uint32_t in place of uint64_t, and with different shift/rotate constants.

More recently, the xoshiro++ generators have been made as an alternative to the xoshiro** generators. They are used in some implementations of Fortran compilers such as GNU Fortran, Java, and Julia.

xoshiro256**

xoshiro256** is the family's general-purpose random 64-bit number generator. It is used in GNU Fortran compiler, Lua (as of Lua 5.4), and the .NET framework (as of .NET 6.0).
*/

/*  Adapted from the code included on Sebastiano Vigna's website */

#include <stdint.h>

uint64_t rol64(uint64_t x, int k)
{
	return (x << k) | (x >> (64 - k));
}

struct xoshiro256ss_state {
	uint64_t s[4];
};

uint64_t xoshiro256ss(struct xoshiro256ss_state *state)
{
	uint64_t *s = state->s;
	uint64_t const result = rol64(s[1] * 5, 7) * 9;
	uint64_t const t = s[1] << 17;

	s[2] ^= s[0];
	s[3] ^= s[1];
	s[1] ^= s[2];
	s[0] ^= s[3];

	s[2] ^= t;
	s[3] = rol64(s[3], 45);

	return result;
}

/*
xoshiro256+

xoshiro256+ is approximately 15% faster than xoshiro256**, but the lowest three bits have low linear complexity; therefore, it should be used only for floating point results by extracting the upper 53 bits.

xoroshiro

If space is at a premium, xoroshiro128** and xoroshiro128+ are equivalent to
xoshiro256** and xoshiro256+. These have smaller state spaces, and thus are less
useful for massively parallel programs. xoroshiro128+ also exhibits a mild
dependency in the population count, generating a failure after 5 TB of output.
The authors do not believe that this can be detected in real world programs.

xoroshiro64** and xoroshiro64* are equivalent to xoroshiro128** and
xoroshiro128+. Unlike the xoshiro generators, they are not straightforward ports
of their higher-precision counterparts.

Initialization

In the xoshiro paper, it is recommended to initialize the state of the
generators using a generator which is radically different from the initialized
generators, as well as one which will never give the "all-zero" state; for
shift-register generators, this state is impossible to escape from. The authors
specifically recommend using the SplitMix64 generator, from a 64-bit seed, as
follows:
*/


#include <stdint.h>

uint64_t rol64(uint64_t x, int k)
{
	return (x << k) | (x >> (64 - k));
}

struct xoshiro256p_state {
	uint64_t s[4];
};

uint64_t xoshiro256p(struct xoshiro256p_state *state)
{
	uint64_t *s = state->s;
	uint64_t const result = s[0] + s[3];
	uint64_t const t = s[1] << 17;

	s[2] ^= s[0];
	s[3] ^= s[1];
	s[1] ^= s[2];
	s[0] ^= s[3];

	s[2] ^= t;
	s[3] = rol64(s[3], 45);

	return result;
}

#endif


} //::chaos::generators ////////////////////////////////////////////////////////
} //::chaos ////////////////////////////////////////////////////////////////////

CHAOS_GENERATOR_REGISTER_3PARAM(XORSHIFT32, chaos::generators::xorshift, uint32_t, 13, 17, 5);  // Marsaglia suggestion for 32bit random on small machines
CHAOS_GENERATOR_REGISTER_3PARAM(XORSHIFT64, chaos::generators::xorshift, uint64_t, 13, 7, 17);  // Marsaglia suggestion for 64bit random on small machines
CHAOS_GENERATOR_REGISTER_3PARAM(XORSHIFT128, chaos::generators::xorshift128, uint32_t, 11, 8, 19);
CHAOS_GENERATOR_REGISTER_4PARAM(XORWOW, chaos::generators::xorwow, uint32_t, 2, 1, 4, 362437);
/* xorshift64s, variant A_1(12,25,27) with multiplier M_32 from line 3 of table 5 */
CHAOS_GENERATOR_REGISTER_3PARAM(XORSHIFT64STAR, chaos::generators::xorshiftplus, uint64_t, 12, 25, 27);

#endif // CHAOS_GENERATORS_XORSHIFT_HH
