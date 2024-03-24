#include <Eigen/Core>
#include <Eigen/LU>
#include <iostream>


#if defined(BUILD_MONOLITHIC)
#define main eigen_doc_tutorial_partial_lu_solver_main
#endif

int main() {
  Eigen::Matrix3f A;
  Eigen::Vector3f b;
  A << 1, 2, 3, 4, 5, 6, 7, 8, 10;
  b << 3, 3, 4;
  std::cout << "Here is the matrix A:" << std::endl << A << std::endl;
  std::cout << "Here is the vector b:" << std::endl << b << std::endl;
  Eigen::Vector3f x = A.lu().solve(b);
  std::cout << "The solution is:" << std::endl << x << std::endl;
  return 0;
}
