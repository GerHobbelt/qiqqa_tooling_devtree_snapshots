#include <iostream>
#include <Eigen/Dense>

using namespace std;


#if defined(BUILD_MONOLITHIC)
#define main eigen_doc_tutorial_redvisit_col_main
#endif

int main() {
  Eigen::MatrixXf mat(2, 4);
  mat << 1, 2, 6, 9, 3, 1, 7, 2;

  std::cout << "Column's maximum: " << std::endl << mat.colwise().maxCoeff() << std::endl;
  return 0;
}
