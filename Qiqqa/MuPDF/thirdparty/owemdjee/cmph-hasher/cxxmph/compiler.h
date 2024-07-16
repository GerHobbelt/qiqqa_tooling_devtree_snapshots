#pragma once

// The next __builtin_prefetch portability code chunk is ripped & adapted from GraphBLAS/zstd:

/* prefetch
 * can be disabled, by declaring NO_PREFETCH build macro */
#if defined(NO_PREFETCH)
#  define CMPH_PREFETCH_L1(ptr)  (void)(ptr)  /* disabled */
#  define CMPH_PREFETCH_L2(ptr)  (void)(ptr)  /* disabled */
#else
#  if defined(_MSC_VER) && (defined(_M_X64) || defined(_M_I86))  /* _mm_prefetch() is not defined outside of x86/x64 */
#    include <xmmintrin.h>   /* _MM_HINT_T0, _MM_HINT_T1 */
#    include <mmintrin.h>   /* https://msdn.microsoft.com/fr-fr/library/84szxsww(v=vs.90).aspx */
#    define CMPH_PREFETCH_L1(ptr)  _mm_prefetch((const char*)(ptr), _MM_HINT_T0)
#    define CMPH_PREFETCH_L2(ptr)  _mm_prefetch((const char*)(ptr), _MM_HINT_T1)
#  elif defined(__GNUC__) && ( (__GNUC__ >= 4) || ( (__GNUC__ == 3) && (__GNUC_MINOR__ >= 1) ) )
#    define CMPH_PREFETCH_L1(ptr)  __builtin_prefetch((ptr), 0 /* rw==read */, 3 /* locality */)
#    define CMPH_PREFETCH_L2(ptr)  __builtin_prefetch((ptr), 0 /* rw==read */, 2 /* locality */)
#  elif defined(__aarch64__)
#    define CMPH_PREFETCH_L1(ptr)  __asm__ __volatile__("prfm pldl1keep, %0" ::"Q"(*(ptr)))
#    define CMPH_PREFETCH_L2(ptr)  __asm__ __volatile__("prfm pldl2keep, %0" ::"Q"(*(ptr)))
#  else
#    define CMPH_PREFETCH_L1(ptr) (void)(ptr)  /* disabled */
#    define CMPH_PREFETCH_L2(ptr) (void)(ptr)  /* disabled */
#  endif
#endif  /* NO_PREFETCH */



 // The next __builtin_expect portability code chunk is ripped & adapted from IMath (of OpenEXR fame):

 //
 // Some compilers define a special intrinsic to use in conditionals that can
 // speed up extremely performance-critical spots if the conditional is
 // usually (or rarely) is true.  You use it by replacing
 //     if (x) ...
 // with
 //     if (IMATH_LIKELY(x)) ...     // if you think x will usually be true
 // or
 //     if (IMATH_UNLIKELY(x)) ...   // if you think x will rarely be true
 //
 // Caveat: Programmers are notoriously bad at guessing this, so it should be
 // used only with thorough benchmarking.
 //
#if defined(__GNUC__) || defined(__clang__) || defined(__INTEL_COMPILER)
#    define CMPH_LIKELY(x) (__builtin_expect(bool(x), true))
#    define CMPH_UNLIKELY(x) (__builtin_expect(bool(x), false))
#else
#    define CMPH_LIKELY(x) (x)
#    define CMPH_UNLIKELY(x) (x)
#endif
