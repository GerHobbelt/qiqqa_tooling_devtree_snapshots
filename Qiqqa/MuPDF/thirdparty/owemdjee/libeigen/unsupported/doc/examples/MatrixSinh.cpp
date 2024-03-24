#include <unsupported/Eigen/MatrixFunctions>
#include <iostream>

using namespace Eigen;


#if defined(BUILD_MONOLITHIC)
#define main eigen_doc_example_matrix_sinh_main
#endif

int main() {
  MatrixXf A = MatrixXf::Random(3, 3);
  std::cout << "A = \n" << A << "\n\n";

  MatrixXf sinhA = A.sinh();
  std::cout << "sinh(A) = \n" << sinhA << "\n\n";

  MatrixXf coshA = A.cosh();
  std::cout << "cosh(A) = \n" << coshA << "\n\n";

  // The matrix functions satisfy cosh^2(A) - sinh^2(A) = I,
  // like the scalar functions.
  std::cout << "cosh^2(A) - sinh^2(A) = \n" << coshA * coshA - sinhA * sinhA << "\n\n";
  return 0;
}
