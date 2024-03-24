#include "gemv_common.h"

EIGEN_DONT_INLINE void trmv(const Mat &A, Vec &B, const Vec &C) {
  B.noalias() += A.transpose().triangularView<Lower>() * C;
}


#if defined(BUILD_MONOLITHIC)
#define main eigen_mon_tmv_lot_main
#endif

int main(int argc, char **argv) { return main_gemv(argc, argv, trmv); }
