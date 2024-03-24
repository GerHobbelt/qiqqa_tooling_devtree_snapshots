#include <unsupported/Eigen/MatrixFunctions>
#include <iostream>

using namespace Eigen;


#if defined(BUILD_MONOLITHIC)
#define main eigen_doc_example_matrix_log_main
#endif

int main() {
  using std::sqrt;
  MatrixXd A(3, 3);
  A << 0.5 * sqrt(2), -0.5 * sqrt(2), 0, 0.5 * sqrt(2), 0.5 * sqrt(2), 0, 0, 0, 1;
  std::cout << "The matrix A is:\n" << A << "\n\n";
  std::cout << "The matrix logarithm of A is:\n" << A.log() << "\n";
  return 0;
}
