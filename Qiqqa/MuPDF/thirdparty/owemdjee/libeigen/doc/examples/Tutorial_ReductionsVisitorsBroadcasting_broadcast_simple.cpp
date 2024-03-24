#include <iostream>
#include <Eigen/Dense>

using namespace std;


#if defined(BUILD_MONOLITHIC)
#define main eigen_doc_tutorial_redvisit_simple_main
#endif

int main() {
  Eigen::MatrixXf mat(2, 4);
  Eigen::VectorXf v(2);

  mat << 1, 2, 6, 9, 3, 1, 7, 2;

  v << 0, 1;

  // add v to each column of m
  mat.colwise() += v;

  std::cout << "Broadcasting result: " << std::endl;
  std::cout << mat << std::endl;
  return 0;
}
