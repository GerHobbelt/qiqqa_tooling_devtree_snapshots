
#ifndef _BLAKE3_GET_CPU_FEATURES_H_
#define _BLAKE3_GET_CPU_FEATURES_H_

#ifdef __cplusplus
extern "C" {
#endif

	/* A little repetition here */
	enum blake3_cpu_feature {
		SSE2 = 1 << 0,
		SSSE3 = 1 << 1,
		SSE41 = 1 << 2,
		AVX = 1 << 3,
		AVX2 = 1 << 4,
		AVX512F = 1 << 5,
		AVX512VL = 1 << 6,
		/* ... */
		UNDEFINED = 1 << 30
	};

	extern enum blake3_cpu_feature g_blake3_cpu_features;
	enum blake3_cpu_feature blake3_get_cpu_features();

#ifdef __cplusplus
}
#endif

#endif
