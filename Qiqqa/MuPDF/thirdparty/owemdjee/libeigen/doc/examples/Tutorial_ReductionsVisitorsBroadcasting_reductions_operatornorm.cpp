#include <Eigen/Dense>
#include <iostream>


#if defined(BUILD_MONOLITHIC)
#define main eigen_doc_tutorial_redvisit_op_norm_main
#endif

int main() {
  Eigen::MatrixXf m(2, 2);
  m << 1, -2, -3, 4;

  std::cout << "1-norm(m)     = " << m.cwiseAbs().colwise().sum().maxCoeff()
            << " == " << m.colwise().lpNorm<1>().maxCoeff() << std::endl;

  std::cout << "infty-norm(m) = " << m.cwiseAbs().rowwise().sum().maxCoeff()
            << " == " << m.rowwise().lpNorm<1>().maxCoeff() << std::endl;
  return 0;
}
