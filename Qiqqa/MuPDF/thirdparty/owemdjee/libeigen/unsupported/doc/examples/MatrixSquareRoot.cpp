#include <unsupported/Eigen/MatrixFunctions>
#include <iostream>

using namespace Eigen;


#if defined(BUILD_MONOLITHIC)
#define main eigen_doc_example_matrix_sqrt_main
#endif

int main() {
  const double pi = std::acos(-1.0);

  MatrixXd A(2, 2);
  A << cos(pi / 3), -sin(pi / 3), sin(pi / 3), cos(pi / 3);
  std::cout << "The matrix A is:\n" << A << "\n\n";
  std::cout << "The matrix square root of A is:\n" << A.sqrt() << "\n\n";
  std::cout << "The square of the last matrix is:\n" << A.sqrt() * A.sqrt() << "\n";
  return 0;
}
