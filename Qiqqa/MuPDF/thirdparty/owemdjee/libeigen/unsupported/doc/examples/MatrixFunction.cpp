#include <unsupported/Eigen/MatrixFunctions>
#include <iostream>

using namespace Eigen;

std::complex<double> expfn(std::complex<double> x, int) { return std::exp(x); }


#if defined(BUILD_MONOLITHIC)
#define main eigen_doc_example_matrix_func_main
#endif

int main() {
  const double pi = std::acos(-1.0);

  MatrixXd A(3, 3);
  A << 0, -pi / 4, 0, pi / 4, 0, 0, 0, 0, 0;

  std::cout << "The matrix A is:\n" << A << "\n\n";
  std::cout << "The matrix exponential of A is:\n" << A.matrixFunction(expfn) << "\n\n";
  return 0;
}
