#include <Eigen/Core>
#include <unsupported/Eigen/SpecialFunctions>
#include <iostream>


#if defined(BUILD_MONOLITHIC)
#define main eigen_doc_example_cwise_gamma_main
#endif

int main() {
  Eigen::Array4d v(0.5, 10, 0, -1);
  std::cout << v.lgamma() << std::endl;
  return 0;
}
