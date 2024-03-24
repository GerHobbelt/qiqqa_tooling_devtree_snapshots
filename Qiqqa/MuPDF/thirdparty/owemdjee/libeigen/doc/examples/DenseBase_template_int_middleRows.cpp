#include <Eigen/Core>
#include <iostream>


#if defined(BUILD_MONOLITHIC)
#define main eigen_doc_example_tpl_midrows_main
#endif

int main() {
  int const N = 5;
  Eigen::MatrixXi A(N, N);
  A.setRandom();
  std::cout << "A =\n" << A << '\n' << std::endl;
  std::cout << "A(1..3,:) =\n" << A.middleRows<3>(1) << std::endl;
  return 0;
}
