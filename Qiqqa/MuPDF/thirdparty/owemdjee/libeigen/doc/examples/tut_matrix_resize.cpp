#include <iostream>
#include <Eigen/Dense>


#if defined(BUILD_MONOLITHIC)
#define main eigen_doc_tutorial_matrix_resize_main
#endif

int main() {
  Eigen::MatrixXd m(2, 5);
  m.resize(4, 3);
  std::cout << "The matrix m is of size " << m.rows() << "x" << m.cols() << std::endl;
  std::cout << "It has " << m.size() << " coefficients" << std::endl;
  Eigen::VectorXd v(2);
  v.resize(5);
  std::cout << "The vector v is of size " << v.size() << std::endl;
  std::cout << "As a matrix, v is of size " << v.rows() << "x" << v.cols() << std::endl;
  return 0;
}
