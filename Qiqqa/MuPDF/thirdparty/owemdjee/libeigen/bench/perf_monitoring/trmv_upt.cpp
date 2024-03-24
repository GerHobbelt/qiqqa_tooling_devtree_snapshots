#include "gemv_common.h"

EIGEN_DONT_INLINE void trmv(const Mat &A, Vec &B, const Vec &C) {
  B.noalias() += A.transpose().triangularView<Upper>() * C;
}


#if defined(BUILD_MONOLITHIC)
#define main eigen_mon_tmv_upt_main
#endif

int main(int argc, char **argv) { return main_gemv(argc, argv, trmv); }
