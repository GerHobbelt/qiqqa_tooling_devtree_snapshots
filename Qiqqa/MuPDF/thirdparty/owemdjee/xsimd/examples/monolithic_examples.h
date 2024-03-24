
#pragma once

#if defined(BUILD_MONOLITHIC)

#ifdef __cplusplus
extern "C" {
#endif

int xsimd_benchmark_main(int argc, const char** argv);
int xsimd_sample_mandelbrot_main(void);

#ifdef __cplusplus
}
#endif

#endif
