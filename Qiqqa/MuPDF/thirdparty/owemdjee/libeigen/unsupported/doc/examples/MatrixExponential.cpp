#include <unsupported/Eigen/MatrixFunctions>
#include <iostream>

using namespace Eigen;


#if defined(BUILD_MONOLITHIC)
#define main eigen_doc_example_matrix_exp_main
#endif

int main() {
  const double pi = std::acos(-1.0);

  MatrixXd A(3, 3);
  A << 0, -pi / 4, 0, pi / 4, 0, 0, 0, 0, 0;
  std::cout << "The matrix A is:\n" << A << "\n\n";
  std::cout << "The matrix exponential of A is:\n" << A.exp() << "\n\n";
  return 0;
}
