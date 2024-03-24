#include <iostream>
#include <Eigen/Dense>


#if defined(BUILD_MONOLITHIC)
#define main eigen_doc_tutorial_scalar_mul_div_main
#endif

int main() {
  Eigen::Matrix2d a;
  a << 1, 2, 3, 4;
  Eigen::Vector3d v(1, 2, 3);
  std::cout << "a * 2.5 =\n" << a * 2.5 << std::endl;
  std::cout << "0.1 * v =\n" << 0.1 * v << std::endl;
  std::cout << "Doing v *= 2;" << std::endl;
  v *= 2;
  std::cout << "Now v =\n" << v << std::endl;
  return 0;
}
