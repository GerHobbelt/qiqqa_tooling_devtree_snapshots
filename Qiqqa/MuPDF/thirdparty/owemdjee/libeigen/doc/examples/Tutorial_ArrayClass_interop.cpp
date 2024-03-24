#include <Eigen/Dense>
#include <iostream>

using Eigen::MatrixXf;


#if defined(BUILD_MONOLITHIC)
#define main eigen_doc_tutorial_arr_interop_main
#endif

int main() {
  MatrixXf m(2, 2);
  MatrixXf n(2, 2);
  MatrixXf result(2, 2);

  m << 1, 2, 3, 4;
  n << 5, 6, 7, 8;

  result = (m.array() + 4).matrix() * m;
  std::cout << "-- Combination 1: --\n" << result << "\n\n";
  result = (m.array() * n.array()).matrix() * m;
  std::cout << "-- Combination 2: --\n" << result << "\n\n";
  return 0;
}
