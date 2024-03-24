#include <iostream>
#include <Eigen/Dense>

using namespace std;


#if defined(BUILD_MONOLITHIC)
#define main eigen_doc_tutorial_redvisit_simple_row_main
#endif

int main() {
  Eigen::MatrixXf mat(2, 4);
  Eigen::VectorXf v(4);

  mat << 1, 2, 6, 9, 3, 1, 7, 2;

  v << 0, 1, 2, 3;

  // add v to each row of m
  mat.rowwise() += v.transpose();

  std::cout << "Broadcasting result: " << std::endl;
  std::cout << mat << std::endl;
  return 0;
}
