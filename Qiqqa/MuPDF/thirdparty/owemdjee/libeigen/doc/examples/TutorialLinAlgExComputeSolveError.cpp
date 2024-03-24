#include <iostream>
#include <Eigen/Dense>

using Eigen::MatrixXd;


#if defined(BUILD_MONOLITHIC)
#define main eigen_doc_tutorial_lin_comp_solve_err_main
#endif

int main() {
  MatrixXd A = MatrixXd::Random(100, 100);
  MatrixXd b = MatrixXd::Random(100, 50);
  MatrixXd x = A.fullPivLu().solve(b);
  double relative_error = (A * x - b).norm() / b.norm();  // norm() is L2 norm
  std::cout << "The relative error is:\n" << relative_error << std::endl;
  return 0;
}
