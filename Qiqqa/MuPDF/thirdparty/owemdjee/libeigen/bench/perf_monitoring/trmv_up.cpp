#include "gemv_common.h"

EIGEN_DONT_INLINE void trmv(const Mat &A, const Vec &B, Vec &C) { C.noalias() += A.triangularView<Upper>() * B; }


#if defined(BUILD_MONOLITHIC)
#define main eigen_mon_tmv_up_main
#endif

int main(int argc, char **argv) { return main_gemv(argc, argv, trmv); }
