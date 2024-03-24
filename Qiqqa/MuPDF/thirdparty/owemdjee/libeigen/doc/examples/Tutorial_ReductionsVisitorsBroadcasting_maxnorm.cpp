#include <iostream>
#include <Eigen/Dense>


#if defined(BUILD_MONOLITHIC)
#define main eigen_doc_tutorial_redvisit_maxnorm_main
#endif

int main() {
  Eigen::MatrixXf mat(2, 4);
  mat << 1, 2, 6, 9, 3, 1, 7, 2;

  Eigen::Index maxIndex;
  float maxNorm = mat.colwise().sum().maxCoeff(&maxIndex);

  std::cout << "Maximum sum at position " << maxIndex << std::endl;

  std::cout << "The corresponding vector is: " << std::endl;
  std::cout << mat.col(maxIndex) << std::endl;
  std::cout << "And its sum is is: " << maxNorm << std::endl;
  return 0;
}
