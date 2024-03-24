#include <iostream>
#include <Eigen/Dense>


#if defined(BUILD_MONOLITHIC)
#define main eigen_doc_tutorial_matrix_resize_fixed_main
#endif

int main() {
  Eigen::Matrix4d m;
  m.resize(4, 4);  // no operation
  std::cout << "The matrix m is of size " << m.rows() << "x" << m.cols() << std::endl;
  return 0;
}
