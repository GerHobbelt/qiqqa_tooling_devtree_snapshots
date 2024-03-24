#include <iostream>
#include <Eigen/Dense>


#if defined(BUILD_MONOLITHIC)
#define main eigen_doc_tutorial_redvisit_base_main
#endif

int main() {
  Eigen::MatrixXf m(2, 2);

  m << 1, 2, 3, 4;

  // get location of maximum
  Eigen::Index maxRow, maxCol;
  float max = m.maxCoeff(&maxRow, &maxCol);

  // get location of minimum
  Eigen::Index minRow, minCol;
  float min = m.minCoeff(&minRow, &minCol);

  std::cout << "Max: " << max << ", at: " << maxRow << "," << maxCol << std::endl;
  std::cout << "Min: " << min << ", at: " << minRow << "," << minCol << std::endl;
  return 0;
}
